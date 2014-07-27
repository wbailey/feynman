#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "report.h"

Report * new_Report(double t, BallCollection *ball) {
  struct Report *report = malloc(sizeof(struct Report));

  report->t = t;
  report->ball = ball;

  return report;
}

void run_Report(Report *report) {
  printf("%12.6f ", report->t);

  for (int j = 0; j <= sizeof(report->ball)/sizeof(report->ball[0]); j++) {
    printf("%12.6f %12.6f ", report->ball[j]->x, report->ball[j]->y);
  }

  printf("\n");
}

void final_Report(Report *report) {
  fprintf(stderr, "Flight Time: %12.6f\nMaximum Height: %12.6f\n", report->flightTime, report->maxHeight);
}

void destroy_Report(Report *report) {
  for (int i = 0; i <= sizeof(report->ball)/sizeof(report->ball[0]); i++) {
    assert(report->ball[i] != NULL);
    free(report->ball[i]);
  }

  free(report);
}
