#include <stdlib.h>
#include <stdio.h>
#include "ball.h"

static const int collection_size = 2;

int main() {
  BallCollection *ball;
  int i,j;

  ball = new_BallCollection(collection_size);

  for (i = 0; i<1000; i++) {
    for (j = 0; j<2; j++) {
      ball[j]->x += 0.1;
    }
  }

  for (j = 0; j < collection_size; j++) {
    toString_Ball(ball[j]);
    printf("\n");
  }

  destroy_BallCollection(ball);

  return 0;
}
