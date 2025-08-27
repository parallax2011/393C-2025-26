#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

#pragma region
/*---------------------------------------------------------------------------*/
/*                             VEXcode Config                                */
/*                                                                           */
/*  Before you do anything else, start by configuring your motors and        */
/*  sensors. In VEXcode Pro V5, you can do this using the graphical          */
/*  configurer port icon at the top right. In the VSCode extension, you'll   */
/*  need to go to robot-config.cpp and robot-config.h and create the         */
/*  motors yourself by following the style shown. All motors must be         */
/*  properly reversed, meaning the drive should drive forward when all       */
/*  motors spin forward.                                                     */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                             JAR-Template Config                           */
/*                                                                           */
/*  Where all the magic happens. Follow the instructions below to input      */
/*  all the physical constants and values for your robot. You should         */
/*  already have configured your motors.                                     */
/*---------------------------------------------------------------------------*/

Drive chassis(

//Pick your drive setup from the list below:
//ZERO_TRACKER_NO_ODOM
//ZERO_TRACKER_ODOM
//TANK_ONE_FORWARD_ENCODER
//TANK_ONE_FORWARD_ROTATION
//TANK_ONE_SIDEWAYS_ENCODER
//TANK_ONE_SIDEWAYS_ROTATION
//TANK_TWO_ENCODER
//TANK_TWO_ROTATION
//HOLONOMIC_TWO_ENCODER
//HOLONOMIC_TWO_ROTATION
//
//Write it here:
ZERO_TRACKER_NO_ODOM,

//Add the names of your Drive motors into the motor groups below, separated by commas, i.e. motor_group(Motor1,Motor2,Motor3).
//You will input whatever motor names you chose when you configured your robot using the sidebar configurer, they don't have to be "Motor1" and "Motor2".

//Left Motors:
motor_group(lf, lm, lb),

//Right Motors:
motor_group(rf, rm, rb),

//Specify the PORT NUMBER of your inertial sensor, in PORT format (i.e. "PORT1", not simply "1"):
PORT18,

//Input your wheel diameter. (4" omnis are actually closer to 4.125"):
3.25,

//External ratio, must be in decimal, in the format of input teeth/output teeth.
//If your motor has an 84-tooth gear and your wheel has a 60-tooth gear, this value will be 1.4.
//If the motor drives the wheel directly, this value is 1:
0.75,

//Gyro scale, this is what your gyro reads when you spin the robot 360 degrees.
//For most cases 360 will do fine here, but this scale factor can be very helpful when precision is necessary.
360,

/*---------------------------------------------------------------------------*/
/*                                  PAUSE!                                   */
/*                                                                           */
/*  The rest of the drive constructor is for robots using POSITION TRACKING. */
/*  If you are not using position tracking, leave the rest of the values as  */
/*  they are.                                                                */
/*---------------------------------------------------------------------------*/

//If you are using ZERO_TRACKER_ODOM, you ONLY need to adjust the FORWARD TRACKER CENTER DISTANCE.

//FOR HOLONOMIC DRIVES ONLY: Input your drive motors by position. This is only necessary for holonomic drives, otherwise this section can be left alone.
//LF:      //RF:    
PORT1,     -PORT2,

//LB:      //RB: 
PORT3,     -PORT4,

//If you are using position tracking, this is the Forward Tracker port (the tracker which runs parallel to the direction of the chassis).
//If this is a rotation sensor, enter it in "PORT1" format, inputting the port below.
//If this is an encoder, enter the port as an integer. Triport A will be a "1", Triport B will be a "2", etc.
3,

//Input the Forward Tracker diameter (reverse it to make the direction switch):
2.75,

//Input Forward Tracker center distance (a positive distance corresponds to a tracker on the right side of the robot, negative is left.)
//For a zero tracker tank drive with odom, put the positive distance from the center of the robot to the right side of the drive.
//This distance is in inches:
-2,

//Input the Sideways Tracker Port, following the same steps as the Forward Tracker Port:
1,

//Sideways tracker diameter (reverse to make the direction switch):
-2.75,

//Sideways tracker center distance (positive distance is behind the center of the robot, negative is in front):
5.5

);
#pragma endregion

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
#define REVERSE_INTAKE false
#define REVERSE_LIFT true

#define PORT_LF PORT14
#define PORT_LM PORT15
#define PORT_LB PORT17
#define PORT_RF PORT11
#define PORT_RM PORT12
#define PORT_RB PORT13
#define PORT_INTAKE PORT10
#define PORT_LIFT PORT9

#define PORT_IMU PORT18
#define PORT_OPTICAL PORT20
#define PORT_ROTATION PORT8
#define PORT_MOGO Brain.ThreeWirePort.A
#define PORT_DOINK Brain.ThreeWirePort.D
#define PORT_INTAKE_PISTON Brain.ThreeWirePort.C

// motors/motor groups
motor lf = motor(PORT_LF, BLUE, REVERSE_L);
motor lm = motor(PORT_LM, BLUE, REVERSE_L);
motor lb = motor(PORT_LB, BLUE, REVERSE_L);
motor rf = motor(PORT_RF, BLUE, REVERSE_R);
motor rm = motor(PORT_RM, BLUE, REVERSE_R);
motor rb = motor(PORT_RB, BLUE, REVERSE_R);
motor intake = motor(PORT_INTAKE, BLUE, REVERSE_INTAKE);
motor lift = motor(PORT_LIFT, GREEN, REVERSE_LIFT);
motor_group l = motor_group(lf, lm, lb);
motor_group r = motor_group(rf, rm, rb);

// sensors
inertial imu = inertial(PORT_IMU);
optical optic = optical(PORT_OPTICAL);
rotation rotationSensor = rotation(PORT_ROTATION, false);

// pneumatics
digital_out mogo = digital_out(PORT_MOGO);
digital_out doink = digital_out(PORT_DOINK);
digital_out intakePiston = digital_out(PORT_INTAKE_PISTON);

void vexcodeInit( void ) {
  // nothing to initialize
}