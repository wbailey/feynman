#include "minunit.h"
#include "particle.h"

char *test_particle() {
  Particle *particle = new_Particle();

  return NULL;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_particle);

    return NULL;
}

RUN_TESTS(all_tests);
