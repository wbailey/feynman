#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "simulation.h"

//void initialize(ParticleCollection);

void initialize(ParticleCollection *collection) {
  collection[0]->x = 0.0;
  collection[0]->vx = 0.5;
  collection[1]->x = 6.0;
  collection[1]->vx = -0.5;
}

void euler(Particle *particle, double force, double dt) {
  particle->ax  = force;
  particle->vx += particle->ax * dt;
  particle->x  += particle->vx * dt;
}

int main(void) {
  double r, force;
  ParticleCollection *particle = new_ParticleCollection(MD_Collection_Size);

  initialize(particle);

  for (int i = 0; i < 100; i++) {
    r = abs(particle[0]->x - particle[1]->x);
    force = LJ_Force(r);

    euler(particle[0], force, dt);
    euler(particle[1], -force, dt);

    t += dt;

    printf("%12.6f %12.6f %12.6f %12.6f\n", t, force, particle[0]->x, particle[1]->x);
  }

  destroy_ParticleCollection(particle);
}
