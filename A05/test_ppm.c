#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: ");
    for (int i = 0; i < argc; i++) {
      printf("%s ", argv[i]);
    }
    printf("\n");
  }

  int w, h;
  struct ppm_pixel *pixmap = read_ppm(argv[1], &w, &h);
  // for (int i = 0; i < h; i++) {
  //   for (int j = 0; j < w; j++) {
  //     struct ppm_pixel p = pixmap[i*w+j];
  //     printf("r:%d g:%d b:%d\t", p.red, p.green, p.blue);
  //   }
  //   printf("\n");
  // }

  char *newfile = malloc(sizeof(char)*200);
  strcpy(newfile, strtok(argv[1], "."));
  strcat(newfile, "-glitch.ppm");

  write_ppm(newfile, pixmap, w, h);


  free (pixmap);
  pixmap = NULL;

  return 0;
}

