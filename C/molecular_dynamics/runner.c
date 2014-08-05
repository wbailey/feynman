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
  Report *report = malloc(sizeof(struct Report));
  int report_interval = MD_Iterations/MD_ReportCount;

  MD_initialize_Collection(particle);

  report->collection      = particle;
  report->collection_size = MD_Collection_Size;

  for (int i = 0; i < MD_Iterations; i++) {
    pe = ke = 0.0;

    MD_reset_Collection_Accel(particle, MD_Collection_Size);

    // This odd function updates the acceleration for all of the particles and returns
    // the total potential energy calculated
    pe = MD_calc_Collection_Forces(particle, MD_Collection_Size);

    MD_iterate_Euler(particle, MD_Collection_Size);

    ke = MD_calc_Kinetic_Energy(particle, MD_Collection_Size);

    t += dt;

    if (i % report_interval == 0) {
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
