#include "lennard_jones.h"

double LJ_R6(double r) {
  return pow(LJ_Sigma/r, 6);
}

double LJ_R12(double r) {
  return pow(LJ_R6(r), 2);
}

double LJ_Force(double r) {
  assert(LJ_Epsilon != 0);
  assert(LJ_Sigma != 0);

  return -(24.0 * LJ_Epsilon/r) * (2.0 * LJ_R12(r) - LJ_R6(r));
}

double LJ_Potential_Energy(double r) {
  assert(LJ_Epsilon != 0);
  assert(LJ_Sigma != 0);

  return 4.0 * LJ_Epsilon * (LJ_R12(r) - LJ_R6(r));
}
