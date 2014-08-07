#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "lennard_jones.h"

LennardJonesPotential * new_LennardJonesPotential(double sigma, double epsilon) {
  LennardJonesPotential *ljp = malloc(sizeof(struct LennardJonesPotential));

  ljp->sigma = sigma;
  ljp->epsilon = epsilon;

  return ljp;
}

void destroy_LennardJonesPotential(LennardJonesPotential *ljp) {
  assert(ljp != NULL);
  free(ljp);
}

double LennardJones_R6(LennardJonesPotential *ljp, double r) {
  return pow(ljp->sigma/r, 6);
}

double LennardJones_R12(LennardJonesPotential *ljp, double r) {
  return pow(LennardJones_R6(ljp, r), 2);
}

double LennardJones_Force(LennardJonesPotential *ljp, double r) {
  assert(ljp->sigma != 0);
  assert(ljp->epsilon != 0);

  return -(24.0 * ljp->epsilon/r) * (2.0 * LennardJones_R12(ljp, r) - LennardJones_R6(ljp, r));
}

double LennardJones_PotentialEnergy(LennardJonesPotential *ljp, double r) {
  assert(ljp->sigma != 0);
  assert(ljp->epsilon != 0);

  return 4.0 * ljp->epsilon * (LennardJones_R12(ljp, r) - LennardJones_R6(ljp, r));
}
