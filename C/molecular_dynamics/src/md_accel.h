#ifndef MD_ACCEL
#define MD_ACCEL

#include <stdlib.h>
#include <assert.h>
#include "lennard_jones.h"
#include "md_separation.h"

typedef struct MD_Accel {
  double ax;
  double ay;
  double az;
} MD_Accel;

MD_Accel * MD_new_Accel(MD_Separation *);
void MD_destroy_Accel(MD_Accel *);

#endif
