#include "lennard_jones.h"
#include "md_report.h"
#include "md_iterator.h"
#include "md_systemenergy.h"
#include "md.h"

int main(void) {
  LennardJonesPotential *ljp = new_LennardJonesPotential(3.40, 0.997);
  MD_BoxParameters *mdb = new_MD_BoxParameters(10, 10, 10, 2.0 * ljp->sigma, 2.0);
  MD_RunParameters *mdp = new_MD_RunParameters(0.0, 0.01, 2000, 500, 500);
  int collection_size = mdb->Nx * mdb->Ny * mdb->Nz;
  ParticleCollection *particle = new_ParticleCollection(collection_size);
  MD_Report *report = new_Report();
  double box_length;

  int report_interval = (mdp->iterations - mdp->equilibrium)/mdp->report_count;

  box_length = initialize_Collection(particle, mdb);

  report->collection      = particle;
  report->collection_size = collection_size;

  calculate_Forces(ljp, particle, collection_size, box_length);

  for (int i = 0; i < mdp->iterations; i++) {
    verlet_IteratePosition(particle, collection_size, mdp->dt, box_length, apply_Periodic);
    verlet_IterateVelocity(particle, collection_size, mdp->dt);

    calculate_Forces(ljp, particle, collection_size, box_length);

    verlet_IterateVelocity(particle, collection_size, mdp->dt);

    MD_SystemEnergy *energy = calculate_SystemEnergy(ljp, particle, collection_size, box_length);

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
  destroy_MD_BoxParameters(mdb);
  destroy_MD_RunParameters(mdp);
  destroy_LennardJonesPotential(ljp);
  destroy_ParticleCollection(particle, collection_size);
}
