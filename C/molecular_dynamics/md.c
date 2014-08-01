#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "simulation.h"

int main(void) {
  printf("force: %12.6f\n", LJ_Force(LJ_Sigma));
  printf("potential energy: %12.6f\n", LJ_Potential_Energy(LJ_Sigma));
}
