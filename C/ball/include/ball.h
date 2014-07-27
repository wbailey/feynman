typedef struct Ball {
  double mass;

  double x;
  double y;
  double z;

  double maxheight;

  double vx;
  double vy;
  double vz;

  double vyold;

  double ax;
  double ay;
  double az;
} Ball;

typedef Ball *BallCollection;

Ball * new_Ball();

void destroy_Ball(struct Ball *);

void toString_Ball(struct Ball *);

BallCollection * new_BallCollection(int);

void destroy_BallCollection(BallCollection *);
