#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main() {
  srand(time(NULL));
  FILE *fptr;
  fptr = fopen("words.txt", "r");
  if (!fptr) {
    printf("File open error.\n");
    exit(1);
  }

  char *word = malloc(sizeof(char)*33);
  fgets(word, 32, fptr);
  int size = atoi(word);

  int line = rand() % size;
  for (int i = 0; i < line; ++i) {
    fgets(word, 32, fptr);
  }

  printf("Welcome to Word Guess!\n\n");
  int j = 1;
  int word_len = strlen(word)-1;
  char *guessword = malloc(sizeof(char)*(word_len+1));
  for (int i = 0; i < word_len; ++i)
    guessword[i] = '_';
  
  char guess;
  int inc;
  int left = word_len;
  while (left) {
    printf("Turn: %d\n\n", j);
    j++;
    for (int i = 0; i < word_len; ++i)
      printf("%c ", guessword[i]);
    printf("\nGuess a character: ");
    scanf(" %c", &guess);
    for (int i = 0; i < word_len; ++i) {
      if (word[i] == guess && guessword[i] == '_') {
        guessword[i] = guess;
        left--;
      } else
        inc++;
    }
    if (inc == word_len)
      printf("Sorry, %c not found!\n", guess);
    inc = 0;

    if (left == 0) {
      printf("\n");
      for (int i = 0; i < word_len; ++i)
        printf("%c ", guessword[i]);
    }
  }

  printf("\nYou won in %d turns!\n", --j);

  fclose(fptr);
  free(word);
  free(guessword);
  guessword = NULL;
  word = NULL;
  fptr = NULL;

  return 0;
}
