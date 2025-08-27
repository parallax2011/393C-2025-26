#include "vex.h"

// robot
#define WHEEL_DIAMETER 3.25
#define GEAR_RATIO 0.75
#define IMU_SCALE 360

// chassis curve
#define TURN_CURVE_SCALE 15

// optical

// color signatures
#define RED_LOWER_LIM 0
#define RED_UPPER_LIM 15
#define BLUE_LOWER_LIM 203
#define BLUE_UPPER_LIM 230

// lift
#define LIFT_VEL 100
#define LIFT_GRAB_POS 135
#define LIFT_WALL_STAKE_POS 500
#define LIFT_SCORE_POS 647

// PID gains

// lateral PID controller
#define DRIVE_MAX 12
#define DRIVE_KP 1.2
#define DRIVE_KI 0
#define DRIVE_KD 8
#define DRIVE_STARTI 0
#define DRIVE_SETTLE_ERROR 1.5
#define DRIVE_SETTLE_TIME 300
#define DRIVE_TIMEOUT 4000

// heading PID controller
#define HEADING_MAX 6
#define HEADING_KP .4
#define HEADING_KI 0
#define HEADING_KD 1
#define HEADING_STARTI 0

// angular PID controller
#define TURN_MAX 12
// #define TURN_KP 0.7
// #define TURN_KI 0.02
// #define TURN_KD 5.5
// #define TURN_KP 0.465
// #define TURN_KI 0
// #define TURN_KD 2.55
#define TURN_KP 0.4
#define TURN_KI 0.03
#define TURN_KD 3.2
#define TURN_STARTI 15
#define TURN_SETTLE_ERROR 1
#define TURN_SETTLE_TIME 300
#define TURN_TIMEOUT 3000

#define s 2.8
#define m 3.2
#define x 3.8

// swing PID controller
#define SWING_MAX 12
#define SWING_KP 1
#define SWING_KI 0.01
#define SWING_KD 6
#define SWING_STARTI 15
#define SWING_SETTLE_ERROR 1
#define SWING_SETTLE_TIME 200
#define SWING_TIMEOUT 3000
#define LEFT 1
#define RIGHT 2

// arc PID controller
#define ARC_MAX 10
#define ARC_KP 0.6 
#define ARC_KI 0.001
#define ARC_KD 3
#define ARC_STARTI 0