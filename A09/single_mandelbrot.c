#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "read_ppm.h"

int main(int argc, char* argv[]) {
  struct timeval tstart, tend;
  gettimeofday(&tstart, NULL);

  int size = 480;
  float xmin = -2.0;
  float xmax = 0.47;
  float ymin = -1.12;
  float ymax = 1.12;
  int maxIterations = 1000;

  int opt;
  while ((opt = getopt(argc, argv, ":s:l:r:t:b:")) != -1) {
    switch (opt) {
      case 's': size = atoi(optarg); break;
      case 'l': xmin = atof(optarg); break;
      case 'r': xmax = atof(optarg); break;
      case 't': ymax = atof(optarg); break;
      case 'b': ymin = atof(optarg); break;
      case '?': printf("usage: %s -s <size> -l <xmin> -r <xmax> -b <ymin> -t <ymax>\n", argv[0]); break;
    }
  }
  printf("Generating mandelbrot with size %dx%d\n", size, size);
  printf("  X range = [%.4f,%.4f]\n", xmin, xmax);
  printf("  Y range = [%.4f,%.4f]\n", ymin, ymax);

  // todo: your work here
  // generate pallet
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

  // compute image
  struct ppm_pixel *pixmap = malloc(sizeof(struct ppm_pixel)*size*size);
  for (int i=0; i<size; i++) {
    for (int j=0; j<size; j++) {
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

  write_ppm("mandelbrot.ppm", pixmap, size, size);

  gettimeofday(&tend,NULL);
  int timer = tend.tv_sec - tstart.tv_sec;
  printf("Time in secs: %d\n", timer);
  return 0;
}