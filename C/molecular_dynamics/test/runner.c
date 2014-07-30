#include "minunit.h"
#include "particle.h"


char *test_particle() {
  Particle *particle1 = new_Particle();
  Particle *particle2 = new_Particle();

  mu_assert( particle1 != particle2, "Equivalent Particles"); 

  return NULL;
}

char *test_collection() {
  ParticleCollection *collection = new_ParticleCollection(10);

  mu_assert( sizeof(collection)/sizeof(collection[0]) == 10, "incorrect collection size" );
  return NULL;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_particle);
    mu_run_test(test_collection);

    return NULL;
}

RUN_TESTS(all_tests);
