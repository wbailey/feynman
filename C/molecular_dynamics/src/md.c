#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "md.h"
#include "md_math.h"
#include "md_separation.h"
#include "md_accel.h"
#include "lennard_jones.h"
#include "dbg.h"

MD_Parameters * new_MD_Parameters(double t, double dt, int pc, int itr, int eqi, int rc) {
  MD_Parameters *mdp = malloc(sizeof(struct MD_Parameters));

  mdp->t = t;
  mdp->dt = dt;
  mdp->particle_count = pc;
  mdp->iterations = itr;
  mdp->equilibrium = eqi;
  mdp->report_count = rc;

  return mdp;
}

void destroy_MD_Parameters(MD_Parameters *mdp) {
  assert(mdp != NULL);
  free(mdp);
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

void MD_calculate_Forces(LennardJonesPotential *ljp, ParticleCollection *particle, int collection_size, double length) {
  MD_Separation *sep;
  MD_Accel *accel;

  for (int i = 0; i < collection_size; i++) {
    particle[i]->ax = 0.0;
    particle[i]->ay = 0.0;
    particle[i]->az = 0.0;
  }

  for (int m = 0; m < collection_size - 1; m++) {
    for (int n = m + 1; n < collection_size; n++) {
      sep = MD_new_Separation(particle[m], particle[n], length);
      accel = MD_new_Accel(ljp, sep); // calculates (dx/r)*force

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

double MD_initialize_Collection(ParticleCollection *p, int collection_size, double sigma) {
  int Nx, Ny;
  int c, d;
  double x, y, vmax;
  double length;

  x = y = sigma;

  MD_RandomSeed();
  vmax = 2.1; // relate to temperature going forward

  /*
   * Given a number N we need to compute the number of rows and columns
   * making up a grid that supports the remainder.  Consider the following:
   *
   * NOTE: integer math
   *
   * Nx * Ny + c = N
   *
   * and
   *
   * (Nx + 1) * (Ny + 1) - d = N
   *
   * solving for c and d yields:
   *
   * c = N - Nx * Ny
   * d = 2 * sqrt(N) + 1 - c
   *
   * Consider the example:
   *
   * N = 15
   *
   * (3)^2 + 6 = 15
   * (4)^2 - 1 = 15
   *
   * so Nx=3, Ny=3, c=6 and d=1.  When c > d then we add 1 to Nx and Ny and go until
   * we have layed out 15 particles.
   *
   * Consider the next example:
   *
   * N = 17
   *
   * (4)^2 + 1 = 17
   * (5)^2 - 8 = 17
   *
   * so Nx=4 and Ny=4, c=1 and d=8.  When d > c then we choose Nx = 5 and Ny = 4 and
   * stop when we have layed out 17 particles.
   *
   * The formulas and conditionals below implement this logic.
   */

  Ny = Nx = sqrt(collection_size);

  c = collection_size - Nx * Nx;
  d = 2 * Nx + 1 - c;

  DEBUG_PRINT("collection size: %d Nx: %d Ny: %d c: %d d: %d", collection_size, Nx, Ny, c, d);

  if (c == 0) {
    // do nothing on purpose
  } else if (c < d) {
    Nx += 1;
  } else {
    Nx += 1;
    Ny += 1;
  }

  int i = 0;

  for (int m = 0; m < Nx; m++) {
    for (int n = 0; n < Ny; n++) {
      if (i > collection_size - 1) break;

      p[i]->x = x;
      p[i]->y = y;

      p[i]->vx = vmax * (2 * MD_Random() - 1.0);
      p[i]->vy = vmax * (2 * MD_Random() - 1.0);

      DEBUG_PRINT("%d %d %8.4f %8.4f %12.6f %12.6f",i, Nx, x, y, p[i]->vx, p[i]->vy);

      y += 2.0 * sigma;

      i++;
    }
    x += 2.0 * sigma;
    y = sigma;
  }

  // Calculate the velocity drift
  double vxcum, vycum;
  vxcum = vycum = 0.0;

  for (int i = 0; i < collection_size; i++) {
    vxcum += p[i]->vx;
    vycum += p[i]->vy;
  }

  vxcum = vxcum/(double) collection_size;
  vycum = vycum/(double) collection_size;

  DEBUG_PRINT("vxcum: %12.6f vycum: %12.6f", vxcum, vycum);

  for (int i = 0; i < collection_size; i++) {
    p[i]->vx -= vxcum;
    p[i]->vy -= vycum;

    DEBUG_PRINT("%12.6f %12.6f %12.6f %12.6f", p[i]->x, p[i]->y, p[i]->vx, p[i]->vy);
  }

  length = sigma * (2 * Nx);

  DEBUG_PRINT("box length: %12.6f", length);

  return length;
}
