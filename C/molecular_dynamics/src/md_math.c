#include "md_math.h"

int MD_Sign(double val) {
  return (val > 0) - (val < 0);
}

void MD_RandomSeed() {
  srand(time(NULL));
}

double MD_Random() {
  return (double) rand()/(double) RAND_MAX;
}

