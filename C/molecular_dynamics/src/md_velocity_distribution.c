#include <stdio.h>
#include <math.h>
#include "md_velocity_distribution.h"
#include "particle.h"

void report_Velocities(ParticleCollection *p, int collection_size, const char *filename) {
  FILE *fp = fopen(filename, "w");
  double v, vmax = -1.0;

  for (int i = 0; i < collection_size; i++) {
    v = sqrt(p[i]->vx * p[i]->vx + p[i]->vy * p[i]->vy + p[i]->vz * p[i]->vz);
    if (v > vmax) vmax = v;
    fprintf(fp, "%d %12.6f\n", i, v);
  }

  fprintf(fp, "vmax: %12.6f\n", vmax);

  fclose(fp);
}
