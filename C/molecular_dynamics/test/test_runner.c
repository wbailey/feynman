#include <stdio.h>
#include "minunit.h"
#include "simulation.h"
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

  destroy_ParticleCollection(collection);

  return NULL;
}

char *test_md_sign() {
  int expectation, result;
  float test;

  test = 0.9;
  expectation = 1;
  result = math_Sign(test);

  printf("test: %8.4f result: %d, expectation: %d\n", test, result, expectation);

  mu_assert(result == expectation, "Positive number identified");

  test = 0.0;
  expectation = 0;
  result = math_Sign(test);

  printf("test: %8.4f result: %d, expectation: %d\n", test, result, expectation);
  
  mu_assert(result == expectation, "Zero identified");
  
  test = -9.5;
  expectation = -1;
  result = math_Sign(test);

  printf("test: %8.4f result: %d, expectation: %d\n", test, result, expectation);
  
  mu_assert(result == expectation, "Negative number identified");
  
  return NULL;
}

char *test_periodic() {
  Particle *p = new_Particle();
  double test, result, expectation;

  p->x = p->y = p->z = -2.0;

  printf("test particle before: x = %8.4f y = %8.4f z = %8.4f\n", p->x, p->y, p->z);

  test = 10.0;
  expectation = 8.0;

  apply_Periodic(p, test);

  printf("test particle  after: x = %8.4f y = %8.4f z = %8.4f\n", p->x, p->y, p->z);
  printf("test: %8.4f expectation: %8.4f\n", test, expectation);

  mu_assert( p->x == expectation, "Negative side test shift");
  mu_assert( p->y == expectation, "Negative side test shift");
  mu_assert( p->z == expectation, "Negative side test shift");
  
  p->x = p->y = p->z = 12.0;

  printf("test particle before: x = %8.4f y = %8.4f z = %8.4f\n", p->x, p->y, p->z);

  test = 10.0;
  expectation = 2.0;

  apply_Periodic(p, test);

  printf("test particle  after: x = %8.4f y = %8.4f z = %8.4f\n", p->x, p->y, p->z);
  printf("test: %8.4f expectation: %8.4f\n", test, expectation);

  mu_assert( p->x == expectation, "Positive side test shift");
  mu_assert( p->y == expectation, "Positive side test shift");
  mu_assert( p->z == expectation, "Positive side test shift");
  return NULL;
}

char *test_md_new_separation() {
  Particle *p = new_Particle();
  Particle *o = new_Particle();
  double test, expectation;

  p->x = p->y = p->z = 5.0;
  o->x = o->y = o->z = 15.0;

  test =  30.0;
  expectation = -10.0;

  MD_Separation *sep = MD_new_Separation(p, o, test);

  printf("test particle 1: x = %8.4f y = %8.4f z = %8.4f\n", p->x, p->y, p->z);
  printf("test particle 2: x = %8.4f y = %8.4f z = %8.4f\n", o->x, o->y, o->z);
  printf("test: %8.4f expectation: %8.4f result: dx = %8.4f dy = %8.4f dz = %8.4f\n", test, expectation, sep->dx, sep->dy, sep->dz);

  mu_assert(sep->dx == expectation, "Particles are closer than PBC result")
  mu_assert(sep->dy == expectation, "Particles are closer than PBC result")
  mu_assert(sep->dz == expectation, "Particles are closer than PBC result")

  destroy_MD_Separation(sep);

  test =  18.0;
  expectation = 8.0;

  MD_Separation *pep = MD_new_Separation(p, o, test);

  printf("test particle 1: x = %8.4f y = %8.4f z = %8.4f\n", p->x, p->y, p->z);
  printf("test particle 2: x = %8.4f y = %8.4f z = %8.4f\n", o->x, o->y, o->z);
  printf("test: %8.4f expectation: %8.4f result: dx = %8.4f dy = %8.4f dz = %8.4f\n", test, expectation, pep->dx, pep->dy, pep->dz);

  mu_assert(pep->dx == expectation, "Particles are using PBC result")
  mu_assert(pep->dy == expectation, "Particles are using PBC result")
  mu_assert(pep->dz == expectation, "Particles are using PBC result")

  destroy_MD_Separation(pep);

  return NULL;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_particle_uniqueness);
    mu_run_test(test_collection_intialization);
    mu_run_test(test_lennard_jones_force_calculation);
    mu_run_test(test_lennard_jones_potential_energy_calculation);
    mu_run_test(test_md_sign);
    mu_run_test(test_md_new_separation);
    mu_run_test(test_periodic);

    return NULL;
}

RUN_TESTS(all_tests);
