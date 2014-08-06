#ifndef MD_H
#define MD_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#include "dbg.h"
#include "lennard_jones.h"
#include "particle.h"
#include "md_math.h"
#include "md_iterator.h"
#include "md_report.h"
#include "md_separation.h"
#include "md_systemenergy.h"
#include "md_accel.h"

extern double t;
extern double dt;

extern double particle_count;
extern int iterations;

void MD_apply_Periodic(Particle *, double);
double MD_initialize_Collection(ParticleCollection *, int, double);
void MD_calculate_Forces(ParticleCollection *, int, double);

#endif
