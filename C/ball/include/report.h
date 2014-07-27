#include "ball.h"

typedef struct Report {
  double t;
  BallCollection *ball;
  double maxHeight;
  double flightTime;
} Report;

Report * new_Report(double t, BallCollection *ball);

void run_Report(Report *);

void destroy_Report(Report *);

void final_Report(Report *);
