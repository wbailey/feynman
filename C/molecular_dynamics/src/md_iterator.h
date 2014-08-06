#ifndef MD_ITERATOR
#define MD_ITERATOR

#include "particle.h"

typedef void (*MD_pbc)(Particle *, double);

void MD_iterate_Euler(ParticleCollection *, int, double, double, MD_pbc);

void MD_iterate_VerletPosition(ParticleCollection *, int, double, double, MD_pbc);
void MD_iterate_VerletVelocity(ParticleCollection *, int, double);

#endif
