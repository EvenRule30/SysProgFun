#include <stdio.h>
#include <stdlib.h>
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

  unsigned char *message = malloc(sizeof(unsigned char)*((w*h*3)/8 + 1));
  int byteind = 0;
  //  01100110
  //  01000010
  // &--------
  //  01000000
  unsigned char mask = 1;
  while (byteind < w*h*3) {
    int pixind = byteind / 3;
    int rgbind = byteind % 3;
    unsigned char bit = pixmap[pixind].colors[rgbind];
    if (byteind % 8 == 0) message[byteind/8] = 0;
    bit &= mask;
    int shift = 7 - (byteind % 8);
    bit = bit << shift;
    message[byteind/8] += bit;

    if (byteind % 8 == 7 && message[byteind/8] == '\0') break;
    byteind++;
  }

  printf("Reading %s with width %d and height %d\nMax number of characters in the image: %d\n%s\n", argv[1], w, h, w*h*3/8, message);

  free(pixmap);
  pixmap = NULL;
  free(message);
  message = NULL;

  return 0;
}

