#include "vex.h"
#include <iostream>
#include <string>
#include <array>
#include <sstream>  
#include <vector>
#include <typeinfo>
#include <functional>

using namespace vex;
competition Competition;

/**
 * Function before autonomous. It prints the current auton number on the screen
 * and tapping the screen cycles the selected auton by 1. Add anything else you
 * may need, like resetting pneumatic components. You can rename these autons to
 * be more descriptive, if you like.
 */

//int auton = 0;
bool auto_started = false;

thread t1283789;

void telemetry() {
    while (1) {
        std::cout << "pos:              " << (chassis.get_left_position_in() + chassis.get_right_position_in()) / 2 << std::endl;
        std::cout << "heading:          " << imu.rotation() << std::endl;
        // std::cout << "drive:            " << (l.position(deg) + r.position(deg))/2 << std::endl;
        // std::cout << "intake:           " << intake.temperature(celsius) << std::endl << std::endl;

        //std::cout << "Direction:              " << intake.direction() << std::endl;
        // std::cout << "Position [deg]:         " << intake.position(deg) << std::endl;
        // std::cout << "Velocity [pct]:         " << intake.velocity(pct) << std::endl;
        // std::cout << "Current [pct]:          " << intake.current(pct) << std::endl;
        // std::cout << "Power [watt]:           " << intake.power(watt) << std::endl;
        // std::cout << "Torque [Nm]:            " << intake.torque(Nm) << std::endl;
        // std::cout << "Efficiency [pct]:       " << intake.efficiency(pct) << std::endl;
        // std::cout << "Voltage [volt]:         " << intake.voltage() << std::endl;
        // std::cout << std::endl << std::endl;

        //std::cout << "velocity:         " << (l.voltage() + r.voltage()) / 2 << std::endl << std::endl;
        //std::cout << "output:           " << chassis.
        //std::cout << "drive temp:       " << l.temperature() << std::endl;
        //std::cout << "intake temp:      " << i ntake.temperature(celsius) << std::endl;
        //std::cout << "intake vel:       " << intake.voltage() << std::endl;
        //std::cout << "lift position:    " << lift.position(deg) << std::endl;
        wait(500, msec);
    }
}

void pre_auton() {
    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();
    //default_constants();

    telemetry();
    imu.calibrate(3000);
    wait(3000, msec);

    optic.setLight(ledState::on);
    optic.setLightPower(100);
    optic.objectDetectThreshold(10);
}

/**
 * Auton function, which runs the selected auton. Case 0 is the default,
 * and will run in the brain screen goes untouched during preauton. Replace
 * drive_test(), for example, with your own auton function you created in
 * autons.cpp and declared in autons.h.
 */

void autonomous(void) {
    l.resetPosition();
    r.resetPosition();
    imu.resetHeading();
    imu.resetRotation();

    //left2();
    //right2();
    //autoSkills();

    chassis.set_drive_exit_conditions(0.5, 300, 2000);
    chassis.set_drive_constants(12, 1, 0, 5.5, 0); // 1.2,4.5
    chassis.set_heading_constants(6, 0.4, 0, 1, 0);

    chassis.set_turn_exit_conditions(0.5, 300, 1000);
    chassis.set_turn_constants(12, 0.4, 0.03, 3.1, 15);
 
    autoRIGHT();
    // wait(13000, msec);
    // chassis.move(10);
    // l.stop();
    // r.stop();

    //skills();

    // auto t = []() {intake.setMaxTorque(100, pct);}; thread T = thread(t);

    // // match loader
    // chassis.move(32.3);//32.3
    // basket();
    // chassis.turn(-88);
    // scraper.set(true);
    // wait(1000, msec);
    // chassis.drive_timeout = 1000; chassis.move(9.2, 3);
    // wait(100, msec);
    // chassis.move(-13.5);
    // scraper.set(false);
    // chassis.turn(-213);
    
    // auto t2 = []() { wait(1000, msec); scraper.set(true); }; thread T2 = thread(t2); //800
    // chassis.move(37, 5.5); //23, 26, 23
    // wait(300, msec);
    
    // // long goal and push
    // chassis.drive_timeout = 1800;
    // chassis.move(-41, 12);//v=7
    // scraper.set(false);
    // chassis.turn(95);
    // longGoal();
    // chassis.move(15);
    // wait(4000, msec);
    // chassis.move(-10, 12);
    // chassis.drive_timeout = 5000;
    // chassis.move(20, 12);


    /*
    kp
    1 - 10.4
    1.4 ----
    1.5 - 9.86

    */


    
    // r.stop();
    // l.stop();
    
    
    // chassis.turn(90);
    // chassis.move(50);
    // chassis.turn(0);
    // chassis.move(25);
    // chassis.move(-90);


}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

