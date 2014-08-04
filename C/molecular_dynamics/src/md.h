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
void MD_apply_Periodic(Particle *, double);
void MD_initialize_Collection(ParticleCollection *);

typedef struct MD_Accel {
  double ax;
  double ay;
  double az;
} MD_Accel;

MD_Accel * MD_new_Accel(MD_Separation *);
void MD_flipsign_Accel(MD_Accel *);
void MD_destroy_Accel(MD_Accel *);

void MD_iterate_Euler(Particle *, MD_Accel *, double);
double MD_calc_Kinetic_Energy(ParticleCollection *, int);

int MD_Sign(double);

#endif
