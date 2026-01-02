#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

#define MAX_LINE_LENGTH 256
// Feel free to change the function signature if you prefer to implement an 
// array of arrays
struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
  FILE *fp = fopen(filename, "rb");
  if (!fp) return NULL;

  char line[MAX_LINE_LENGTH];

  fgets(line, sizeof(line), fp);
  fgets(line, sizeof(line), fp);
  while (line[0] == '#') fgets(line, sizeof(line), fp);

  *w = atoi(strtok(line, " "));
  *h = atoi(strtok(NULL, " "));

  fgets(line, sizeof(line), fp);

  struct ppm_pixel *matrix = malloc(sizeof(struct ppm_pixel)*(*w)*(*h));

  fread(matrix, 3, (*w)*(*h), fp);

  return matrix;
}

// Feel free to change the function signature if you prefer to implement an 
// array of arrays
extern void write_ppm(const char* filename, struct ppm_pixel* pxs, int w, int h) {
  FILE *fp = fopen(filename, "wb");
  if (!fp) exit(1);

  fwrite("P6\n", sizeof(char), 3, fp);
  char *line = malloc(sizeof(char)*(1+MAX_LINE_LENGTH));
  if (!line) {
    printf("malloc fail.\n");
    exit(1);
  }
  sprintf(line, "%d %d\n", w, h);
  fwrite(line, sizeof(char), strlen(line), fp);
  fwrite("255\n", sizeof(char), 4, fp);

  unsigned char *color = malloc(sizeof(char)*(1+MAX_LINE_LENGTH));
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      struct ppm_pixel p = pxs[i*w+j];
      *color = p.red << ((rand() % 2) + 1);
      fwrite( (void *) color, 1, 1, fp);
      *color = p.green << ((rand() % 2) + 1);
      fwrite( (void *) color, 1, 1, fp);
      *color = p.blue << ((rand() % 2) + 1);
      fwrite( (void *) color, 1, 1, fp);
    }
  }

  fclose(fp);
  fp = NULL;
  free(line);
  line = NULL;
  free(color);
  color = NULL;
}