bool enableIntake = true;
bool filtering = false;        // filter mode active?
int filterTimer = 0;           // when to stop filtering

// start filter eject, but non-blocking
void filter_block() {
    filtering = true;
    filterTimer = timer::system() + 200; // run for 1.5s
}

void get_block(std::string targetColor) {
    // initialization
    optic.integrationTime(5);
    while (1) {
        optic.setLight(ledState::on);
        optic.setLightPower(100);
    
        if (optic.isNearObject()) {
            if (optic.isNearObject()) {
                // if we are on blue team
                if (targetColor == "red") {
                    if ((optic.hue() > RED_LOWER_LIM) && (optic.hue() < RED_UPPER_LIM)) {
                        if ((optic.hue() > RED_LOWER_LIM) && (optic.hue() < RED_UPPER_LIM)) {
                            filter_block();
                        }
                    }
                }

                // if we are on red team
                else if (targetColor == "blue") {
                    if ((optic.hue() > BLUE_LOWER_LIM) && (optic.hue() < BLUE_UPPER_LIM)) {
                        if ((optic.hue() > BLUE_LOWER_LIM) && (optic.hue() < BLUE_UPPER_LIM)) {
                            filter_block();
                        }
                    }
                }
            }
        } else {

        }
    }
}
bool STATE = false;

// void ctrlKillSwitch() {
//     STATE = !STATE;
//     if (STATE) {
//         t1283789.interrupt();
//         controller1.Screen.clearScreen();
//         controller1.Screen.setCursor(1,1);
//         controller1.Screen.print("NO SORTING");
//     } else {
//         t1283789 = thread(filterRed);
//         controller1.Screen.clearScreen();
//         controller1.Screen.setCursor(1,1);
//         controller1.Screen.print("YES SORTING");
//     }

// }
//false = blue;

void filter_blue() { get_block("blue"); }
void filter_red() { get_block("red"); }

bool driverControl = false;

void usercontrol(void) {

    l.setStopping(coast);
    r.setStopping(coast);

    optic.setLight(ledState::on);
    optic.setLightPower(100);
    optic.objectDetectThreshold(50);

    thread t12312 = thread(filterRed);


    while (1) {

        // chassis
        arcade(controller1.Axis3.position(), // forward
                controller1.Axis1.position(), // turn
                false, // enabling turn curves
                5 // deadzone=5
        );

        // intake
        if (controller1.ButtonR1.pressing() and !(controller1.ButtonL1.pressing()) and filtering) {
            // run filter eject
            inl.spin(fwd, 12, volt);
            inu.spin(fwd, -12, volt);

            if (vex::timer::system() > filterTimer) {
                filtering = false;
                moveIntake(0, 0); //stop for adjustment
            }
        }

        // lower goal
        else if (controller1.ButtonR1.pressing() and controller1.ButtonL1.pressing()) {
            outtake();

        // basket
        } else if (controller1.ButtonR1.pressing() and !(controller1.ButtonL1.pressing()) and (enableIntake == true)) {
            basket();

        // upper goal
        } else if (controller1.ButtonR2.pressing() and controller1.ButtonL1.pressing()) {
            // moveIntake(12, 0);

        // long goal
        } else if (controller1.ButtonR2.pressing() and !(controller1.ButtonL1.pressing())) {
            longGoal();

        } else if (controller1.ButtonB.pressing()) {
            gate.set(true);
            moveIntake(12, 0);
        
        // anti-jamming
        } else if (controller1.ButtonX.pressing()) {
            antiJam();

        } else {
            gate.set(false);
            moveIntake(0, 0);
        }

        wait(20, msec);
    }
}

//
// Main will set up the competition functions and callbacks.
//

int main() {
    // Set up callbacks for autonomous and driver control periods.
    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);

    controller1.ButtonY.pressed(ctrlScraper);
    controller1.ButtonL2.pressed(ctrlDescorer);
    // controller1.ButtonDown.pressed(ctrlKillSwitch);

    // Run the pre-autonomous function.
    pre_auton();

    // Prevent main from exiting with an infinite loop.
    while (true) {
        wait(100, msec);
    }
}