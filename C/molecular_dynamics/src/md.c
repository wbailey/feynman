#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "md.h"

double MD_Periodic(double pos1, double pos2, double length) {
  double separation = fabs(pos1 - pos2);
  double separation_periodic = fabs(separation - length);

  // Return the shortest distance between the points
  return separation < separation_periodic ? separation : separation_periodic;
}

void MD_Initialize(ParticleCollection *collection) {
  collection[0]->x  =  3.0;
  collection[0]->y  =  0.0;
  collection[0]->vx =  0.5;
  collection[0]->vy =  0.0;
  collection[1]->x  =  9.0;
  collection[1]->y  =  0.0;
  collection[1]->vx = -0.5;
  collection[1]->vy =  0.0;
}

void MD_Euler(Particle *particle, double ax, double ay, double dt) {
  particle->ax  = ax;
  particle->vx += particle->ax * dt;
  particle->x  += particle->vx * dt;

  particle->ay  = ay;
  particle->vy += particle->ay * dt;
  particle->y  += particle->vy * dt;
}

int main(void) {
  double dx, dy, r;
  double ax, ay, force;
  double pe, ke;
  ParticleCollection *particle = new_ParticleCollection(MD_Collection_Size);

  MD_Initialize(particle);

  for (int i = 0; i < MD_Iterations; i++) {
    dx = MD_Periodic(particle[0]->x, particle[1]->x, MD_Box_Length);
    dy = MD_Periodic(particle[0]->y, particle[1]->y, MD_Box_Length);

    r = sqrt(dx * dx + dy * dy);

    force = LJ_Force(r);

    ax = (dx/r) * force;
    ay = (dy/r) * force;

    pe = LJ_Potential_Energy(r);
    ke = 0.0;

    for (int j = 0; j < 2; j++) {
      ke += 0.5 * (particle[j]->vx * particle[j]->vx + particle[j]->vy * particle[j]->vy);
    }

    MD_Euler(particle[0], ax, ay, dt);
    MD_Euler(particle[1], -ax, -ay, dt);

    t += dt;

    printf("%12.6f %12.6f %12.6f %12.6f %12.6f %12.6f %12.6f %12.6f\n", t, ke + pe, pe, ke, particle[0]->x, particle[0]->y, particle[1]->x, particle[1]->y);
  }

  destroy_ParticleCollection(particle);
}
