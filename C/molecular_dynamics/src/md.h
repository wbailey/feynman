#ifndef MD_H
#define MD_H

#include "simulation.h"

double MD_Periodic(double, double, double);
void MD_Initialize(ParticleCollection *);
void MD_Euler(Particle *, double, double);

#endif
