#ifndef MD_REPORT
#define MD_REPORT

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "particle.h"

typedef struct MD_Report {
  double t;
  double pe;
  double ke;
  double te;
  ParticleCollection *collection;
  int collection_size;
} MD_Report;

MD_Report * MD_new_Report();
void MD_destroy_Report(MD_Report *);
void MD_print_Report(MD_Report *);

#endif
