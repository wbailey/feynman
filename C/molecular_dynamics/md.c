#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "simulation.h"

double MD_Periodic(double pos1, double pos2, double length) {
  double separation = fabs(pos1 - pos2);
  double separation_periodic = fabs(separation - length);

  // Return the shortest distance between the points
  return separation < separation_periodic ? separation : separation_periodic;
}

void MD_Initialize(ParticleCollection *collection) {
  collection[0]->x  = 3.0;
  collection[0]->vx = 0.5;
  collection[1]->x  = 9.0;
  collection[1]->vx = -0.5;
}

void MD_Euler(Particle *particle, double force, double dt) {
  particle->ax  = force;
  particle->vx += particle->ax * dt;
  particle->x  += particle->vx * dt;
}

int main(void) {
  double r, force;
  ParticleCollection *particle = new_ParticleCollection(particle_count);

  MD_Initialize(particle);

  for (int i = 0; i < iterations; i++) {
    r = MD_Periodic(particle[0]->x, particle[1]->x, MD_BoxLength);
    force = LJ_Force(r);

    MD_Euler(particle[0], force, dt);
    MD_Euler(particle[1], -force, dt);

    t += dt;

    printf("%12.6f %12.6f %12.6f %12.6f %12.6f %12.6f\n", t, r, particle[0]->x, particle[0]->y, particle[1]->x, particle[1]->y);
  }

  destroy_ParticleCollection(particle);
}
