#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "md.h"

double MD_calculate_R(MD_Separation *sep) {
  return sqrt(sep->dx * sep->dx + sep->dy * sep->dy + sep->dz * sep->dz);
}

MD_Separation * MD_new_Separation(Particle *p1, Particle *p2, double length) {
  struct MD_Separation *separation = malloc(sizeof(struct MD_Separation));
  double dx, dy, dz;
  double sdx, sdy, sdz;

  dx = fabs(p1->x - p2->x);
  dy = fabs(p1->y - p2->y);
  dz = fabs(p1->z - p2->z);

  sdx = fabs(length - dx);
  sdy = fabs(length - dy);
  sdz = fabs(length - dz);

  separation->dx = dx < sdx ? dx : sdx;
  separation->dy = dy < sdy ? dy : sdy;
  separation->dz = dz < sdz ? dz : sdz;

  return separation;
}

void MD_destroy_Separation(MD_Separation *separation) {
  assert(separation != NULL);
  free(separation);
}

/*
double MD_calculate_Separation(double pos1, double pos2, double length) {
  double separation = fabs(pos1 - pos2);
  double separation_periodic = fabs(separation - length);

  // Return the shortest distance between the points
  return separation < separation_periodic ? separation : separation_periodic;
}
*/

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

void MD_iterate_Euler(Particle *particle, double ax, double ay, double az, double dt) {
  particle->ax  = ax;
  particle->vx += particle->ax * dt;
  particle->x  += particle->vx * dt;

  particle->ay  = ay;
  particle->vy += particle->ay * dt;
  particle->y  += particle->vy * dt;

  particle->az  = az;
  particle->vz += particle->az * dt;
  particle->z  += particle->vz * dt;
}

void MD_initialize_Collection(ParticleCollection *collection) {
  collection[0]->x  =  3.0;
  collection[0]->y  =  6.0;
  collection[0]->vx =  0.5;
  collection[0]->vy =  0.0;
  collection[1]->x  =  9.0;
  collection[1]->y  =  6.0;
  collection[1]->vx = -0.5;
  collection[1]->vy =  0.0;
}

