using namespace vex;

extern brain Brain;

//To set up a motor called LeftFront here, you'd use
//extern motor LeftFront;

//Add your devices below, and don't forget to do the same in robot-config.cpp:
extern controller controller1;

// motors/motor groups
extern motor lf;
extern motor lm;
extern motor lb;
extern motor rf;
extern motor rm;
extern motor rb;
extern motor intake;
extern motor lift;
extern motor_group l;
extern motor_group r;

// sensors
extern inertial imu;
extern optical optic;
extern rotation rotationSensor;

// pneumatics
extern digital_out mogo;
extern digital_out doink;
extern digital_out intakePiston;

void  vexcodeInit( void );