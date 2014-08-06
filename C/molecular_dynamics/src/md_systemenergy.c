#include "md_systemenergy.h"

MD_SystemEnergy * MD_new_SystemEnergy() {
  struct MD_SystemEnergy *system = malloc(sizeof(struct MD_SystemEnergy));

  system->pe = 0.0;
  system->ke = 0.0;
  system->te = 0.0;

  return system;
}

void MD_destroy_SystemEnergy(MD_SystemEnergy *system) {
  assert(system != NULL);
  free(system);
}

MD_SystemEnergy * MD_calculate_SystemEnergy(ParticleCollection *particle, int collection_size, double length) {
  double pe, ke, r;
  MD_Separation *sep;
  MD_SystemEnergy *system = MD_new_SystemEnergy();
  
  pe = ke = 0.0;

  for (int i = 0; i < collection_size; i++) {
    ke += 
        particle[i]->vx * particle[i]->vx + 
        particle[i]->vy * particle[i]->vy +
        particle[i]->vz * particle[i]->vz;
    if (i < collection_size - 1) {
      for (int j = i + 1; j < collection_size; j++) {
        sep = MD_new_Separation(particle[i], particle[j], length);
        r = MD_calculate_SeparationMagnitude(sep);
        pe += LJ_Potential_Energy(r);
      }
    }
  }

  ke *= 0.5;

  system->pe = pe;
  system->ke = ke;
  system->te = pe + ke;

  return system;
}
