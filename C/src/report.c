#include <stdio.h>
#include <report.h>

void run_report(Report *report) {
  printf("%12.6f ", report->t);

  for (int j = 0; j < sizeof(report->ball)/sizeof(report->ball[0]) + 1; j++) {
    printf("%12.6f %12.6f ", report->ball[j]->x, report->ball[j]->y);
  }

  printf("\n");
}

