#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "md_separation.h"
#include "md_math.h"
#include "dbg.h"

MD_Separation * MD_new_Separation(Particle *p1, Particle *p2, double length) {
  struct MD_Separation *separation = malloc(sizeof(struct MD_Separation));
  double half = 0.5 * length;
  double dx, dy, dz;

  dx = p1->x - p2->x;
  dy = p1->y - p2->y;
  dz = p1->z - p2->z;

  if (fabs(dx) > half) dx -= MD_Sign(dx) * length;
  if (fabs(dy) > half) dy -= MD_Sign(dy) * length;
  if (fabs(dz) > half) dz -= MD_Sign(dz) * length;

  separation->dx = dx;
  separation->dy = dy;
  separation->dz = dz;

  return separation;
}

void MD_destroy_Separation(MD_Separation *separation) {
  assert(separation != NULL);
  free(separation);
}

void MD_toString_Separation(MD_Separation *sep) {
  DEBUG_PRINT("dx: %12.8f dy: %12.8f dz: %12.8f", sep->dx, sep->dy, sep->dz);
}

double MD_calculate_SeparationMagnitude(MD_Separation *sep) {
  return sqrt(sep->dx * sep->dx + sep->dy * sep->dy + sep->dz * sep->dz);
}

