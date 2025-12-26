#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "read_ppm.h"

// TODO: Implement this function
// Feel free to change the function signature if you prefer to implement an 
// array of arrays
struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
  FILE *fptr = fopen(filename, "r");
  if (!fptr) return NULL;

  char *line = malloc(sizeof(char)*101);
  fgets(line, 100, fptr);
  fgets(line, 100, fptr);
  while (line[0] == '#' || isspace(line[0])) fgets(line, 100, fptr);

  char *num = strtok(line, " ");
  *w = atoi(num);
  num = strtok(NULL, " ");
  *h = atoi(num);

  fgets(line, 100, fptr);
  while (line[0] == '#' || isspace(line[0])) fgets(line, 100, fptr);

  struct ppm_pixel *matrix = malloc(sizeof(struct ppm_pixel)*(*w)*(*h));
  if (!matrix) return NULL;
  int i = 0;
  unsigned char r, g, b;
  
  while (fscanf(fptr, " %hhu %hhu %hhu", &r, &g, &b) == 3) {
    struct ppm_pixel p;
    p.red = r;
    p.green = g;
    p.blue = b;
    matrix[i] = p;
    i++;
  }

  // struct ppm_pixel p;
  // for (int i = 0; i < *h; ++i) {
  //   for (int j = 0; j < *w; ++j) {
  //     p = matrix[i*(*w)+j];
  //     printf("(%d, %d, %d)\t", p.red, p.green, p.blue);
  //   }
  //   printf("\n");
  // }

  fclose(fptr);
  fptr = NULL;
  free(line);
  line = NULL;
  
  return matrix;
}

