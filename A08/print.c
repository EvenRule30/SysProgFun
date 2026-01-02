#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "rand.h"

int main (int argc, char* argv[]) {
  void *p = sbrk(0);
  printf("The first is %p\n", p);
  void *q = sbrk(0);
  printf("The second is %p\n", q);
  long x = ((long)q)-(long)p;
  printf("Increased by %ld (%lx) bytes\n", x, x);
  return 0 ;
}
