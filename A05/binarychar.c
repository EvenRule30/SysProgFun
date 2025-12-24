#include <stdio.h>
#include <stdlib.h>

int main() {
  char binary[8];
  char binary_char;
  long deci;
  printf("Enter 8 bits: ");
  scanf("%s", binary);

  deci = strtol(binary, NULL, 2);
  binary_char = (char)deci;

  printf("Your character is: %c\n", binary_char);
  return 0;
}
