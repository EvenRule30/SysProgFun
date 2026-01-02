#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

int main(int argc, char** argv) {
  if(argc != 2) {
    printf("usage: ");
    for (int i=0; i<argc; i++)
      printf("%s", argv[i]);
    printf("\n");
  }

  int w, h;
  struct ppm_pixel *pixmap = read_ppm(argv[1], &w, &h);
  float intens;
  struct ppm_pixel p;
  printf("Reading %s with width %d and height %d\n", argv[1], w, h);

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      p = pixmap[i*w+j];
      intens = (p.red+p.green+p.blue)/3.0;
      if (intens <= 25) printf("@");
      else if (intens <= 50) printf("#");
      else if (intens <= 75) printf("%%");
      else if (intens <= 100) printf("*");
      else if (intens <= 125) printf("o");
      else if (intens <= 150) printf(";");
      else if (intens <= 175) printf(":");
      else if (intens <= 200) printf(",");
      else if (intens <= 225) printf(".");
      else printf(" ");
    }
    printf("\n");
  }

  free(pixmap);
  pixmap = NULL;
  return 0;
}

