#include <stdio.h>
#include "minunit.h"
#include "md.h"

char *test_lennard_jones_force_calculation() {
  double r = 5.0;
  double force = 0.0;
  double force_at_sigma = -24.0 * LJ_Epsilon / LJ_Sigma;
  char result[10];
  char expectation[10] = "0.380";

  force = LJ_Force(r);
  sprintf(result, "%5.3f", force);

  mu_assert(strcmp(result, expectation) == 0, "invalid force calculation");

  force = LJ_Force(LJ_Sigma);
  mu_assert(force == force_at_sigma, "The force should be 0.0 at Sigma");

  return NULL;
}

char *test_lennard_jones_potential_energy_calculation() {
  double pe = LJ_Potential_Energy(LJ_Sigma);

  mu_assert(pe == 0, "Potential energy at Sigma should be 0.0");

  return NULL;
}

char *test_particle_uniqueness() {
  Particle *particle1 = new_Particle();
  Particle *particle2 = new_Particle();

  mu_assert( particle1 != particle2, "Equivalent Particles"); 

  return NULL;
}

char *test_collection_intialization() {
  ParticleCollection *collection = new_ParticleCollection(10);

  for (int i = 0; i < 10; i++) {
    mu_assert( collection[i]->x == 0.0, "particle not initialized");
  }

  free(collection);

  return NULL;
}

char *test_periodic() {
  double length = 12.0;
  double result, expectation = 2.0;

  result = MD_Periodic(3.0, 5.0, length);
  mu_assert( result == expectation, "Standard separation");
  
  result = MD_Periodic(1.0, 11.0, length);
  mu_assert( result == expectation, "Using periodic boundary conditions for separation"); 

  return NULL;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_particle_uniqueness);
    mu_run_test(test_collection_intialization);
    mu_run_test(test_lennard_jones_force_calculation);
    mu_run_test(test_lennard_jones_potential_energy_calculation);
    mu_run_test(test_periodic);

    return NULL;
}

#define SKIP_RUNNING

RUN_TESTS(all_tests);
