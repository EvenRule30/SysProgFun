#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
  char word[4];
  char hex_word1[3], hex_word2[3], hex_word3[3], hex_word4[3];
  long int deci1, deci2, deci3, deci4;
  char *ptr;

  printf("Enter 4 characters: ");
  scanf(" %s", word);

  sprintf(hex_word1, "%02X", (unsigned char)word[0]);
  sprintf(hex_word2, "%02X", (unsigned char)word[1]);
  sprintf(hex_word3, "%02X", (unsigned char)word[2]);
  sprintf(hex_word4, "%02X", (unsigned char)word[3]);

  printf("Debug: %c = 0x000000%s\n", word[3], hex_word4);
  printf("Debug: %c = 0x0000%s00\n", word[2], hex_word3);
  printf("Debug: %c = 0x00%s0000\n", word[1], hex_word2);
  printf("Debug: %c = 0x%s000000\n", word[0], hex_word1);

  deci1 = strtol(hex_word1, &ptr, 16) * pow(16, 6);
  deci2 = strtol(hex_word2, &ptr, 16) * pow(16, 4);
  deci3 = strtol(hex_word3, &ptr, 16) * pow(16, 2);
  deci4 = strtol(hex_word4, &ptr, 16);
  long int deci = deci1 + deci2 + deci3 + deci4;

  printf("Your number is: %ld (0x%s%s%s%s)\n", deci, hex_word1, hex_word2, hex_word3, hex_word4);
  return 0;
}
