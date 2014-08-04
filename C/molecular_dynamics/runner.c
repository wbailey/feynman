#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "simulation.h"

typedef struct Report {
  double t;
  double r;
  double pe;
  double ke;
  double te;
  double v1;
  double v2;
  double v3;
  double v4;
} Report;

//void do_report(Report *);

void do_report(Report *report) {
  printf("%12.6f", report->t);
  printf("%12.6f", report->r);
  printf("%12.6f", report->pe);
  printf("%12.6f", report->ke);
  printf("%12.6f", report->te);
  printf("%12.6f", report->v1);
  printf("%12.6f", report->v2);
  printf("%12.6f", report->v3);
  printf("%12.6f", report->v4);
  printf("\n");
}

int main(void) {
  double r;
  double ax, ay, az, force;
  double pe, ke;
  ParticleCollection *particle = new_ParticleCollection(MD_Collection_Size);
  MD_Separation *sep;
  Report *report = malloc(sizeof(struct Report));

  MD_initialize_Collection(particle);

  for (int i = 0; i < MD_Iterations; i++) {
    pe = LJ_Potential_Energy(r);
    ke = 0.0;

    for (int m = 0; m < MD_Collection_Size - 1; m++) {
      for (int n = m + 1; n > MD_Collection_Size; n--) {
        sep   = MD_new_Separation(particle[m], particle[n], MD_Box_Length);
        r     = MD_calculate_R(sep);
        force = LJ_Force(r);

        ax = (sep->dx/r) * force;
        ay = (sep->dy/r) * force;
        az = (sep->dz/r) * force;

        ke += 0.5 * (particle[m]->vx * particle[m]->vx + particle[m]->vy * particle[m]->vy + particle[m]->vz * particle[m]->vz);
        ke += 0.5 * (particle[n]->vx * particle[n]->vx + particle[n]->vy * particle[n]->vy + particle[n]->vz * particle[n]->vz);

        MD_iterate_Euler(particle[m], ax, ay, az, dt);
        MD_iterate_Euler(particle[n], -ax, -ay, -az, dt);

        MD_apply_Periodic(particle[m], MD_Box_Length);
        MD_apply_Periodic(particle[n], MD_Box_Length);

        report->r  = r;
        report->v1 = sep->dx;
        report->v2 = sep->dy;
        report->v3 = particle[m]->x;
        report->v4 = particle[n]->x;
      }
    }

    t += dt;

    report->t = t;
    report->pe = pe;
    report->ke = ke;
    report->te = pe + ke;

    do_report(report);
  }

  destroy_ParticleCollection(particle);
}
