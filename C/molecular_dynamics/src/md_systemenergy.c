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

double calculate_KineticEnergy(Particle *p) {
  double ke = 0.0;

  DEBUG_PRINT("vx: %12.8f", p->vx);
  DEBUG_PRINT("vy: %12.8f", p->vy);
  DEBUG_PRINT("vz: %12.8f", p->vz);

  ke += 
    p->vx * p->vx + 
    p->vy * p->vy +
    p->vz * p->vz;

  ke *= 0.5;

  return ke;
}
