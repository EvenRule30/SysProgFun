//---------------------------------------------------------------------
// match_braces.c 
// CS223 - Spring 2022
// Identify matched braces from a given file
// Name:
//
#include <stdio.h>
#include <stdlib.h>

struct node {
  char sym;
  int linenum;
  int colnum;
  struct node* next;
};

// Push a new node to a stack (implemented as a linked list). 
// The new node should store the given symbol, line number, and column number
// Param sym: a character symbol, '{' for this program
// Param line: the line number of the symbol
// Param col: the column number of the symbol
// Param top: the top node of the stack (NULL if empty)
// Returns the new top of the stack
struct node* push(char sym, int line, int col, struct node* top) {
  struct node *new = malloc(sizeof(struct node));
  if (!new) {
    printf("Malloc failed.\n");
    exit(1);
  }
  new->sym = sym;
  new->linenum = line;
  new->colnum = col;
  new->next = top;
  return new;
}

// Pop the top node from a stack (implemented as a linked list) and frees it
// Param top: the top node of the current stack (NULL if empty)
// Returns the new top of the stack
struct node* pop(struct node* top) {
  if (!top) {
    printf("Warning: Called pop on an empty stack.\n");
    exit(2);
  }
  struct node *temp = top->next;
  free(top);
  return temp;
}

// Delete (e.g. free) all nodes in the given stack
// Param top: the top node of the stack (NULL if empty)
void clear(struct node* top) {
  while (top) top = pop(top);
}

// Print all nodes in the given stack (from top to bottom)
// Param top: the top node of the stack (NULL if empty)
void print(struct node* top) {
  while (top) {
    printf("{");
    top = pop(top);
  }
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("usage: ");
    for (int i = 0; i < argc; i++) printf("%s", argv[i]);
    printf("\n");
  }

  FILE *fptr = fopen(argv[1], "r");
  if (!fptr) {
    if (argv[1]) printf("Cannot open file: %s\n", argv[1]);
    exit(3);
  }

  char c = fgetc(fptr);
  struct node *stack = NULL;
  int line = 1, col = 1;
  while (c != EOF) {
    if (c == '{') stack = push(c, line, col, stack);
    if (c == '}') {
      if (!stack) {
        printf("Unmatched brace on Line %d and Column %d\n", line, col);
      } else {
        printf("Found matching braces: (%d, %d) -> (%d, %d)\n", stack->linenum, stack->colnum, line, col);
        stack = pop(stack);
      }
    }
    col++;
    if (c == '\n') {
      line++;
      col = 1;
    }
    c = fgetc(fptr);
  }

  while (stack) {
    printf("Unmatched brace on Line %d and Column %d\n", stack->linenum, stack->colnum);
    stack = pop(stack);
  }

  clear(stack);
  fclose(fptr);
  fptr = NULL;
  return 0;
}
