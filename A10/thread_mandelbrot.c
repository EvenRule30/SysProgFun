#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include "read_ppm.h"

struct arg_struct {
  int ulrow,ulcol,lrrow,lrcol,size,maxIterations;
  float xmin,xmax,ymin,ymax;
  struct ppm_pixel* pixmap, * pallet, black;
};

void *populate_region(void *args) {
  struct arg_struct *as = (struct arg_struct *) args;
  int ulrow = as->ulrow,
      ulcol = as->ulcol,
      lrrow = as->lrrow,
      lrcol = as->lrcol,
      size = as->size,
      maxIterations = as->maxIterations;
  float xmin = as->xmin,
        xmax = as->xmax,
        ymin = as->ymin,
        ymax = as->ymax;
  struct ppm_pixel *pixmap = as->pixmap,
      *pallet = as->pallet,
      black = as->black;
  
  for (int i=ulrow; i<lrrow; i++) {
    for (int j=ulcol; j<lrcol; j++) {
      float real = xmin + j*(xmax-xmin)/size;
      float imag = ymin + i*(ymax-ymin)/size;

      float x = 0.0, y = 0.0;
      int inter = 0;
      while (inter < maxIterations && x*x+y*y < 4) {
        float xtemp = x*x-y*y + real;
        y = 2*x*y + imag;
        x = xtemp;
        inter++;
      }

      if (inter < maxIterations) {
        pixmap[i*size+j] = pallet[inter];
      } else {
        pixmap[i*size+j] = black;
      }
    }
  }
  return NULL;
}

int main(int argc, char* argv[]) {
  int size = 480;
  float xmin = -2.0;
  float xmax = 0.47;
  float ymin = -1.12;
  float ymax = 1.12;
  int maxIterations = 1000;
  int numProcesses = 4;

  int opt;
  while ((opt = getopt(argc, argv, ":s:l:r:t:b:p:")) != -1) {
    switch (opt) {
      case 's': size = atoi(optarg); break;
      case 'l': xmin = atof(optarg); break;
      case 'r': xmax = atof(optarg); break;
      case 't': ymax = atof(optarg); break;
      case 'b': ymin = atof(optarg); break;
      case '?': printf("usage: %s -s <size> -l <xmin> -r <xmax> "
        "-b <ymin> -t <ymax> -p <numProcesses>\n", argv[0]); break;
    }
  }
  printf("Generating mandelbrot with size %dx%d\n", size, size);
  printf("  Num processes = %d\n", numProcesses);
  printf("  X range = [%.4f,%.4f]\n", xmin, xmax);
  printf("  Y range = [%.4f,%.4f]\n", ymin, ymax);

  // todo: your code here
  // generate pallet
  // compute image
  struct ppm_pixel *pixmap = malloc(sizeof(struct ppm_pixel)*size*size);

  srand(time(0));
  struct ppm_pixel *pallet = malloc(sizeof(struct ppm_pixel)*maxIterations);
  for (int i = 0; i < maxIterations; i++) {
    struct ppm_pixel color;
    color.red = rand() % 256;
    color.green = rand() % 256;
    color.blue = rand() % 256;
    pallet[i] = color;
  }

  struct ppm_pixel black;
  black.red = 0;
  black.green = 0;
  black.blue = 0;

  int half = size/2;

  pthread_t t1, t2, t3, t4;

  struct arg_struct *a2 = malloc(sizeof(struct arg_struct));
  a2->ulrow = 0;
  a2->ulcol = half;
  a2->lrcol = size;
  a2->lrrow = half;
  a2->size = size;
  a2->maxIterations = maxIterations;
  a2->xmin = xmin;
  a2->xmax = xmax;
  a2->ymin = ymin;
  a2->ymax = ymax;
  a2->pixmap = pixmap;
  a2->pallet = pallet;
  a2->black = black;

  struct arg_struct *a3 = malloc(sizeof(struct arg_struct));
  a2->ulrow = half;
  a2->ulcol = 0;
  a2->lrcol = half;
  a2->lrrow = size;
  a2->size = size;
  a2->maxIterations = maxIterations;
  a2->xmin = xmin;
  a2->xmax = xmax;
  a2->ymin = ymin;
  a2->ymax = ymax;
  a2->pixmap = pixmap;
  a2->pallet = pallet;
  a2->black = black;

  struct arg_struct *a4 = malloc(sizeof(struct arg_struct));
  a2->ulrow = half;
  a2->ulcol = half;
  a2->lrcol = size;
  a2->lrrow = size;
  a2->size = size;
  a2->maxIterations = maxIterations;
  a2->xmin = xmin;
  a2->xmax = xmax;
  a2->ymin = ymin;
  a2->ymax = ymax;
  a2->pixmap = pixmap;
  a2->pallet = pallet;
  a2->black = black;

  struct arg_struct *a1 = malloc(sizeof(struct arg_struct));
  a2->ulrow = 0;
  a2->ulcol = 0;
  a2->lrcol = half;
  a2->lrrow = half;
  a2->size = size;
  a2->maxIterations = maxIterations;
  a2->xmin = xmin;
  a2->xmax = xmax;
  a2->ymin = ymin;
  a2->ymax = ymax;
  a2->pixmap = pixmap;
  a2->pallet = pallet;
  a2->black = black;

  pthread_create(&t1, NULL, populate_region, a1);
  pthread_create(&t2, NULL, populate_region, a2);
  pthread_create(&t3, NULL, populate_region, a3);
  pthread_create(&t4, NULL, populate_region, a4);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  pthread_join(t3, NULL);
  pthread_join(t4, NULL);

  write_ppm("mandelbrot.ppm", pixmap, size, size);

  return 0;
}
