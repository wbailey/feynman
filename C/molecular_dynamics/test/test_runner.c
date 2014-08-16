#include <stdio.h>
#include <math.h>
#include "minunit.h"
#include "lennard_jones.h"
#include "md_math.h"
#include "md_separation.h"
#include "md.h"

char *test_new_LennardJonesPotential() {
  double sigma_exp = 0.5;
  double epsilon_exp = 1.0;

  LennardJonesPotential *ljp = new_LennardJonesPotential(sigma_exp, epsilon_exp);

  DEBUG_PRINT("sigma: %12.6f", sigma_exp);
  DEBUG_PRINT("epsilon: %12.6f", epsilon_exp);

  mu_assert(ljp->sigma == sigma_exp, "sigma equivalence");
  mu_assert(ljp->epsilon == epsilon_exp, "epsilon equivalence");

  destroy_LennardJonesPotential(ljp);

  return NULL;
}

char * test_LennardJones_R6() {
  double sigma_exp = 2.0;
  double epsilon_exp = 1.0;
  double r = 1.0;
  double expectation = 64.0;
  double result;

  LennardJonesPotential *ljp = new_LennardJonesPotential(sigma_exp, epsilon_exp);

  result = LennardJones_R6(ljp, r);

  DEBUG_PRINT("result: %12.6f", result);
  DEBUG_PRINT("expectation: %12.6f", expectation);

  mu_assert(result == expectation, "r6 value");

  return NULL;  
}

char * test_LennardJones_R12() {
  double sigma_exp = 2.0;
  double epsilon_exp = 1.0;
  double r = 1.0;
  double expectation = 4096.0;
  double result;

  LennardJonesPotential *ljp = new_LennardJonesPotential(sigma_exp, epsilon_exp);

  result = LennardJones_R12(ljp, r);

  DEBUG_PRINT("result: %12.6f", result);
  DEBUG_PRINT("expectation: %12.6f", expectation);

  mu_assert(result == expectation, "r12 value");

  return NULL;  
}

char *test_LennardJones_Force() {
  double r = 1.0;
  double force = 0.0;
  double sigma = 2.0;
  double epsilon = 2.0;
  double force_at_sigma = -24.0;
  double expectation = -390144.0;

  LennardJonesPotential *ljp = new_LennardJonesPotential(sigma, epsilon);

  force = LennardJones_Force(ljp, r);
  DEBUG_PRINT("force: %5.3f", force);

  mu_assert(force == expectation, "invalid force calculation");

  r = sigma;

  force = LennardJones_Force(ljp, r);
  mu_assert(force == force_at_sigma, "invalid force at sigma");

  return NULL;
}

char *test_LennardJones_PotentialEnergy() {
  double r = 1.0;
  double pe = 0.0;
  double sigma = 2.0;
  double epsilon = 2.0;
  double expectation = 32256.0;

  LennardJonesPotential *ljp = new_LennardJonesPotential(sigma, epsilon);

  pe = LennardJones_PotentialEnergy(ljp, r);
  DEBUG_PRINT("potential energy: %5.3f", pe);

  mu_assert(pe == expectation, "invalid potential energy at r");

  r = sigma;

  pe = LennardJones_PotentialEnergy(ljp, r);
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
  int collection_size = 10;
  ParticleCollection *collection = new_ParticleCollection(collection_size);

  for (int i = 0; i < collection_size; i++) {
    mu_assert( collection[i]->x == 0.0, "particle not initialized");
  }

  destroy_ParticleCollection(collection, collection_size);

  return NULL;
}

char *test_md_sign() {
  int expectation, result;
  float test;

  test = 0.9;
  expectation = 1;
  result = math_Sign(test);

  DEBUG_PRINT("%8.4f result: %d, expectation: %d", test, result, expectation);

  mu_assert(result == expectation, "Positive number identified");

  test = 0.0;
  expectation = 0;
  result = math_Sign(test);

  DEBUG_PRINT("%8.4f result: %d, expectation: %d", test, result, expectation);
  
  mu_assert(result == expectation, "Zero identified");
  
  test = -9.5;
  expectation = -1;
  result = math_Sign(test);

  DEBUG_PRINT("%8.4f result: %d, expectation: %d", test, result, expectation);
  
  mu_assert(result == expectation, "Negative number identified");
  
  return NULL;
}

char *test_periodic() {
  Particle *p = new_Particle();
  double test, expectation;

  p->x = p->y = p->z = -2.0;

  DEBUG_PRINT("particle before: x = %8.4f y = %8.4f z = %8.4f", p->x, p->y, p->z);

  test = 10.0;
  expectation = 8.0;

  apply_Periodic(p, test);

  DEBUG_PRINT("particle  after: x = %8.4f y = %8.4f z = %8.4f", p->x, p->y, p->z);
  DEBUG_PRINT("%8.4f expectation: %8.4f", test, expectation);

  mu_assert( p->x == expectation, "Negative side shift");
  mu_assert( p->y == expectation, "Negative side shift");
  mu_assert( p->z == expectation, "Negative side shift");
  
  p->x = p->y = p->z = 12.0;

  DEBUG_PRINT("particle before: x = %8.4f y = %8.4f z = %8.4f", p->x, p->y, p->z);

  test = 10.0;
  expectation = 2.0;

  apply_Periodic(p, test);

  DEBUG_PRINT("particle  after: x = %8.4f y = %8.4f z = %8.4f", p->x, p->y, p->z);
  DEBUG_PRINT("%8.4f expectation: %8.4f", test, expectation);

  mu_assert( p->x == expectation, "Positive side shift");
  mu_assert( p->y == expectation, "Positive side shift");
  mu_assert( p->z == expectation, "Positive side shift");

  return NULL;
}

