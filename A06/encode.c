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
    return 1;
  }

  int w, h;
  struct ppm_pixel *pixmap = read_ppm(argv[1], &w, &h);

  int maxchar = w*h*3/8;
  printf("Reading %s with width %d and height %d\nMax number of characters in the image: %d\nEnter a phrase: ", argv[1], w, h, maxchar);
  char *message = malloc(sizeof(unsigned char)*maxchar);
  if (!message) {
    printf("Malloc fail.\n");
    exit(1);
  }
  scanf("%s", message);
  char *newfilename = malloc(sizeof(char)*strlen(argv[1]+1+8));
  if (!newfilename) {
    printf("Malloc fail\n");
    exit(1);
  }
  strcpy(newfilename, strtok(argv[1], "."));
  strcat(newfilename, "-encoded.ppm");
  printf("Writing file %s\n", newfilename);

  int byteind = 7;
  unsigned char mask0 = -2;
  unsigned char mask1 = 1;

  for (int i=0; i<strlen(message); i++) {
    char c = message[i];
    for (int j=0; j<8; j++) {
      int pixind = byteind / 3;
      int rgbind = byteind % 3;
      int bit = c%2;
      if (bit) pixmap[pixind].colors[rgbind] |= mask1;
      else pixmap[pixind].colors[rgbind] &= mask0;
      byteind--;
      c = c >> 1;
    }
    byteind += 16;
  }

  write_ppm(newfilename, pixmap, w, h);

  free(pixmap);
  pixmap = NULL;
  free(message);
  message = NULL;
  free(newfilename);
  newfilename = NULL;

  return 0;
}

