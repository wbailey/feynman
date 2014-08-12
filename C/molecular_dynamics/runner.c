#include "lennard_jones.h"
#include "md_report.h"
#include "md_iterator.h"
#include "md_systemenergy.h"
#include "md.h"
#include "md_velocity_distribution.h"
#include "dbg.h"

int main(void) {
  LennardJonesPotential *ljp = new_LennardJonesPotential(3.40, 0.997);
  MD_BoxParameters *mdb = new_MD_BoxParameters(20, 20, 20, 2.0 * ljp->sigma, 2.0);
  MD_RunParameters *mdp = new_MD_RunParameters(0.0, 0.01, 1200, 200, 500);
  MD_Report *report = new_Report();
  double box_length;

  int collection_size = mdb->Nx * mdb->Ny * mdb->Nz;
  ParticleCollection *particle = new_ParticleCollection(collection_size);

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

  for (int i = 0; i < collection_size; i++) {
    DEBUG_PRINT("%9.6f %9.6f %9.6f ", particle[i]->x, particle[i]->y, particle[i]->z);
  }

  report_Velocities(particle, collection_size, "velocity.csv");

  destroy_Report(report);
  destroy_MD_BoxParameters(mdb);
  destroy_MD_RunParameters(mdp);
  destroy_LennardJonesPotential(ljp);
  destroy_ParticleCollection(particle, collection_size);
}
