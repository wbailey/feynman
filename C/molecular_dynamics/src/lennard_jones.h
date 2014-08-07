#ifndef LENNARD_JONES_H
#define LENNARD_JONES_H

typedef struct LennardJonesPotential {
  double sigma;
  double epsilon;
} LennardJonesPotential;

LennardJonesPotential * new_LennardJonesPotential(double, double);
void destroy_LennardJonesPotential(LennardJonesPotential *);

double LennardJones_R6(LennardJonesPotential *, double);
double LennardJones_R12(LennardJonesPotential *, double);
double LennardJones_Force(LennardJonesPotential *, double);
double LennardJones_PotentialEnergy(LennardJonesPotential *, double);

#endif
