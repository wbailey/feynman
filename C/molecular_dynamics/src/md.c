#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "md.h"

double MD_calculate_SeparationMagnitude(MD_Separation *sep) {
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

void MD_iterate_VerletPosition(ParticleCollection *particle, int collection_size, double length) {
  for (int m = 0; m < collection_size; m++) {
    particle[m]->x += particle[m]->vx * dt + 0.5 * particle[m]->ax * dt * dt;
    particle[m]->y += particle[m]->vy * dt + 0.5 * particle[m]->ay * dt * dt;
    particle[m]->z += particle[m]->vz * dt + 0.5 * particle[m]->az * dt * dt;

    MD_apply_Periodic(particle[m], length);
  }
}

void MD_iterate_VerletVelocity(ParticleCollection *particle, int collection_size) {
  for (int m = 0; m < collection_size; m++) {
    particle[m]->vx += 0.5 * particle[m]->ax * dt;
    particle[m]->vy += 0.5 * particle[m]->ay * dt;
    particle[m]->vz += 0.5 * particle[m]->az * dt;
  }
}

void MD_iterate_Euler(ParticleCollection *particle, int collection_size, double length) {
  for (int m = 0; m < collection_size; m++) {
    particle[m]->vx += particle[m]->ax * dt;
    particle[m]->vy += particle[m]->ay * dt;
    particle[m]->vz += particle[m]->az * dt;

    particle[m]->x  += particle[m]->vx * dt;
    particle[m]->y  += particle[m]->vy * dt;
    particle[m]->z  += particle[m]->vz * dt;

    MD_apply_Periodic(particle[m], length);
  }
}

MD_Accel * MD_new_Accel(MD_Separation *sep) {
  struct MD_Accel *accel = malloc(sizeof(struct MD_Accel));
  double r = MD_calculate_SeparationMagnitude(sep);
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

void MD_reset_Collection_Accel(ParticleCollection *particle, int collection_size) {
  for (int i = 0; i < collection_size; i++) {
    particle[i]->ax = 0.0;
    particle[i]->ay = 0.0;
    particle[i]->az = 0.0;
  }
}

void MD_calculate_Forces(ParticleCollection *particle, int collection_size, double length) {
  MD_Separation *sep;
  MD_Accel *accel;

  for (int i = 0; i < collection_size; i++) {
    particle[i]->ax = 0.0;
    particle[i]->ay = 0.0;
    particle[i]->az = 0.0;
  }

  for (int m = 0; m < MD_CollectionSize - 1; m++) {
    for (int n = m + 1; n < MD_CollectionSize; n++) {
      sep = MD_new_Separation(particle[m], particle[n], length);
      accel = MD_new_Accel(sep); // calculates (dx/r)*force

      particle[m]->ax += accel->ax;
      particle[m]->ay += accel->ay;
      particle[m]->az += accel->az;

      particle[n]->ax -= accel->ax;
      particle[n]->ay -= accel->ay;
      particle[n]->az -= accel->az;

      MD_destroy_Separation(sep);
      MD_destroy_Accel(accel);
    }
  }
}

MD_SystemEnergy * MD_new_SystemEnergy() {
  struct MD_SystemEnergy *system = malloc(sizeof(struct MD_SystemEnergy));

  system->pe = 0.0;
  system->ke = 0.0;
  system->te = 0.0;

  return system;
}

void MD_destroy_SystemEnergy(MD_SystemEnergy *system) {
  assert(system != NULL);
  free(system);
}

MD_SystemEnergy * MD_calculate_SystemEnergy(ParticleCollection *particle, int collection_size, int length) {
  double pe, ke, r;
  MD_Separation *sep;
  MD_SystemEnergy *system = MD_new_SystemEnergy();
  
  pe = ke = 0.0;

  for (int i = 0; i < collection_size; i++) {
    ke += 
        particle[i]->vx * particle[i]->vx + 
        particle[i]->vy * particle[i]->vy +
        particle[i]->vz * particle[i]->vz;
    if (i < collection_size - 1) {
      for (int j = i + 1; j < collection_size; j++) {
        sep = MD_new_Separation(particle[i], particle[j], length);
        r = MD_calculate_SeparationMagnitude(sep);
        pe += LJ_Potential_Energy(r);
      }
    }
  }

  ke *= 0.5;

  system->pe = pe;
  system->ke = ke;
  system->te = pe + ke;

  DEBUG_PRINT("pe: %12.8f ke: %12.8f te: %12.8f", pe, ke, system->te);

  return system;
}

double MD_initialize_Collection(ParticleCollection *p, int collection_size, double sigma) {
  int Nx = sqrt(collection_size);
  double x, y, vmax;
  double length;

  x = y = sigma;

  MD_RandomSeed();
  vmax = 0.1; // relate to temperature going forward

  for (int i = 0; i < collection_size; i++) {
    p[i]->x = x;
    p[i]->y = y;

    p[i]->vx = vmax * (2 * MD_Random() - 1.0);
    p[i]->vy = vmax * (2 * MD_Random() - 1.0);

    DEBUG_PRINT("%d %8.4f %8.4f %12.6f %12.6f", Nx, x, y, p[i]->vx, p[i]->vy);

    x += 2 * sigma;

    if ( (i - 1) % Nx == 0) {
      y += 2 * sigma;
      x = sigma;
      DEBUG_PRINT("switch: %d %8.4f %8.4f", i, x, y);
    }
  }

  // Calculate the center of mass
  double vxcum, vycum;
  vxcum = vycum = 0.0;

  for (int i = 0; i < collection_size; i++) {
    vxcum += p[i]->vx;
    vycum += p[i]->vy;
  }

  vxcum = vxcum/(double) collection_size;
  vycum = vycum/(double) collection_size;

  for (int i = 0; i < collection_size; i++) {
    p[i]->vx -= vxcum;
    p[i]->vy -= vycum;

    DEBUG_PRINT("%12.6f %12.6f %12.6f %12.6f", p[i]->x, p[i]->y, p[i]->vx, p[i]->vy);
  }

  length = sigma * (2 * Nx);

  DEBUG_PRINT("box length: %12.6f", length);

  return length;
}

int MD_Sign(double val) {
  return (val > 0) - (val < 0);
}

void MD_RandomSeed() {
  srand(time(NULL));
}

double MD_Random() {
  return (double) rand()/(double) RAND_MAX;
}

MD_Report * MD_new_Report() {
  struct MD_Report *report = malloc(sizeof(struct MD_Report));
  return report;
}

void MD_destroy_Report(MD_Report *report) {
  assert(report != NULL);
  free(report);
}

void MD_print_Report(MD_Report *report) {
  ParticleCollection *c = report->collection;

  printf("%9.6f ", report->t);
  printf("%9.6f ", report->pe);
  printf("%9.6f ", report->ke);
  printf("%9.6f ", report->te);
  
  for (int i = 0; i < report->collection_size; i++) {
    printf("%9.6f %9.6f ", c[i]->x, c[i]->y);
  }

  printf("\n");
}

