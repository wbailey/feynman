#include <stdlib.h>
#include <stdio.h>
#include "ball.h"

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
  ball[0]->y = 10.0;
  ball[1]->y = 10.0;
  ball[1]->vx = 5.0;
}

int main() {
  BallCollection *ball;
  const double dt = 0.01;
  double t = 0.0;
  int j;

  ball = new_BallCollection(collection_size);

  initialize(ball);

  while (ball[0]->y > 0.0 && ball[1]->y > 0.0) {
    printf("%12.6f ", t);

    for (j = 0; j < 2; j++) {
      euler(ball[j], dt);
      printf("%12.6f %12.6f ", ball[j]->x, ball[j]->y);
    }

    printf("\n");

    t += dt;
  }

  destroy_BallCollection(ball);

  return 0;
}
