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
    default_constants();

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

    //LEFT_6LG_DESCORE();
    //RIGHT_DESCORE();
    autoSkills();
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
    filterTimer = timer::system() + 400; // run for 1.5s
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

void ctrlKillSwitch() {
    STATE = !STATE;
    if (STATE) {
        t1283789.interrupt();
        controller1.Screen.clearScreen();
        controller1.Screen.setCursor(1,1);
        controller1.Screen.print("NO SORTING");
    } else {
        t1283789 = thread(filterRed);
        controller1.Screen.clearScreen();
        controller1.Screen.setCursor(1,1);
        controller1.Screen.print("YES SORTING");
    }

}
//false = blue;

void filter_blue() { get_block("blue"); }
void filter_red() { get_block("red"); }

bool driverControl = false;

void usercontrol(void) {

    //if (driverControl) {

    // controller1.ButtonY.pressed(ctrlScraper);
    // controller1.ButtonL2.pressed(ctrlDescorer);
    // controller1.ButtonDown.pressed(ctrlKillSwitch);

    l.setStopping(coast); 
    r.setStopping(coast);

    optic.setLight(ledState::on);
    optic.setLightPower(100);
    optic.objectDetectThreshold(50);

    while (1) {

        // chassis
        arcade();

        // double park
        if (controller1.ButtonX.pressing() and controller1.ButtonL1.pressing()) {
            ctrlPark();
            while (controller1.ButtonX.pressing() and controller1.ButtonL1.pressing()) {
                wait(20, msec);
            }
        }
        // if (controller1.ButtonRight.pressing()) {
        //     ctrlSortSwap();
        //     while (controller1.ButtonRight.pressing()) {
        //         wait(20, msec);
        //     }
        // }
        
        // intake
        else if (controller1.ButtonR1.pressing() and !(controller1.ButtonL1.pressing()) and filtering) {
            // run filter eject
            inl.spin(fwd, 12, volt);
            inu.spin(fwd, -12, volt);

            if (vex::timer::system() > filterTimer) {
                filtering = false;
                moveIntake(0, 0, 0); //stop for adjustment
            }
        }

        // lower goal
        else if (controller1.ButtonR1.pressing() and controller1.ButtonL1.pressing()) {
            //lowGoal();
            lowGoal();//moveIntake(-6, 0, 6);

        // basket
        } else if (controller1.ButtonR1.pressing() and !(controller1.ButtonL1.pressing()) and (enableIntake == true)) {
            basket();

        // upper goal
        } else if (controller1.ButtonR2.pressing() and controller1.ButtonL1.pressing()) {
            highGoal();//moveIntake(6, -6, 10);

        // long goal
        } else if (controller1.ButtonR2.pressing() and !(controller1.ButtonL1.pressing())) {
            longGoal();

        // intake off         
        } else {
            pto.set(false);
            moveIntake(0, 0, 0);
        }

        wait(20, msec);
    }
    //}
}

string autons[] = {"Skills", "Red Left", "Red Right", "Blue Left", "Blue Right"};

int auton(string selected_auton) {
    if (selected_auton == "Skills") {
        chassis.move(12);
        return 0;
    } else if (selected_auton == "Red Left") {
        return 0;
    } else if (selected_auton == "Red Right") {
        return 0;
    } else if (selected_auton == "Blue Left") {
        return 0;
    } else if (selected_auton == "Blue Right") {
        return 0;
    }
    return 1;
}

string selectedAuton;

std::string auton_menu() {
    int autoPos = 0;
    bool autoSelected = false;

    while (!autoSelected) {
        
        if (controller1.ButtonRight.pressing()) {
            while (controller1.ButtonRight.pressing()) {}
            if (autoPos != end(autons) - begin(autons) - 1) {
                autoPos ++;
            }
        }

        if (controller1.ButtonLeft.pressing()) {
            while (controller1.ButtonLeft.pressing()) {}
            if (autoPos != 0) {
                autoPos --;
            }
        }

        controller1.Screen.clearScreen();
        controller1.Screen.setCursor(1, 1);
        ostringstream autonNum;
        autonNum << autoPos + 1;
        string displayauto= ""+autonNum.str()+". "+autons[autoPos]; //Display selected auton
        controller1.Screen.print(displayauto.c_str());
        controller1.Screen.newLine();
        controller1.Screen.print("Run: A");
        
        if (controller1.ButtonA.pressing()) {
            return displayauto;
        }

        //Controller.Screen.newLine();
        //Controller.Screen.print("Inertial Rotation: %f",Inertial.heading(deg));
    }
    return "No auton selected";
}

bool compMode = false;

int selectAuton() {
    
    // display options on controller
    controller1.Screen.clearScreen();
    controller1.Screen.setCursor(1, 1);
    controller1.Screen.print(" Comp  A");
    controller1.Screen.newLine();
    controller1.Screen.print(" Test   B");
    controller1.Screen.newLine();
    controller1.Screen.print(" Driver >");


    while (1) {
        if (controller1.ButtonA.pressing()) {
            compMode = true; break;
        } if (controller1.ButtonB.pressing()) {
            compMode = false; break;
        } if (controller1.ButtonRight.pressing()) {
            driverControl = true; break;
        }
    }

    if (driverControl) {
        usercontrol(); return 0;
    }

    wait(250, msec);
    selectedAuton = auton_menu();

    controller1.Screen.clearScreen();
    controller1.Screen.setCursor(1,1);
    string displayedAuton = "Run \"" + selectedAuton + "\"?";
    controller1.Screen.print(displayedAuton.c_str());
    controller1.Screen.newLine();
    controller1.Screen.print("Confirm A");
  
    while (1) {
        if (controller1.ButtonA.pressing()) {
            return 0;
        }
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
    controller1.ButtonDown.pressed(ctrlKillSwitch);


    // controller1.ButtonRight.pressed(ctrlSortSwap);

    // vexcodeInit();
    // default_constants();
    // optic.setLightPower(100, percent); 
    // optic.setLight(ledState::on); 
    // Brain.Screen.clearScreen();

    // cout << "033[2J";

    // imu.calibrate();
    // // Set up callbacks for autonomous and driver control periods.
    // intake.setVelocity(100, pct);

    // l.resetPosition();
    // r.resetPosition();
    // imu.resetHeading();
    // imu.resetRotation();

    // selectAuton();
    // if (compMode) {
    //     controller1.Screen.clearScreen();
    //     controller1.Screen.setCursor(1,1);
    //     controller1.Screen.print("Waiting to start...");
    //     while (1) { //check if comp switch enabled for auton
    //         wait(50, msec);
    //         if (Competition.isAutonomous() && Competition.isEnabled()){
    //             break;
    //         }
    //     }
    //     auton(selectedAuton);
    //     while (1) { //check if comp switch enabled for driver
    //         wait(50, msec);
    //         if (Competition.isDriverControl() && Competition.isEnabled()){
    //             break;
    //         }
    //     }
    //     usercontrol();
    //     driverControl = true;
    // } else { //Regular/test mode
    //     cout << "Run";
    //     int autonRun = auton(selectedAuton); //run auton
    //     if (autonRun != 2){
    //         usercontrol(); //Instantly run auton
    //     }        
    // }

    // Run the pre-autonomous function.
    pre_auton();

    // Prevent main from exiting with an infinite loop.
    while (true) {
        wait(100, msec);
    }
}