#include <stdio.h>
#include <stdlib.h>

int main() {
  char *password = malloc(sizeof(char) * 10);
  if (password == NULL) {
    printf("Malloc failed.");
    exit(1);
  }
  password[0] = '\0';

  printf("Enter a word: ");
  scanf("%s", password);

  for (int i = 0; i < 10; ++i) {
    if (password[i] != '\0') {
      if (password[i] == 'e') 
        password[i] = '3';
      else if (password[i] == 'l') 
        password[i] = '1';
      else if (password[i] == 'a') 
        password[i] = '@';
    } else {
        printf("Your bad password is %s\n", password);
        break;
    }
  }

  free(password);
  password = NULL;
  return 0;
}
