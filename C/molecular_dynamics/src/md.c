#include <math.h>
#include "md.h"

double MD_Periodic(double pos1, double pos2, double length) {
  double separation = fabs(pos1 - pos2);
  double separation_periodic = fabs(separation - length);

  // Return the shortest distance between the points
  return separation < separation_periodic ? separation : separation_periodic;
}

void MD_Euler(Particle *particle, double ax, double ay, double dt) {
  particle->ax  = ax;
  particle->vx += particle->ax * dt;
  particle->x  += particle->vx * dt;

  particle->ay  = ay;
  particle->vy += particle->ay * dt;
  particle->y  += particle->vy * dt;
}

void MD_Initialize(ParticleCollection *collection) {
  collection[0]->x  =  3.0;
  collection[0]->y  =  6.0;
  collection[0]->vx =  0.5;
  collection[0]->vy =  0.0;
  collection[1]->x  =  9.0;
  collection[1]->y  =  6.0;
  collection[1]->vx = -0.5;
  collection[1]->vy =  0.0;
}

