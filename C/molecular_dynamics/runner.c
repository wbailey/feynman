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

  printf("%9.6f ", report->t);
  printf("%9.6f ", report->pe);
  printf("%9.6f ", report->ke);
  printf("%9.6f ", report->te);
  
  for (int i = 0; i < report->collection_size; i++) {
    printf("%9.6f %9.6f ", c[i]->x, c[i]->y);
    printf("%9.6f %9.6f ", c[i]->vx, c[i]->vy);
    printf("%9.6f %9.6f ", c[i]->ax, c[i]->ay);
  }

  printf("\n");
}

int main(void) {
  MD_SystemEnergy *energy;
  ParticleCollection *particle = new_ParticleCollection(MD_Collection_Size);
  Report *report = malloc(sizeof(struct Report));
  int report_interval = MD_Iterations/MD_ReportCount;

  MD_initialize_Collection(particle);

  report->collection      = particle;
  report->collection_size = MD_Collection_Size;

  MD_calc_Collection_Forces(particle, MD_Collection_Size);

  for (int i = 0; i < MD_Iterations; i++) {
    MD_iterate_VerletPosition(particle, MD_Collection_Size);
    MD_iterate_VerletVelocity(particle, MD_Collection_Size);

    MD_calc_Collection_Forces(particle, MD_Collection_Size);

    /*
    MD_iterate_Euler(particle, MD_Collection_Size);
    */

    MD_iterate_VerletVelocity(particle, MD_Collection_Size);

    energy = MD_calculate_SystemEnergy(particle, MD_Collection_Size, MD_Box_Length);

    t += dt;

    if (i % report_interval == 0) {
      report->t  = t;
      report->pe = energy->pe;
      report->ke = energy->ke;
      report->te = energy->te;
      print_Report(report);
    }
  }

  destroy_Report(report);
  destroy_ParticleCollection(particle);
}