char *test_new_MD_Separation() {
  Particle *p = new_Particle();
  Particle *o = new_Particle();
  double test, expectation;

  p->x = p->y = p->z = 5.0;
  o->x = o->y = o->z = 15.0;

  test =  30.0;
  expectation = -10.0;

  MD_Separation *sep = new_MD_Separation(p, o, test);

  DEBUG_PRINT("particle 1: x = %8.4f y = %8.4f z = %8.4f", p->x, p->y, p->z);
  DEBUG_PRINT("particle 2: x = %8.4f y = %8.4f z = %8.4f", o->x, o->y, o->z);
  DEBUG_PRINT("%8.4f expectation: %8.4f result: dx = %8.4f dy = %8.4f dz = %8.4f", test, expectation, sep->dx, sep->dy, sep->dz);

  mu_assert(sep->dx == expectation, "Particles are closer than PBC result")
  mu_assert(sep->dy == expectation, "Particles are closer than PBC result")
  mu_assert(sep->dz == expectation, "Particles are closer than PBC result")

  destroy_MD_Separation(sep);

  test =  18.0;
  expectation = 8.0;

  MD_Separation *pep = new_MD_Separation(p, o, test);

  DEBUG_PRINT("particle 1: x = %8.4f y = %8.4f z = %8.4f", p->x, p->y, p->z);
  DEBUG_PRINT("particle 2: x = %8.4f y = %8.4f z = %8.4f", o->x, o->y, o->z);
  DEBUG_PRINT("%8.4f expectation: %8.4f result: dx = %8.4f dy = %8.4f dz = %8.4f", test, expectation, pep->dx, pep->dy, pep->dz);

  mu_assert(pep->dx == expectation, "Particles are using PBC result")
  mu_assert(pep->dy == expectation, "Particles are using PBC result")
  mu_assert(pep->dz == expectation, "Particles are using PBC result")

  destroy_MD_Separation(pep);

  return NULL;
}

char * test_new_SystemEnergy() {
  MD_SystemEnergy *se = new_SystemEnergy();

  DEBUG_PRINT("potential energy: %12.6f", se->pe);
  DEBUG_PRINT("kinetic energy: %12.6f", se->ke);
  DEBUG_PRINT("total energy: %12.6f", se->te);

  mu_assert(se->pe == 0.0, "invalid potential energy");
  mu_assert(se->ke == 0.0, "invalid kinetic energy");
  mu_assert(se->te == 0.0, "invalid total energy");

  destroy_SystemEnergy(se);

  return NULL;
}

char * test_calculate_KineticEnergy() {
  Particle *p = new_Particle();
  double ke = 0.0;
  double expectation = 37.50;

  p->vx = 5.0;
  p->vy = 5.0;
  p->vz = 5.0;

  ke = calculate_KineticEnergy(p);

  DEBUG_PRINT("particle vx: %12.6f %12.6f", p->vx, p->vx * p->vx);
  DEBUG_PRINT("particle vy: %12.6f %12.6f", p->vy, p->vy * p->vy);
  DEBUG_PRINT("particle vz: %12.6f %12.6f", p->vz, p->vz * p->vz);
  DEBUG_PRINT("calculated kinetic energy: %12.6f", ke);

  mu_assert(ke == expectation, "invalid kinetic energy: expected 75.0/2.0");

  return NULL;
}

char * test_calculate_SeparationMagnitude() {
  double length = 15.0;
  double mag;

  Particle *p1 = new_Particle();
  Particle *p2 = new_Particle();

  p1->x = p1->y = p1->z = 10.0;
  p2->x = p2->y = p2->z = 5.0;

  MD_Separation *sep = new_MD_Separation(p1, p2, length);
  mag = calculate_SeparationMagnitude(sep);

  DEBUG_PRINT("calculated magnitude: %12.6f", mag);

  mu_assert(mag == sqrt(75.0), "invalid separation magnitue: expected sqrt(75.0)")

  p1->x = p1->y = p1->z = 13.0;
  p2->x = p2->y = p2->z = 2.0;

  sep = new_MD_Separation(p1, p2, length);
  mag = calculate_SeparationMagnitude(sep);

  DEBUG_PRINT("calculated magnitude using pbc: %12.6f", mag);

  mu_assert(mag == sqrt(48.0), "invalid pbc separation magnitue: expected sqrt(48.0)")

  return NULL;

}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_particle_uniqueness);
    mu_run_test(test_collection_intialization);
    mu_run_test(test_md_sign);
    mu_run_test(test_new_MD_Separation);
    mu_run_test(test_periodic);
    mu_run_test(test_new_LennardJonesPotential);
    mu_run_test(test_LennardJones_R6);
    mu_run_test(test_LennardJones_R12);
    mu_run_test(test_LennardJones_Force);
    mu_run_test(test_LennardJones_PotentialEnergy);
    mu_run_test(test_new_SystemEnergy);
    mu_run_test(test_calculate_KineticEnergy);
    mu_run_test(test_calculate_SeparationMagnitude);

    return NULL;
}

RUN_TESTS(all_tests);
