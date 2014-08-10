#ifndef MD_H
#define MD_H

#include "particle.h"
#include "lennard_jones.h"

typedef struct MD_BoxParameters {
  int Nx;
  int Ny;
  int Nz;
  double spacing;
  double vmax;
} MD_BoxParameters;

typedef struct MD_RunParameters {
  double t;
  double dt;
  int iterations;
  int equilibrium;
  int report_count;
} MD_RunParameters;

MD_RunParameters * new_MD_RunParameters(double, double, int, int, int);
void destroy_MD_RunParameters(MD_RunParameters *);

MD_BoxParameters * new_MD_BoxParameters(int, int, int, double, double);
void destroy_MD_BoxParameters(MD_BoxParameters *);

void apply_Periodic(Particle *, double);
double initialize_Collection(ParticleCollection *, MD_BoxParameters *);
void calculate_Forces(LennardJonesPotential *, ParticleCollection *, int, double);

#endif
