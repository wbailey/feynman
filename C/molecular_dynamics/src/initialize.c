#include "initialize.h"

void MD_Initialize(ParticleCollection *collection) {
  collection[0]->x  =  3.0;
  collection[0]->y  =  0.0;
  collection[0]->vx =  0.5;
  collection[0]->vy =  0.0;
  collection[1]->x  =  9.0;
  collection[1]->y  =  0.0;
  collection[1]->vx = -0.5;
  collection[1]->vy =  0.0;
}
