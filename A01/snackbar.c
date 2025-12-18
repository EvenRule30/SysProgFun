#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct snack {
    char name[30];
    float cost;
    int quantity;
  };

int main() {
  struct snack slist[3];
  strcpy(slist[0].name, "Coco Puffs");
  slist[0].cost = 1.50;
  slist[0].quantity = 4;

  strcpy(slist[1].name, "Manchego cheese");
  slist[1].cost = 15.50;
  slist[1].quantity = 6;

  strcpy(slist[2].name, "Magic beans");
  slist[2].cost = 0.50;
  slist[2].quantity = 0;

  int money, item;

  printf("Welcome to Steven Struct's Snack Bar.\n\nHow much money do you have? ");
  scanf("%d", &money);

  printf("\n");
  for (int i = 0; i < 3; ++i) {
    printf("%d) %s \t\t cost: $%.2f \t\t quantity: %d\n", i, slist[i].name, slist[i].cost, slist[i].quantity);
  }

  printf("\nWhat snack would you like to buy? [0,1,2] ");
  scanf("%d", &item);

  if (!(item < 3 && item > -1)) {
    printf("Error: Out of bounds of machine.\n");
  } else if (slist[item].quantity == 0) {
    printf("Sorry, we are out of %s\n", slist[item].name);
  } else if (slist[item].cost <= money) {
    printf("You bought %s\n", slist[item].name);
    printf("You have $%.2f left\n", money - slist[item].cost);
  } else {
    printf("You can't afford it!\n");
  }

  printf("\n");
  return 0;
}
