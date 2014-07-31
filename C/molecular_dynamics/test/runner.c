#include <stdio.h>
#include "minunit.h"
#include "lennard_jones.h"
#include "particle.h"

char *test_lennard_jones_force_calculation() {
  double r = 5.0;
  double force = 0.0;
  char result[10];
  char expectation[10] = "0.380";

  force = LJ_Force(r);
  sprintf(result, "%5.3f", force);

  mu_assert(strcmp(result, expectation) == 0, "invalid force calculation");

  force = LJ_Force(LJ_Sigma);
  mu_assert(force == 0, "The force should be 0.0 at Sigma");

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

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_particle_uniqueness);
    mu_run_test(test_collection_intialization);
    mu_run_test(test_lennard_jones_force_calculation);

    return NULL;
}

RUN_TESTS(all_tests);
