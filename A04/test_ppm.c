#include <stdio.h>
#include "read_ppm.h"

int main() {

  // todo: call read_ppm
  int w, h;
  read_ppm("feep-ascii.ppm", &w, &h);

  return 0;
}

