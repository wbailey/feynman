#include "simulation.h"

int main(void) {
  MD_SystemEnergy *energy = MD_new_SystemEnergy();
  ParticleCollection *particle = new_ParticleCollection(MD_CollectionSize);
  MD_Report *report = MD_new_Report();
  double box_length;

  int report_interval = MD_Iterations/MD_ReportCount;

  box_length = MD_initialize_Collection(particle, MD_CollectionSize, LJ_Sigma);

  report->collection      = particle;
  report->collection_size = MD_CollectionSize;

  MD_calculate_Forces(particle, MD_CollectionSize, box_length);

  for (int i = 0; i < MD_Iterations; i++) {
    MD_iterate_VerletPosition(particle, MD_CollectionSize, dt, box_length, MD_apply_Periodic);
    MD_iterate_VerletVelocity(particle, MD_CollectionSize, dt);

    MD_calculate_Forces(particle, MD_CollectionSize, box_length);

    MD_iterate_VerletVelocity(particle, MD_CollectionSize, dt);

    energy = MD_calculate_SystemEnergy(particle, MD_CollectionSize, box_length);

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
