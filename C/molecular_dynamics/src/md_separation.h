#ifndef MD_SEPARATION
#define MD_SEPARATION

#include <stdlib.h>
#include <math.h>
#include "particle.h"
#include "md_math.h"
#include "dbg.h"

typedef struct MD_Separation {
  double dx;
  double dy;
  double dz;
} MD_Separation;

MD_Separation * MD_new_Separation(Particle *, Particle *, double);
void MD_destroy_Separation(MD_Separation *);
void MD_toString_Separation(MD_Separation *);

double MD_calculate_SeparationMagnitude(MD_Separation *);

#endif
