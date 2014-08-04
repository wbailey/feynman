#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "simulation.h"

typedef struct Report {
  double t;
  double r;
  double pe;
  double ke;
  double te;
  double force;
  Particle *p;
  Particle *o;
  Particle *n;
} Report;

void destroy_Report(Report *report) {
  assert(report != NULL);
  free(report);
}

void print_Report(Report *report) {
  printf("%12.6f", report->t);
  printf("%12.6f", report->r);
  printf("%12.6f", report->force);
  printf("%12.6f", report->pe);
  printf("%12.6f", report->ke);
  printf("%12.6f", report->te);
  printf("%12.6f", report->p->x);
  printf("%12.6f", report->p->y);
  printf("%12.6f", report->p->vx);
  printf("%12.6f", report->p->ax);
  printf("%12.6f", report->o->x);
  printf("%12.6f", report->o->y);
  printf("%12.6f", report->o->vx);
  printf("%12.6f", report->o->ax);
  printf("%12.6f", report->n->x);
  printf("%12.6f", report->n->y);
  printf("%12.6f", report->n->vx);
  printf("%12.6f", report->n->ax);
  printf("\n");
}

int main(void) {
  double pe, ke;
  ParticleCollection *particle = new_ParticleCollection(MD_Collection_Size);
  MD_Separation *sep;
  MD_Accel *accel;
  Report *report = malloc(sizeof(struct Report));

  MD_initialize_Collection(particle);

  for (int i = 0; i < MD_Iterations; i++) {
    pe = ke = 0.0;

    MD_reset_Collection_Accel(particle, MD_Collection_Size);

    for (int m = 0; m < MD_Collection_Size - 1; m++) {
      for (int n = m + 1; n < MD_Collection_Size; n++) {
        sep   = MD_new_Separation(particle[m], particle[n], MD_Box_Length);
        accel = MD_new_Accel(sep);

        pe += LJ_Potential_Energy(MD_calculate_R(sep));

        MD_iterate_Euler(particle[m], accel, dt);
        MD_thirdlaw_Accel(accel);
        MD_iterate_Euler(particle[n], accel, dt);

        MD_apply_Periodic(particle[m], MD_Box_Length);
        MD_apply_Periodic(particle[n], MD_Box_Length);

        report->r     = MD_calculate_R(sep);
        report->force = LJ_Force(MD_calculate_R(sep));
        report->p     = particle[m];
        report->o     = particle[n];

        MD_destroy_Separation(sep);
        MD_destroy_Accel(accel);
      }
    }

    t += dt;
    ke = MD_calc_Kinetic_Energy(particle, MD_Collection_Size);

    report->t = t;
    report->pe = pe;
    report->ke = ke;
    report->te = pe + ke;

    print_Report(report);

  }

  destroy_Report(report);
  destroy_ParticleCollection(particle);
}
