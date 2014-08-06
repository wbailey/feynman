#include "md.h"

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

void MD_calculate_Forces(ParticleCollection *particle, int collection_size, double length) {
  MD_Separation *sep;
  MD_Accel *accel;

  for (int i = 0; i < collection_size; i++) {
    particle[i]->ax = 0.0;
    particle[i]->ay = 0.0;
    particle[i]->az = 0.0;
  }

  for (int m = 0; m < particle_count - 1; m++) {
    for (int n = m + 1; n < particle_count; n++) {
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
