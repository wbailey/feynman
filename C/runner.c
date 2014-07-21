#include <stdlib.h>
#include <stdio.h>
#include "ball.h"

static const int collection_size = 2;

int main() {
  BallCollection *ball;
  const double g = 9.8, dt = 0.01;
  double t = 0.0;
  int j;

  ball = new_BallCollection(collection_size);

  // Initial Conditions
  ball[0]->y = 10.0;
  ball[1]->y = 10.0;
  ball[1]->vx = 5.0;

  ball[0]->ay = -g;
  ball[1]->ay = -g;

  while (ball[0]->y > 0.0 && ball[1]->y > 0.0) {
    printf("%12.6f ", t);

    for (j = 0; j < 2; j++) {
      ball[j]->vx += ball[j]->ax * dt;
      ball[j]->x += ball[j]->vx * dt;
      ball[j]->vy += ball[j]->ay * dt;
      ball[j]->y += ball[j]->vy * dt;

      printf("%12.6f %12.6f ", ball[j]->x, ball[j]->y);
    }

    printf("\n");

    t += dt;
  }

  destroy_BallCollection(ball);

  return 0;
}
