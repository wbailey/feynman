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

double Ball_set_x(double);
double Ball_set_y(double);
double Ball_set_z(double);

double Ball_set_maxheight(double);

double Ball_set_vx(double);
double Ball_set_vy(double);
double Ball_set_vz(double);

double Ball_set_vyold(double);

double Ball_set_ax(double);
double Ball_set_ay(double);
double Ball_set_az(double);

void destroy_Ball(struct Ball *);

void Ball_to_string(struct Ball *);

BallCollection * new_BallCollection(int);

void destroy_BallCollection(BallCollection *);
