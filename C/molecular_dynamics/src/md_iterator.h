#ifndef MD_ITERATOR
#define MD_ITERATOR

#include "particle.h"

typedef void (*MD_pbc)(Particle *, double);

void euler_Iterate(ParticleCollection *, int, double, double, MD_pbc);

void verlet_IteratePosition(ParticleCollection *, int, double, double, MD_pbc);
void verlet_IterateVelocity(ParticleCollection *, int, double);

#endif
