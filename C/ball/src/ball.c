#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "ball.h"

Ball * new_Ball() {
  struct Ball *ball = malloc(sizeof(struct Ball));

  ball->x = 0.0;
  ball->y = 0.0;
  ball->z = 0.0;

  ball->maxheight = -1.0;

  ball->vx = 0.0;
  ball->vy = 0.0;
  ball->vz = 0.0;

  ball->vyold = 0.0;

  ball->ax = 0.0;
  ball->ay = 0.0;
  ball->az = 0.0;

  return ball;
}

BallCollection * new_BallCollection(int count) {
  BallCollection *collection = malloc(sizeof(Ball) * count);
  int i;


  assert(collection != NULL);

  for (i = 0; i < count; i++) {
    collection[i] = new_Ball();
  }

  return collection;
}

void destroy_BallCollection(BallCollection *collection) {
  for (int i = 0; i <= sizeof(collection)/sizeof(collection[0]); i++) {
    destroy_Ball(collection[i]);
  }

  free(collection);
}

void destroy_Ball(struct Ball *ball) {
  assert(ball != NULL);
  free(ball);
}

void toString_Ball(struct Ball *ball) {
  printf("x: %12.8f\n", ball->x);
  printf("y: %12.8f\n", ball->y);
  printf("z: %12.8f\n", ball->z);

  printf("maxheight: %f\n", ball->maxheight);

  printf("vx: %12.8f\n", ball->vx);
  printf("vy: %12.8f\n", ball->vy);
  printf("vz: %12.8f\n", ball->vz);

  printf("vyold: %12.8f\n", ball->vyold);

  printf("ax: %12.8f\n", ball->ax);
  printf("ay: %12.8f\n", ball->ay);
  printf("az: %12.8f\n", ball->az);
}
