#ifndef MD_H
#define MD_H

#include "lennard_jones.h"
#include "particle.h"

extern double LJ_Epsilon; // kJ/mol
extern double LJ_Sigma;    // Angstroms

extern double t;
extern double dt;

extern double MD_Collection_Size;
extern double MD_Box_Length;

extern int MD_Iterations;

double MD_Periodic(double, double, double);
void MD_Initialize(ParticleCollection *);
void MD_Euler(Particle *, double, double, double);

#endif
