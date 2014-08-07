#ifndef MD_H
#define MD_H

#include "particle.h"
#include "lennard_jones.h"

typedef struct MD_Parameters {
  double t;
  double dt;
  int particle_count;
  int iterations;
  int equilibrium;
  int report_count;
} MD_Parameters;

MD_Parameters * new_MD_Parameters(double, double, int, int, int, int);
void destroy_MD_Parameters(MD_Parameters *);

void MD_apply_Periodic(Particle *, double);
double MD_initialize_Collection(ParticleCollection *, int, double);
void MD_calculate_Forces(LennardJonesPotential *, ParticleCollection *, int, double);

#endif
