#include <stdlib.h>
#include <stdio.h>
#include "ball.h"

static const int collection_size = 2;

int main() {
  BallCollection *collection;
  int i,j;

  collection = new_BallCollection(collection_size);

  for (i = 0; i<1000; i++) {
    for (j = 0; j<2; j++) {
      collection[j]->x += 0.1;
    }
  }

  for (j = 0; j < collection_size; j++) {
    Ball_to_string(collection[j]);
    printf("\n");
  }

  destroy_BallCollection(collection);

  return 0;
}
