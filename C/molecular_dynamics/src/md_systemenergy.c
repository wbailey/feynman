#include <stdlib.h>
#include <assert.h>
#include "md_systemenergy.h"
#include "md_separation.h"
#include "lennard_jones.h"
#include "dbg.h"

MD_SystemEnergy * new_SystemEnergy() {
  struct MD_SystemEnergy *system = malloc(sizeof(struct MD_SystemEnergy));

  system->pe = 0.0;
  system->ke = 0.0;
  system->te = 0.0;

  return system;
}

void destroy_SystemEnergy(MD_SystemEnergy *energy) {
  assert(energy != NULL);
  free(energy);
}

MD_SystemEnergy * calculate_SystemEnergy(LennardJonesPotential *ljp, ParticleCollection *particle, int collection_size, double length) {
  double pe, ke, r;
  MD_Separation *sep;
  MD_SystemEnergy *system = new_SystemEnergy();
  
  pe = ke = 0.0;

  for (int i = 0; i < collection_size; i++) {
    ke += 
        particle[i]->vx * particle[i]->vx + 
        particle[i]->vy * particle[i]->vy +
        particle[i]->vz * particle[i]->vz;
    if (i < collection_size - 1) {
      for (int j = i + 1; j < collection_size; j++) {
        sep = MD_new_Separation(particle[i], particle[j], length);

        r = calculate_SeparationMagnitude(sep);
        pe += LennardJones_PotentialEnergy(ljp, r);

        destroy_MD_Separation(sep);
      }
    }
  }

  ke *= 0.5;

  system->pe = pe;
  system->ke = ke;
  system->te = pe + ke;

  return system;
}
