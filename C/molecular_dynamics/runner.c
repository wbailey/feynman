#include "lennard_jones.h"
#include "md_report.h"
#include "md_iterator.h"
#include "md_systemenergy.h"
#include "md.h"

int main(void) {
  MD_Parameters *mdp = new_MD_Parameters(0.0, 0.01, 50, 6000, 1000, 1000);
  LennardJonesPotential *ljp = new_LennardJonesPotential(3.40, 0.997);
  ParticleCollection *particle = new_ParticleCollection(mdp->particle_count);
  MD_Report *report = new_Report();
  double box_length;

  int report_interval = (mdp->iterations - mdp->equilibrium)/mdp->report_count;

  box_length = initialize_Collection(particle, mdp->particle_count, ljp->sigma);

  report->collection      = particle;
  report->collection_size = mdp->particle_count;

  calculate_Forces(ljp, particle, mdp->particle_count, box_length);

  for (int i = 0; i < mdp->iterations; i++) {
    verlet_IteratePosition(particle, mdp->particle_count, mdp->dt, box_length, apply_Periodic);
    verlet_IterateVelocity(particle, mdp->particle_count, mdp->dt);

    calculate_Forces(ljp, particle, mdp->particle_count, box_length);

    verlet_IterateVelocity(particle, mdp->particle_count, mdp->dt);

    MD_SystemEnergy *energy = calculate_SystemEnergy(ljp, particle, mdp->particle_count, box_length);

    mdp->t += mdp->dt;

    if (i % report_interval == 0 && i > mdp->equilibrium) {
      report->t  = mdp->t;
      report->pe = energy->pe;
      report->ke = energy->ke;
      report->te = energy->te;
      print_Report(report);
    }
  
    destroy_SystemEnergy(energy);
  }

  destroy_Report(report);
  destroy_MD_Parameters(mdp);
  destroy_LennardJonesPotential(ljp);
  destroy_ParticleCollection(particle, mdp->particle_count);
}
