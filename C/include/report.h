#include "ball.h"

typedef struct Report {
  double t;
  BallCollection *ball;
} Report;

void run_report(Report *);
