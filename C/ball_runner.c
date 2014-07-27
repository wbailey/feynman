#include <stdlib.h>
#include <stdio.h>
#include "report.h"

static const int collection_size = 2;

void accel(Ball *ball) {
  const double g = 9.80;

  ball->ay = -g;
}

void euler(Ball *ball, double dt) {
  accel(ball);
  ball->vx += ball->ax * dt;
  ball->x  += ball->vx * dt;
  ball->vy += ball->ay * dt;
  ball->y  += ball->vy * dt;
}

void initialize(BallCollection *ball) {
  // Initial Conditions
  ball[0]->vy = 5.0;
  ball[1]->vx = 5.0;
  ball[1]->vy = 5.0;
}

int main() {
  BallCollection *ball;
  const double dt = 0.01;
  double t = 0.0;
  int j;

  struct Report *report = malloc(sizeof(struct Report));

  ball = new_BallCollection(collection_size);

  initialize(ball);

  report->t = t;
  report->ball = ball;

  run_report(report);

  while (ball[0]->y >= 0.0 && ball[1]->y >= 0.0) {
    for (j = 0; j < collection_size; j++) {
      ball[j]->vyold = ball[j]->vy;

      euler(ball[j], dt);

      if (ball[j]->vyold * ball[j]->vy < 0 )
        ball[j]->maxheight = ball[j]->y;
    }

    t += dt;

    report->t = t;
    report->ball = ball;

    run_report(report);
  }

  report->flightTime = t;
  report->maxHeight = ball[0]->maxheight;

  destroy_BallCollection(ball);

  return 0;
}
