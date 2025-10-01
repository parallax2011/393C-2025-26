#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// global instance of chassis
Drive chassis(ZERO_TRACKER_NO_ODOM, // drive setup
              motor_group(lf, lm, lb), // left motors
              motor_group(rf, rm, rb), // right motors
              PORT17, // imu port
              3.25, // wheel diameter
              0.75, // external ratio
              360, // gyro scale
              // odom setup
              PORT1, // LF motor port
              -PORT2, // RF motor port
              PORT3, // LB motor port
              -PORT4, // RB motor port
              3, // forward tracker port
              2.75, // forward tracker diameter
              -2, // forward tracker center distance
              1, // sideways tracker port
              -2.75,  // sideways tracker diameter
              5.5 // sideways tracker center distance
);

// A global instance of brain used for printing to the V5 Brain screen.
brain Brain;
controller controller1;

//The motor constructor takes motors as (port, ratio, reverse), so for example
//motor LeftFront = motor(PORT1, ratio6_1, false);

//Add your devices below, and don't forget to do the same in robot-config.h:
#define RED ratio36_1
#define GREEN ratio18_1
#define BLUE ratio6_1

#define REVERSE_L true
#define REVERSE_R false

#define PORT_LF PORT13
#define PORT_LM PORT12
#define PORT_LB PORT11
#define PORT_RF PORT20
#define PORT_RM PORT19
#define PORT_RB PORT18
#define PORT_INTAKE_LOWER PORT10
#define PORT_INTAKE_UPPER PORT9
#define PORT_INTAKE_BACK PORT7

#define PORT_IMU PORT17
#define PORT_OPTICAL PORT14

// motors/motor groups
motor lf = motor(PORT_LF, BLUE, REVERSE_L);
motor lm = motor(PORT_LM, BLUE, REVERSE_L);
motor lb = motor(PORT_LB, BLUE, REVERSE_L);
motor rf = motor(PORT_RF, BLUE, REVERSE_R);
motor rm = motor(PORT_RM, BLUE, REVERSE_R);
motor rb = motor(PORT_RB, BLUE, REVERSE_R);

motor inl = motor(PORT_INTAKE_LOWER, BLUE, false); // intake lower 11w
motor inu = motor(PORT_INTAKE_UPPER, BLUE, false); // intake upper 5.5w
motor inb = motor(PORT_INTAKE_BACK, BLUE, true); // intake back 5.5w

motor_group l = motor_group(lf, lm, lb);
motor_group r = motor_group(rf, rm, rb);
motor_group intake = motor_group(inl, inu, inb);

// sensors
inertial imu = inertial(PORT_IMU);
optical optic = optical(PORT_OPTICAL);

// pneumatics
digital_out scraper = digital_out(Brain.ThreeWirePort.A);
digital_out descorer = digital_out(Brain.ThreeWirePort.B);
digital_out parker = digital_out(Brain.ThreeWirePort.C);

void vexcodeInit( void ) {
  // nothing to initialize
}