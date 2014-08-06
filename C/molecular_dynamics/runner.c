#include "simulation.h"

int main(void) {
  MD_SystemEnergy *energy = MD_new_SystemEnergy();
  ParticleCollection *particle = new_ParticleCollection(particle_count);
  MD_Report *report = MD_new_Report();
  double box_length;

  int report_interval = iterations/reportcount;

  box_length = MD_initialize_Collection(particle, particle_count, LJ_Sigma);

  report->collection      = particle;
  report->collection_size = particle_count;

  MD_calculate_Forces(particle, particle_count, box_length);

  for (int i = 0; i < iterations; i++) {
    MD_iterate_VerletPosition(particle, particle_count, dt, box_length, MD_apply_Periodic);
    MD_iterate_VerletVelocity(particle, particle_count, dt);

    MD_calculate_Forces(particle, particle_count, box_length);

    MD_iterate_VerletVelocity(particle, particle_count, dt);

    energy = MD_calculate_SystemEnergy(particle, particle_count, box_length);

    t += dt;

    if (i % report_interval == 0) {
      report->t  = t;
      report->pe = energy->pe;
      report->ke = energy->ke;
      report->te = energy->te;
      MD_print_Report(report);
    }
  
    MD_destroy_SystemEnergy(energy);
  }

  MD_destroy_Report(report);
  destroy_ParticleCollection(particle, particle_count);
}
