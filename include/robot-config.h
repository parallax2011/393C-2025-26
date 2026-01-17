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

extern motor inf;
extern motor inb;

extern motor_group l;
extern motor_group r;

// sensors
extern inertial imu;
extern optical optic;
extern vex::distance dist;

// pneumatics
extern digital_out scraper;
extern digital_out descorer;
extern digital_out hood;
extern digital_out trapdoor;

void  vexcodeInit( void );