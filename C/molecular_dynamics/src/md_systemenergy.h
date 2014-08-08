#ifndef MD_SYSTEMENERGY
#define MD_SYSTEMENERGY

#include "particle.h"
#include "lennard_jones.h"

typedef struct MD_SystemEnergy {
  double pe;
  double ke;
  double te;
} MD_SystemEnergy;

MD_SystemEnergy * new_SystemEnergy();
void destroy_SystemEnergy(MD_SystemEnergy *);
MD_SystemEnergy * calculate_SystemEnergy(LennardJonesPotential *, ParticleCollection *, int, double);

#endif
