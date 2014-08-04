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

typedef struct MD_Separation {
  double dx;
  double dy;
  double dz;
} MD_Separation;

MD_Separation * MD_new_Separation(Particle *, Particle *, double);
void MD_destroy_Separation(MD_Separation *);

double MD_calculate_R(MD_Separation *);

//double MD_calculate_Separation(double, double, double);
void MD_apply_Periodic(Particle *, double);
void MD_initialize_Collection(ParticleCollection *);
void MD_iterate_Euler(Particle *, double, double, double, double);

#endif
