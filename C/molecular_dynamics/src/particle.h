#ifndef _PARTICLE_H
#define _PARTICLE_H

typedef struct Particle {
  double x;
  double y;
  double z;

  double vx;
  double vy;
  double vz;

  double ax;
  double ay;
  double az;
} Particle;

typedef Particle *ParticleCollection;

Particle * new_Particle();

void destroy_Particle(Particle *);

void toString_Particle(Particle *);

ParticleCollection * new_ParticleCollection(int);

void destroy_ParticleCollection(ParticleCollection *);

#endif
