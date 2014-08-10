#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "md_report.h"

MD_Report * new_Report() {
  struct MD_Report *report = malloc(sizeof(struct MD_Report));
  return report;
}

void destroy_Report(MD_Report *report) {
  assert(report != NULL);
  free(report);
}

void print_Report(MD_Report *report) {
  ParticleCollection *c = report->collection;

  printf("%9.6f ", report->t);
  printf("%9.6f ", report->pe);
  printf("%9.6f ", report->ke);
  printf("%9.6f ", report->te);
  
  for (int i = 0; i < report->collection_size; i++) {
    printf("%9.6f %9.6f ", c[i]->x, c[i]->y);
  }

  printf("\n");
  fflush(stdout);
}
