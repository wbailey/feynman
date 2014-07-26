#include "ball.h"

typedef struct Report {
  double t;
  BallCollection *ball;
  double maxHeight;
  double flightTime;
} Report;

void run_report(Report *);
