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

void destroy_Particle(struct Particle *);

void toString_Particle(struct Particle *);

ParticleCollection * new_ParticleCollection(int);

