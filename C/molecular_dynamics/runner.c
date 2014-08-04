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
  double pe, ke;
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

    for (int m = 0; m < MD_Collection_Size - 1; m++) {
      for (int n = m + 1; n < MD_Collection_Size; n++) {
        sep   = MD_new_Separation(particle[m], particle[n], MD_Box_Length);

        MD_toString_Separation(sep);

        accel = MD_new_Accel(sep);

        pe += LJ_Potential_Energy(MD_calculate_R(sep));

        MD_iterate_Euler(particle[m], accel, dt);
        MD_thirdlaw_Accel(accel);
        MD_iterate_Euler(particle[n], accel, dt);

        MD_apply_Periodic(particle[m], MD_Box_Length);
        MD_apply_Periodic(particle[n], MD_Box_Length);

        MD_destroy_Separation(sep);
        MD_destroy_Accel(accel);
      }
    }

    // Euler iteration should be happening here after all of the accelerations
    // have been summed per particle

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
