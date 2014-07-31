#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "lennard_jones.h"

double LJ_Force(double r) {
  double force, r6, r12;

  assert(LJ_Epsilon != 0);
  assert(LJ_Sigma != 0);

  r6 = pow(LJ_Sigma/r, 6);
  r12 = pow(r6, 2);

  force = -(24.0 * LJ_Epsilon/r) * (2.0 * r12 - r6);

  return force;
}
