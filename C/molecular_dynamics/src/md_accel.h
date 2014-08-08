#ifndef MD_ACCEL
#define MD_ACCEL

#include "md_separation.h"
#include "lennard_jones.h"

typedef struct MD_Accel {
  double ax;
  double ay;
  double az;
} MD_Accel;

MD_Accel * new_MD_Accel(LennardJonesPotential *, MD_Separation *);
void destroy_MD_Accel(MD_Accel *);

#endif
