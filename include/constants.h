#include "vex.h"

// robot
#define WHEEL_DIAMETER 3.25
#define GEAR_RATIO 0.75
#define IMU_SCALE 360

// chassis curve
#define TURN_CURVE_SCALE 15

// optical
#define MIN_OUTTAKE_TIME 1000

// color signatures
#define RED_LOWER_LIM 0
#define RED_UPPER_LIM 30
#define BLUE_LOWER_LIM 203
#define BLUE_UPPER_LIM 250

#define s 2.8
#define m 3.2
#define x 3.8

#define LEFT 1
#define RIGHT 2