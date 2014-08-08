#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#include "md_math.h"

int math_Sign(double val) {
  return (val > 0) - (val < 0);
}

void math_RandomSeed() {
  srand(time(NULL));
}

double math_Random() {
  return (double) rand()/(double) RAND_MAX;
}

