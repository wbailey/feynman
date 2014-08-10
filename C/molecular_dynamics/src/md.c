#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "md.h"
#include "md_math.h"
#include "md_separation.h"
#include "md_accel.h"
#include "lennard_jones.h"
#include "dbg.h"

MD_BoxParameters * new_MD_BoxParameters(int Nx, int Ny, int Nz, double spacing, double vmax) {
  MD_BoxParameters *mdb = malloc(sizeof(struct MD_BoxParameters));

  mdb->Nx = Nx;
  mdb->Ny = Ny;
  mdb->Nz = Nz;
  mdb->spacing = spacing;
  mdb->vmax = vmax;

  return mdb;
}

void destroy_MD_BoxParameters(MD_BoxParameters *mdb) {
  assert(mdb != NULL);
  free(mdb);
}

MD_RunParameters * new_MD_RunParameters(double t, double dt, int itr, int eqi, int rc) {
  MD_RunParameters *mdp = malloc(sizeof(struct MD_RunParameters));

  mdp->t = t;
  mdp->dt = dt;
  mdp->iterations = itr;
  mdp->equilibrium = eqi;
  mdp->report_count = rc;

  return mdp;
}

void destroy_MD_RunParameters(MD_RunParameters *mdp) {
  assert(mdp != NULL);
  free(mdp);
}

void apply_Periodic(Particle *particle, double length) {
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

void calculate_Forces(LennardJonesPotential *ljp, ParticleCollection *particle, int collection_size, double length) {
  MD_Separation *sep;
  MD_Accel *accel;

  for (int i = 0; i < collection_size; i++) {
    particle[i]->ax = 0.0;
    particle[i]->ay = 0.0;
    particle[i]->az = 0.0;
  }

  for (int m = 0; m < collection_size - 1; m++) {
    for (int n = m + 1; n < collection_size; n++) {
      sep = new_MD_Separation(particle[m], particle[n], length);
      accel = new_MD_Accel(ljp, sep); // calculates (dx/r)*force

      particle[m]->ax += accel->ax;
      particle[m]->ay += accel->ay;
      particle[m]->az += accel->az;

      particle[n]->ax -= accel->ax;
      particle[n]->ay -= accel->ay;
      particle[n]->az -= accel->az;

      destroy_MD_Separation(sep);
      destroy_MD_Accel(accel);
    }
  }
}

double initialize_Collection(ParticleCollection *p, MD_BoxParameters *mdb) {
  double x, y, z;
  double length;
  int collection_size = mdb->Nx * mdb->Ny * mdb->Nz;

  x = y = z = mdb->spacing;

  math_RandomSeed();

  int i = 0;

  for (int m = 0; m < mdb->Nx; m++) {
    for (int n = 0; n < mdb->Ny; n++) {
      for (int o = 0; o < mdb->Nz; o++) {
        if (i > collection_size - 1) break;

        p[i]->x = x;
        p[i]->y = y;
        p[i]->z = z;

        p[i]->vx = mdb->vmax * (2 * math_Random() - 1.0);
        p[i]->vy = mdb->vmax * (2 * math_Random() - 1.0);
        p[i]->vz = mdb->vmax * (2 * math_Random() - 1.0);

        DEBUG_PRINT("%d %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f",i, x, y, z, p[i]->vx, p[i]->vy, p[i]->vz);

        z += mdb->spacing;

        i++;
      }
      y += mdb->spacing;
      z =  mdb->spacing;
    }
    x += mdb->spacing;
    y =  mdb->spacing;
  }

  // Calculate the velocity drift
  double vxcum, vycum, vzcum;
  vxcum = vycum = vzcum = 0.0;

  for (int i = 0; i < collection_size; i++) {
    vxcum += p[i]->vx;
    vycum += p[i]->vy;
    vzcum += p[i]->vy;
  }

  vxcum = vxcum/(double) collection_size;
  vycum = vycum/(double) collection_size;
  vzcum = vzcum/(double) collection_size;

  DEBUG_PRINT("vxcum: %12.6f vycum: %12.6f vycum: %12.6f", vxcum, vycum, vzcum);

  for (int i = 0; i < collection_size; i++) {
    p[i]->vx -= vxcum;
    p[i]->vy -= vycum;
    p[i]->vz -= vzcum;

    DEBUG_PRINT("%12.6f %12.6f %12.6f", p[i]->vx, p[i]->vy, p[i]->vz);
  }

  length = x;

  DEBUG_PRINT("box length: %12.6f", length);

  return length;
}
