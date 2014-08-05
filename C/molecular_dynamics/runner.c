#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "simulation.h"

typedef struct Report {
  double t;
  double pe;
  double ke;
  double te;
  ParticleCollection *collection;
  int collection_size;
} Report;

void destroy_Report(Report *report) {
  assert(report != NULL);
  free(report);
}

void print_Report(Report *report) {
  ParticleCollection *c = report->collection;

  printf("%12.6f ", report->t);
  printf("%12.6f ", report->pe);
  printf("%12.6f ", report->ke);
  printf("%12.6f ", report->te);
  
  for (int i = 0; i < report->collection_size; i++) {
    printf("%12.8f %12.8f ", c[i]->x, c[i]->y);
  }

  printf("\n");
}

int main(void) {
  double r, pe, ke;
  ParticleCollection *particle = new_ParticleCollection(MD_Collection_Size);
  MD_Separation *sep;
  MD_Accel *accel;
  Report *report = malloc(sizeof(struct Report));
  int interval = MD_Iterations/MD_ReportCount;

  MD_initialize_Collection(particle);

  report->collection  = particle;
  report->collection_size = MD_Collection_Size;

  for (int i = 0; i < MD_Iterations; i++) {
    pe = ke = 0.0;

    MD_reset_Collection_Accel(particle, MD_Collection_Size);

    // Calculate the cumalative force on each particle
    for (int m = 0; m < MD_Collection_Size - 1; m++) {
      for (int n = m + 1; n < MD_Collection_Size; n++) {
        sep = MD_new_Separation(particle[m], particle[n], MD_Box_Length);
        r = MD_calculate_R(sep);

        accel = MD_new_Accel(sep);

        pe += LJ_Potential_Energy(r);

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

    for (int m = 0; m < MD_Collection_Size; m++) {
      particle[m]->vx += particle[m]->ax * dt;
      particle[m]->vy += particle[m]->ay * dt;
      particle[m]->vz += particle[m]->az * dt;

      particle[m]->x  += particle[m]->vx * dt;
      particle[m]->y  += particle[m]->vy * dt;
      particle[m]->z  += particle[m]->vz * dt;

      MD_apply_Periodic(particle[m], MD_Box_Length);
    }

    t += dt;
    ke = MD_calc_Kinetic_Energy(particle, MD_Collection_Size);

    if (i % interval == 0) {
      report->t  = t;
      report->pe = pe;
      report->ke = ke;
      report->te = pe + ke;
      print_Report(report);
    }
  }

  destroy_Report(report);
  destroy_ParticleCollection(particle);
}
