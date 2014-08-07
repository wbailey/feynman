#ifndef MD_SYSTEMENERGY
#define MD_SYSTEMENERGY

#include "particle.h"
#include "lennard_jones.h"

typedef struct MD_SystemEnergy {
  double pe;
  double ke;
  double te;
} MD_SystemEnergy;

MD_SystemEnergy * MD_new_SystemEnergy();
void MD_destroy_SystemEnergy(MD_SystemEnergy *);
MD_SystemEnergy * MD_calculate_SystemEnergy(LennardJonesPotential *, ParticleCollection *, int, double);

#endif