#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include "read_ppm.h"

void populate_region(int ulrow, int ulcol, int lrrow, int lrcol,
    int size,
    float xmin, float xmax, float ymin, float ymax,
    int maxIterations,
    struct ppm_pixel *pixmap, struct ppm_pixel *pallet,
    struct ppm_pixel black) {

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
}

int main(int argc, char* argv[]) {
  struct timeval tstart, tend;
  gettimeofday(&tstart, NULL);

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
  key_t key = ftok(".", 'w');
  size_t pmsize = sizeof(struct ppm_pixel)*size*size;
  int shmid = shmget(key, pmsize, IPC_CREAT | 0666);
  if(shmid == -1) {
    perror("shmget");
    exit(1);
  }

  struct ppm_pixel *pixmap = shmat(shmid, NULL, 0);
  if (pixmap == (struct ppm_pixel *)-1) {
    perror("shmat");
    exit(1);
  }

  pid_t c1 = fork();
  if (c1 == 0) {
    pid_t c2 = fork();
    if (c2 == 0) {
      pid_t c3 = fork();
      if (c3 == 0) {
        populate_region(0,0,half,half,size,
            xmin, xmax, ymin, ymax, maxIterations,
            pixmap, pallet, black);
      } else {
        populate_region(0,half,half,size,size,
            xmin, xmax, ymin, ymax, maxIterations,
            pixmap, pallet, black);
      }
      wait(NULL);
      exit(0);
    } else {
      populate_region(half,0,size,half,size,
          xmin, xmax, ymin, ymax, maxIterations,
          pixmap, pallet, black);
      wait(NULL);
      exit(0);
    }
  } else {
    populate_region(half,half,size,size,size,
        xmin, xmax, ymin, ymax, maxIterations,
        pixmap, pallet, black);
    wait(NULL);
  }
  
  write_ppm("mandelbrot.ppm", pixmap, size, size);

  shmdt(pixmap);
  shmctl(shmid, IPC_RMID, NULL);

  gettimeofday(&tend,NULL);
  int timer = tend.tv_sec - tstart.tv_sec;
  printf("Time in secs: %d\n", timer);

  return 0;

  // compute image

}
