#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// global instance of chassis
Drive chassis(ZERO_TRACKER_NO_ODOM, // drive setup
              motor_group(lf, lm, lb), // left motors
              motor_group(rf, rm, rb), // right motors
              PORT6, // imu port
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

brain Brain;
controller controller1;

#define RED ratio36_1
#define GREEN ratio18_1
#define BLUE ratio6_1

#define REVERSE_L true
#define REVERSE_R false

#define PORT_LF PORT12 //16
#define PORT_LM PORT11 //15
#define PORT_LB PORT13 //14
#define PORT_RF PORT20 //13
#define PORT_RM PORT19 //12
#define PORT_RB PORT18 //11
#define PORT_INTAKE_FRONT PORT1
#define PORT_INTAKE_BACK PORT9
// #define PORT_INTAKE_LOWER PORT20
// #define PORT_INTAKE_UPPER PORT9
// #define PORT_INTAKE_BACK PORT7

#define PORT_IMU PORT6
#define PORT_OPTICAL PORT4
#define PORT_DISTANCE PORT8

// motors/motor groups
motor lf = motor(PORT_LF, BLUE, true); //t
motor lm = motor(PORT_LM, BLUE, false); //f
motor lb = motor(PORT_LB, BLUE, true); //t
motor rf = motor(PORT_RF, BLUE, true); //t
motor rm = motor(PORT_RM, BLUE, false); //f
motor rb = motor(PORT_RB, BLUE, false); //f

// 9/14 config
// motor inl = motor(PORT_INTAKE_LOWER, BLUE, false); // intake lower 11w
// motor inu = motor(PORT_INTAKE_UPPER, BLUE, false); // intake upper 5.5w
// motor inb = motor(PORT_INTAKE_BACK, BLUE, true); // intake back 5.5w
motor inf = motor(PORT_INTAKE_FRONT, BLUE, false); // intake lower 11w
motor inb = motor(PORT_INTAKE_BACK, BLUE, false); // intake upper 11w,

motor_group l = motor_group(lf, lm, lb);
motor_group r = motor_group(rf, rm, rb);

// sensors
inertial imu = inertial(PORT_IMU);
optical optic = optical(PORT_OPTICAL);
vex::distance dist = vex::distance(PORT_DISTANCE);
 
// pneumatics
digital_out scraper = digital_out(Brain.ThreeWirePort.A);
digital_out hood = digital_out(Brain.ThreeWirePort.B);
digital_out trapdoor = digital_out(Brain.ThreeWirePort.G);
digital_out descorer = digital_out(Brain.ThreeWirePort.C);

// digital_out gate = digital_out(Brain.ThreeWirePort.A);
// digital_out parker = digital_out(Brain.ThreeWirePort.C);
// digital_out pto = digital_out(Brain.ThreeWirePort.F);

void vexcodeInit( void ) {
  // nothing to initialize
}