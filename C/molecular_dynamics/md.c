#include <stdio.h>
#include <stdlib.h>
#include "lennard_jones.h"

int main(void) {
  printf("force: %12.6f\n", LJ_Force(5.0));
}
