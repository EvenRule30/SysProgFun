#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char *s = malloc(sizeof(char)*33);
  if (s == NULL) {
    printf("Error, malloc failed to allocate.");
    exit(1);
  }
  int n;

  printf("Enter a word: ");
  scanf("%s", s);

  printf("Enter a count: ");
  scanf("%d", &n);

  char *out = malloc(sizeof(char)*(32*n+1));
  if (!out) {
    printf("Cannot allocate new string. Exiting...\n");
    exit(1);
  }

  printf("Your word is ");
  for (int i = 0; i < n; ++i) {
    strcat(out, s);
  }
  
  printf("%s\n", out);
  free(s);
  free(out);
  s = NULL;
  out = NULL;

  return 0;
}
