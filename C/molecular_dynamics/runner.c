#include <stdio.h>
#include <math.h>
#include "simulation.h"

int main(void) {
  double dx, dy, r;
  double ax, ay, force;
  double pe, ke;
  ParticleCollection *particle = new_ParticleCollection(MD_Collection_Size);

  MD_Initialize(particle);

  for (int i = 0; i < MD_Iterations; i++) {
    pe = LJ_Potential_Energy(r);
    ke = 0.0;

    for (int m = 0; m < MD_Collection_Size/2; m++) {
      for (int n = MD_Collection_Size - 1; n > (MD_Collection_Size - 1)/2; n--) {
        dx = MD_Periodic(particle[m]->x, particle[n]->x, MD_Box_Length);
        dy = MD_Periodic(particle[m]->y, particle[n]->y, MD_Box_Length);

        r = sqrt(dx * dx + dy * dy);

        force = LJ_Force(r);

        ax = (dx/r) * force;
        ay = (dy/r) * force;

        ke += 0.5 * (particle[m]->vx * particle[m]->vx + particle[m]->vy * particle[m]->vy);
        ke += 0.5 * (particle[n]->vx * particle[n]->vx + particle[n]->vy * particle[n]->vy);

        MD_Euler(particle[m], -ax, -ay, dt);
        MD_Euler(particle[n], ax, ay, dt);

      }
    }

    t += dt;

    printf("%12.6f %12.6f %12.6f %12.6f %12.6f %12.6f %12.6f %12.6f\n", t, ke + pe, pe, ke, particle[0]->x, particle[0]->y, particle[1]->x, particle[1]->y);
  }

  destroy_ParticleCollection(particle);
}
