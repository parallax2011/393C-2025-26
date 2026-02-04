#include "vex.h"
#include <iostream>
#include <string>
#include <array>
#include <sstream>  
#include <vector>
#include <typeinfo>
#include <functional>

using namespace vex;
using namespace std;
competition Competition;

bool auto_started = false;
int auton = -1; //int auton = 0;

void telemetry() {
    while (1) {

        // cout << "Accel time:         " << accelTime.count() << "s" << endl; 
        // cout << "Oscil time:       " << "s" << endl;
        // cout << "INIT overshoot:    " << initOvershoot << "in" << endl;
        // cout << "ESSE overshoot:    " << esseOvershoot << "in" << endl;

        cout << "Pos [in]:     " << (chassis.getLeftPos() + chassis.getRightPos()) / 2 << std::endl;
        cout << "Ang [deg]:    " << imu.rotation() << std::endl << std::endl;
        // std::cout << "drive:            " << (l.position(deg) + r.position(deg))/2 << std::endl;
        // std::cout << "intake:           " << intake.temperature(celsius) << std::endl << std::endl;
        // std::cout << "Position [deg]:         " << intake.position(deg) << std::endl;
        // std::cout << "Velocity [pct]:         " << intake.velocity(pct) << std::endl;
        // std::cout << "Current [pct]:          " << intake.current(pct) << std::endl;
        // std::cout << "Power [watt]:           " << intake.power(watt) << std::endl;
        // std::cout << "Torque [Nm]:            " << intake.torque(Nm) << std::endl;
        // std::cout << "Efficiency [pct]:       " << intake.efficiency(pct) << std::endl;
        // std::cout << "Voltage [volt]:         " << intake.voltage() << std::endl;
        // std::cout << std::endl << std::endl;

        // std::cout << "velocity:         " << (l.voltage() + r.voltage()) / 2 << std::endl << std::endl;
        // wait(500, msec);
        wait(500, msec);
    }
}

void pre_auton() {
    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();
    //default_constants();
    // thread TLM = thread(telemetry);
    // thread batteryUpdate = thread(batteryCheck);
    // batteryUpdate.setPriority(1);

    cont.Screen.clearScreen(); cont.Screen.setCursor(1, 1); cont.Screen.print("IMU Calibrating...");

    optic.setLight(ledState::on);
    optic.setLightPower(100);
    optic.objectDetectThreshold(10);
    
    imu.calibrate(3000);
    wait(3000, msec);

    os.menuCONFIG();
}

void autonomous(void) {
    l.resetPosition();
    r.resetPosition();
    imu.resetHeading();
    imu.resetRotation();

    chassis.setLinExits(1.5, 300, 2000);
    chassis.setLin(12, 1, 0, 7, 0); // 1.2,4.5
    chassis.setAng(6, 0.4, 0, 1, 0); // kp0.4, kd1

    chassis.setTurnExits(0.8, 300, 3000);

    // chassis.set_turn_constants(12, 0.37, 0.03, 3.1, 15); // 120-180s
    chassis.setTurn(12, 0.37, 0.03, 3.1, 15); // 45-90
    //chassis.set_turn_constants(12, 0.37, 0.03, 2.9, 5); // smaller than 30

    if (auton == 0) {} // left 6+3
    else if (auton == 1) {} 
    else if (auton == 2) {} // right 6+3
    else if (auton == 3) {} // solo awp
    else if (auton == 4) {} // left 9
    
    //autoLSAWP();
    // auto_left_4_5();
    //autoRight();
    //autoSKILLS();
}

bool enableIntake = true;
// void filter_blue() { get_block("blue"); }
// void filter_red() { get_block("red"); }

bool scraperState = false;
bool descorerState = false;

// Most global initializations occur in config.cpp
int main() {
    // Set up callbacks for autonomous and driver control periods.
    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);

    // cont.ButtonY.pressed(ctrl_scraper);
    // cont.ButtonL2.pressed(ctrl_descorer);

    // scraper
    auto ctrl_scraper = []() { 
        scraperState = !scraperState;
        scraper.set(scraperState); };
    cont.ButtonY.pressed(ctrl_scraper);
    
    // descorer
    auto ctrl_descorer = []() {
        descorerState = !descorerState;
        descorer.set(descorerState); };
    cont.ButtonL2.pressed(ctrl_descorer);

    // Run the pre-autonomous function.
    pre_auton();

    // Prevent main from exiting with an infinite loop.
    while (true) {
        wait(100, msec);
        // Sleep the task for a short amount of time to
        // prevent wasted resources.
    }
}