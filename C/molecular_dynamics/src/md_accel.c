#include "md_accel.h"

MD_Accel * MD_new_Accel(MD_Separation *sep) {
  struct MD_Accel *accel = malloc(sizeof(struct MD_Accel));
  double r = MD_calculate_SeparationMagnitude(sep);
  double force = LJ_Force(r);

  accel->ax = -(sep->dx/r) * force;
  accel->ay = -(sep->dy/r) * force;
  accel->az = -(sep->dz/r) * force;

  return accel;
}

void MD_destroy_Accel(MD_Accel *accel) {
  assert(accel != NULL);
  free(accel);
}
