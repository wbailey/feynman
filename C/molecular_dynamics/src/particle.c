#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "particle.h"

Particle * new_Particle() {
  struct Particle *particle = malloc(sizeof(struct Particle));

  particle->x = 0.0;
  particle->y = 0.0;
  particle->z = 0.0;

  particle->vx = 0.0;
  particle->vy = 0.0;
  particle->vz = 0.0;

  particle->ax = 0.0;
  particle->ay = 0.0;
  particle->az = 0.0;

  return particle;
}

ParticleCollection * new_ParticleCollection(int count) {
  ParticleCollection *collection = malloc(sizeof(Particle) * count);
  int i;


  assert(collection != NULL);

  for (i = 0; i < count; i++) {
    collection[i] = new_Particle();
  }

  return collection;
}

void destroy_ParticleCollection(ParticleCollection *collection) {
  for (int i = 0; i <= sizeof(collection)/sizeof(collection[0]); i++) {
    destroy_Particle(collection[i]);
  }

  free(collection);
}

void destroy_Particle(struct Particle *particle) {
  assert(particle != NULL);
  free(particle);
}

void toString_Particle(struct Particle *particle) {
  printf("x: %12.8f\n", particle->x);
  printf("y: %12.8f\n", particle->y);
  printf("z: %12.8f\n", particle->z);

  printf("vx: %12.8f\n", particle->vx);
  printf("vy: %12.8f\n", particle->vy);
  printf("vz: %12.8f\n", particle->vz);

  printf("ax: %12.8f\n", particle->ax);
  printf("ay: %12.8f\n", particle->ay);
  printf("az: %12.8f\n", particle->az);
}

