#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct snack {
  char name[32];
  float cost;
  int quantity;
};

int main() {
  int num;

  printf("Enter a number of snacks: ");
  scanf("%d", &num);
  struct snack *pt = malloc(num * sizeof(struct snack));

  for (int i = 0; i < num; i++) {
    printf("Enter a name: ");
    scanf("%s", pt[i].name);
    printf("Enter a cost: ");
    scanf("%f", &pt[i].cost);
    printf("Enter a quantity: ");
    scanf("%d", &pt[i].quantity);
  }

  for (int i = 0; i < num; ++i) {
    printf("\nWelcome to Dynamic Donna's Snack Bar\n\n%d) %s \t\t cost: $%.2f \t\t quantity: %d\n", i, pt[i].name, pt[i].cost, pt[i].quantity);
  }

  free(pt);
  pt = NULL; 

  return 0;
}
