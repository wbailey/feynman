#include <stdlib.h>
#include <assert.h>
#include "lennard_jones.h"
#include "md_accel.h"
#include "lennard_jones.h"

MD_Accel * new_MD_Accel(LennardJonesPotential *ljp, MD_Separation *sep) {
  struct MD_Accel *accel = malloc(sizeof(struct MD_Accel));
  double r = calculate_SeparationMagnitude(sep);
  double force = LennardJones_Force(ljp, r);

  accel->ax = -(sep->dx/r) * force;
  accel->ay = -(sep->dy/r) * force;
  accel->az = -(sep->dz/r) * force;

  return accel;
}

void destroy_MD_Accel(MD_Accel *accel) {
  assert(accel != NULL);
  free(accel);
}
