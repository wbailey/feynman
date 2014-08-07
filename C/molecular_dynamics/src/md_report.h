#ifndef MD_REPORT
#define MD_REPORT

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
void destroy_MD_Report(MD_Report *);
void print_MD_Report(MD_Report *);

#endif
