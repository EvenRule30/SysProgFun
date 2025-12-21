//---------------------------------------------------------------------
// sorted_snackbar.c 
// CS223 - Spring 2022
// Ask the user for a list of snacks and store them in alphabetical order
// Name:
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct snack {
  char name[32];
  int quantity;
  float cost;
  struct snack* next;
};

// Insert a new node to a list (implemented as a linked list). 
// The new node should store the given properties
// Param snacks: the first item in the list (NULL if empty)
// Param name: the snack name (max length is 32 characters)
// Param quantity: the snack quantity
// Param cost: the snack cost
// Returns the first item in the list
struct snack* insert_sorted(struct snack* snacks, 
  const char* name, int quantity, float cost) {
    struct snack *new = malloc(sizeof(struct snack));
    strcpy(new->name, name);
    new->quantity = quantity;
    new->cost = cost;
    new->next = NULL;

    // first snack in list
    if (!snacks) return new;

    // if new less than current snack
    if (strcmp(name, snacks->name) < 0) {
      new->next = snacks;
      return new;
    }

    struct snack *head = snacks;
    // gets to snack where next is larger than the new one
    while(snacks->next && strcmp(snacks->next->name, name) < 0) {
      snacks = snacks->next;
    }
    // put new snack after current snack
    struct snack *temp = snacks->next;
    snacks->next = new;
    new->next = temp;
  
    return head;
}

// Delete (e.g. free) all nodes in the given list of snacks
// Param snacks: the first node in the list (NULL if empty)
void clear(struct snack* snacks) {
  if (!snacks) return;
  if (!snacks->next) {
    free(snacks);
    return;
  }
  struct snack *temp = snacks->next;
  while (temp) {
    free(snacks);
    snacks = temp;
    temp = snacks->next;
  }
  free(snacks);
  snacks = NULL;
  temp = NULL;
  return;
}

int main() {
  int num;

  printf("Enter a number of snacks: ");
  scanf("%d", &num);
  if (num < 1) return 0;

  char *name = malloc(sizeof(char)*32);
  float cost;
  int quantity;
  struct snack *lst = NULL;

  for (int i = 0; i < num; i++) {
    printf("Enter a name: ");
    scanf("%s", name);
    printf("Enter a cost: ");
    scanf("%f", &cost);
    printf("Enter a quantity: ");
    scanf("%d", &quantity);
    lst = insert_sorted(lst, name, quantity, cost);
  }

  printf("\nWelcome to Sorted Sally's Snack Bar\n\n");
  for (int i = 0; i < num; ++i) {
    printf("%d) %s \t\t cost: $%.2f \t\t quantity: %d\n", i, lst->name, lst->cost, lst->quantity);
    lst = lst->next;
  }

  clear(lst);

  return 0;
}
