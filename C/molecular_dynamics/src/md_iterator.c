#include "particle.h"
#include "md_iterator.h"

void verlet_IteratePosition(ParticleCollection *particle, int collection_size, double dt, double length, MD_pbc pbc) {
  for (int m = 0; m < collection_size; m++) {
    particle[m]->x += particle[m]->vx * dt + 0.5 * particle[m]->ax * dt * dt;
    particle[m]->y += particle[m]->vy * dt + 0.5 * particle[m]->ay * dt * dt;
    particle[m]->z += particle[m]->vz * dt + 0.5 * particle[m]->az * dt * dt;

    pbc(particle[m], length);
  }
}

void verlet_IterateVelocity(ParticleCollection *particle, int collection_size, double dt) {
  for (int m = 0; m < collection_size; m++) {
    particle[m]->vx += 0.5 * particle[m]->ax * dt;
    particle[m]->vy += 0.5 * particle[m]->ay * dt;
    particle[m]->vz += 0.5 * particle[m]->az * dt;
  }
}

void euler_Iterate(ParticleCollection *particle, int collection_size, double dt, double length, MD_pbc pbc) {
  for (int m = 0; m < collection_size; m++) {
    particle[m]->vx += particle[m]->ax * dt;
    particle[m]->vy += particle[m]->ay * dt;
    particle[m]->vz += particle[m]->az * dt;

    particle[m]->x  += particle[m]->vx * dt;
    particle[m]->y  += particle[m]->vy * dt;
    particle[m]->z  += particle[m]->vz * dt;

    pbc(particle[m], length);
  }
}


