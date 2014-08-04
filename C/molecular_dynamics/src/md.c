#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "md.h"

double MD_calculate_R(MD_Separation *sep) {
  return sqrt(sep->dx * sep->dx + sep->dy * sep->dy + sep->dz * sep->dz);
}

MD_Separation * MD_new_Separation(Particle *p1, Particle *p2, double length) {
  struct MD_Separation *separation = malloc(sizeof(struct MD_Separation));
  double half = 0.5 * length;
  double dx, dy, dz;

  dx = p1->x - p2->x;
  dy = p1->y - p2->y;
  dz = p1->z - p2->z;

  if (fabs(dx) > half) dx -= MD_Sign(dx) * length;
  if (fabs(dy) > half) dy -= MD_Sign(dy) * length;
  if (fabs(dz) > half) dz -= MD_Sign(dz) * length;

  separation->dx = dx;
  separation->dy = dy;
  separation->dz = dz;

  return separation;
}

void MD_toString_Separation(MD_Separation *sep) {
  DEBUG_PRINT("dx: %12.8f dy: %12.8f dz: %12.8f", sep->dx, sep->dy, sep->dz);
}

void MD_destroy_Separation(MD_Separation *separation) {
  assert(separation != NULL);
  free(separation);
}

void MD_apply_Periodic(Particle *particle, double length) {
  if(particle->x < 0.0) {
    particle->x += length;
  } else if (particle->x > length) {
    particle->x -= length;
  }

  if(particle->y < 0.0) {
    particle->y += length;
  } else if (particle->y > length) {
    particle->y -= length;
  }

  if(particle->z < 0.0) {
    particle->z += length;
  } else if (particle->z > length) {
    particle->z -= length;
  }
}

void MD_iterate_Euler(Particle *particle, MD_Accel *accel, double dt) {
  particle->ax += accel->ax;
  particle->vx += particle->ax * dt;
  particle->x  += particle->vx * dt;

  particle->ay += accel->ay;
  particle->vy += particle->ay * dt;
  particle->y  += particle->vy * dt;

  particle->az += accel->az;
  particle->vz += particle->az * dt;
  particle->z  += particle->vz * dt;
}

MD_Accel * MD_new_Accel(MD_Separation *sep) {
  struct MD_Accel *accel = malloc(sizeof(struct MD_Accel));
  double r = MD_calculate_R(sep);
  double force = LJ_Force(r);

  accel->ax = -(sep->dx/r) * force;
  accel->ay = -(sep->dy/r) * force;
  accel->az = -(sep->dz/r) * force;

  return accel;
}

void MD_destroy_Accel(MD_Accel *accel) {
  assert(accel != NULL);
  free(accel);
}

void MD_thirdlaw_Accel(MD_Accel *accel) {
  accel->ax = -accel->ax;
  accel->ay = -accel->ay;
  accel->az = -accel->az;
}

void MD_reset_Collection_Accel(ParticleCollection *particle, int collection_size) {
  for (int i = 0; i < collection_size; i++) {
    particle[i]->ax = 0.0;
    particle[i]->ay = 0.0;
    particle[i]->az = 0.0;
  }
}

double MD_calc_Kinetic_Energy(ParticleCollection *particle, int collection_size) {
  double ke = 0.0;

  for (int i = 0; i < collection_size; i++) {
    ke += 
        particle[i]->vx * particle[i]->vx + 
        particle[i]->vy * particle[i]->vy +
        particle[i]->vz * particle[i]->vz;
  }

  ke *= 0.5;

  DEBUG_PRINT("ke: %12.8f", ke);

  return ke;
}

void MD_initialize_Collection(ParticleCollection *collection) {
  collection[0]->x  =  6.0;
  collection[0]->y  =  3.0;
  collection[0]->vx =  0.0;
  collection[0]->vy =  0.5;
  collection[1]->x  =  6.0;
  collection[1]->y  =  9.0;
  collection[1]->vx =  0.0;
  collection[1]->vy = -0.5;
  collection[2]->x  =  6.0;
  collection[2]->y  =  15.0;
  collection[2]->vx =  0.0;
  collection[2]->vy =  0.5;
}

int MD_Sign(double val) {
  return (val > 0) - (val < 0);
}
