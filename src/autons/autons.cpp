#pragma once
#include "vex.h"
#include "lib/drive.h"

class Drive;
extern Drive chassis;

void default_constants() {      
    chassis.set_drive_constants(12, 1.2, 0, 4.5, 0); // 1.2,4.5
    chassis.set_heading_constants(6, .4, 0, 1, 0);
    chassis.set_turn_constants(12, 0.4, 0.03, 3.1, 15);
    chassis.set_swing_constants(12, 1, 0.01, 6, 0);

    chassis.set_drive_exit_conditions(0.5, 100, 2000);
    chassis.set_turn_exit_conditions(0.5, 100, 1000);
    chassis.set_swing_exit_conditions(1, 200, 3000);
}

// long moves - 6, 0.71, 1.2
// short moves - 6, 0.4, 1

void setHeadingConst(float max, float kp, float kd) {
    chassis.set_heading_constants(max, kp, 0, kd, 0);
}

void auto2() {
    chassis.set_drive_exit_conditions(1.5, 200, 2000);
    chassis.set_turn_exit_conditions(1, 200, 2000);

    chassis.set_heading(-27);

    auto t = []() {intake.setMaxTorque(100, pct);}; thread T = thread(t);
    basket();

    // blocks 1-3
    auto t2 = []() { wait(800, msec); scraper.set(true); }; thread T2 = thread(t2);
    chassis.move(23, 4);
    wait(200, msec);

    // match loader
    chassis.turn(-117.5);
    chassis.move(30, 12);
    chassis.turn(180);
    
    // blocks 4-6
    chassis.move(15, 10);
    wait(700, msec);

    // long goal
    chassis.move(-20);
    chassis.turn(-4);
    scraper.set(false);
    chassis.move(10);
    longGoal();


    //  // block 1
    // chassis.move(12.5);
    // thread t1 = thread(basket);
    // auto t2 = []() { wait(200, msec); scraper.set(true);};
    // chassis.turn(-19);
    // chassis.move(6.2, 6);

    // // blocks 2-3
    // chassis.turn(-37.2, 6);//-25
    // thread T2 = thread(t2);
    // chassis.move(10, 4);
    // wait(250, msec);


}

void autoLeft(std::string alliance) {
    
    chassis.set_drive_exit_conditions(1.5, 200, 2000);
    chassis.set_turn_exit_conditions(1, 200, 2000);

    auto t = []() {intake.setMaxTorque(100, pct);}; thread T = thread(T);

    if (alliance == "red") {
        thread COLOR_SORT_FILTER = thread(filterBlue);
    } else if (alliance == "blue") {
        thread COLOR_SORT_FILTER = thread(filterRed);
    }
    //13.3
    //-32;
    //12

     //13.7
     //-38.5

         //-78
    //23
    //10
    // chassis.move(12.8);
    // thread t1 = thread(basket);
    // auto t2 = []() { wait(500, msec); scraper.set(true);}; 
    // chassis.turn(-21);//-25, -27, -37,-19
    // thread T2 = thread(t2);
    // chassis.move(17, 2);//19.5


    // block 1
    chassis.move(12.5);
    thread t1 = thread(basket);
    auto t2 = []() { wait(200, msec); scraper.set(true);};
    chassis.turn(-19);
    chassis.move(6.2, 6);

    // blocks 2-3
    chassis.turn(-37.2, 6);//-25
    thread T2 = thread(t2);
    chassis.move(10, 4);
    wait(250, msec);

    // goal
    chassis.turn(-125);
    chassis.move(29);
    auto t3 = []() {scraper.set(false);}; thread T3 = thread(t3);
    chassis.turn(0);
    chassis.move(9);
    longGoal();
    wait(2700, msec);

    // descore
    chassis.move(-2);
    chassis.drive_max_voltage = 12;
    chassis.set_drive_constants(9, 1.2, 0, 4.5, 0);
    chassis.drive_timeout = 3000;
    setHeadingConst(9, 0.3, 1.7);
    chassis.arc(-18.5, 90);
    auto t700 = []() { descorer.set(true);}; thread T700 = thread(t700);
    chassis.turn(0);
    chassis.move(28, 9);

    wait(500, msec);
    l.stop();
    r.stop();
}

void autoRight(std::string alliance) {
    
    chassis.set_drive_exit_conditions(1.5, 200, 2000);
    chassis.set_turn_exit_conditions(1, 200, 2000);

    //auto t = []() {intake.setMaxTorque(100, pct);}; thread T = thread(T);

    if (alliance == "red") {
        thread COLOR_SORT_FILTER = thread(filterBlue);
    } else if (alliance == "blue") {
        thread COLOR_SORT_FILTER = thread(filterRed);
    }

    // block 1
    chassis.move(12.5);
    thread t1 = thread(basket);
    auto t2 = []() { wait(200, msec); scraper.set(true);};
    chassis.turn(19);
    chassis.move(6.2, 6);

    // blocks 2-3
    chassis.turn(37.2, 6);//25
    thread T2 = thread(t2);
    chassis.move(10, 4);
    wait(250, msec);

    // goal
    chassis.turn(125);
    chassis.move(31);
    auto t3 = []() {scraper.set(false);}; thread T3 = thread(t3);
    chassis.turn(0);
    chassis.move(9);
    longGoal();
    wait(2700, msec);


    // descore
    chassis.move(-2);
    moveIntake(0, 0, 0);
    chassis.drive_max_voltage = 12;
    chassis.set_drive_constants(9, 1.2, 0, 4.5, 0);
    chassis.drive_timeout = 3000;
    setHeadingConst(9, 0.3, 1.7);
    chassis.arc(-18.5, 90);
    auto t700 = []() { descorer.set(true);}; thread T700 = thread(t700);
    chassis.turn(0);
    chassis.move(28, 9);

    wait(500, msec);
    l.stop();
    r.stop();
}

void autoSkills() {
    chassis.set_drive_exit_conditions(1.5, 200, 2000);
    chassis.set_turn_exit_conditions(1, 200, 2000);

    auto t = []() {intake.setMaxTorque(100, pct);}; thread T = thread(T);

    chassis.move(35);
    wait(2000, msec);
    chassis.move(-10);
    wait(2000, msec);
    l.stop();
    r.stop();
}