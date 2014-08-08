#ifndef MD_SEPARATION
#define MD_SEPARATION

#include "particle.h"

typedef struct MD_Separation {
  double dx;
  double dy;
  double dz;
} MD_Separation;

MD_Separation * new_MD_Separation(Particle *, Particle *, double);
void destroy_MD_Separation(MD_Separation *);
void toString_MD_Separation(MD_Separation *);

double calculate_SeparationMagnitude(MD_Separation *);

#endif
