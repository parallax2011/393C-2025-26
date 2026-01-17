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
        std::cout << "heading:          " << imu.rotation() << std::endl << std::endl;
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

    chassis.set_drive_exit_conditions(0.5, 300, 2000);
    chassis.set_drive_constants(12, 1, 0, 6, 0); // 1.2,4.5
    chassis.set_heading_constants(6, 0.4, 0, 1, 0);

    chassis.set_turn_exit_conditions(0.8, 300, 3000);
    chassis.set_turn_constants(12, 0.37, 0.03, 3.1, 15); // 45-90
    //chassis.set_turn_constants(12, 0.37, 0.03, 2.9, 5); // smaller than 30


    if (imu.installed()) {
        chassis.turn(180);
    }
    //chassis.move(20);
    
    
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
int filterTimer = 200;           // when to stop filtering

// start filter eject, but non-blocking
void filter_block() {
    filtering = true;
    filterTimer = timer::system(); // run for 1.5s
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

    thread tColorSortAlg1 = thread(filterRed);

    bool R1; bool R2; bool L1; bool L2;

    while (1) {

        // intake ping booleans
        R1 = controller1.ButtonR1.pressing(); R2 = controller1.ButtonR2.pressing();
        L1 = controller1.ButtonL1.pressing(); L2 = controller1.ButtonL2.pressing();

        // chassis
        arcade(controller1.Axis3.position(), // forward
                controller1.Axis1.position(), // turn
                false, // enabling turn curves
                5 // deadzone=5
        );

        // intake
        if (R1 and !L1 and filtering) {
            // run filter eject
            moveIntake(0, 0);
            
            if (vex::timer::system() > filterTimer) {
                filtering = false;
                moveIntake(0, 0); //stop for adjustment
            }
        }

        else if (R1 and L1) { descorer.set(false); outtake(); }
        else if (R1 and !L1 and enableIntake) { descorer.set(false); basket(); }
        else if (R2 and L1) { descorer.set(false); highGoal(); }
        else if (R2 and !L1) { descorer.set(false); longGoal(); }
        else if (L2) { descorer.set(true); }
        else { descorer.set(false); moveIntake(0, 0); }

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