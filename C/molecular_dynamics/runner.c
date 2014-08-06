#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "simulation.h"

int main(void) {
  MD_SystemEnergy *energy = MD_new_SystemEnergy();
  ParticleCollection *particle = new_ParticleCollection(MD_CollectionSize);
  MD_Report *report = MD_new_Report();

  int report_interval = MD_Iterations/MD_ReportCount;

  MD_initialize_Collection(particle, MD_CollectionSize);

  report->collection      = particle;
  report->collection_size = MD_CollectionSize;

  MD_calculate_Forces(particle, MD_CollectionSize);

  for (int i = 0; i < MD_Iterations; i++) {
    MD_iterate_VerletPosition(particle, MD_CollectionSize);
    MD_iterate_VerletVelocity(particle, MD_CollectionSize);

    MD_calculate_Forces(particle, MD_CollectionSize);

    MD_iterate_VerletVelocity(particle, MD_CollectionSize);

    energy = MD_calculate_SystemEnergy(particle, MD_CollectionSize, MD_BoxLength);

    t += dt;

    if (i % report_interval == 0) {
      report->t  = t;
      report->pe = energy->pe;
      report->ke = energy->ke;
      report->te = energy->te;
      MD_print_Report(report);
    }
  }

  MD_destroy_SystemEnergy(energy);
  MD_destroy_Report(report);
  destroy_ParticleCollection(particle);
}
