#ifndef MD_H
#define MD_H

#include "dbg.h"
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
void MD_toString_Separation(MD_Separation *);

double MD_calculate_R(MD_Separation *);

void MD_apply_Periodic(Particle *, double);

void MD_initialize_Collection(ParticleCollection *);
void MD_reset_Collection_Accel(ParticleCollection *, int);
void MD_calc_Collection_Forces(ParticleCollection *, int);

typedef struct MD_Accel {
  double ax;
  double ay;
  double az;
} MD_Accel;

MD_Accel * MD_new_Accel(MD_Separation *);
void MD_destroy_Accel(MD_Accel *);

void MD_iterate_Euler(ParticleCollection *, int);

void MD_iterate_VerletPosition(ParticleCollection *, int);
void MD_iterate_VerletVelocity(ParticleCollection *, int);

typedef struct MD_SystemEnergy {
  double pe;
  double ke;
  double te;
} MD_SystemEnergy;

MD_SystemEnergy * MD_new_SystemEnergy();
void MD_destroy_SystemEnergy(MD_SystemEnergy *);
MD_SystemEnergy * MD_calculate_SystemEnergy(ParticleCollection *, int, int);

int MD_Sign(double);

#endif
