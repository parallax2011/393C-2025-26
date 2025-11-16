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


void autoRIGHT() {
    auto t = []() {intake.setMaxTorque(100, pct);}; thread T = thread(t);

    // match loader
    chassis.move(30.3);//32.3
    basket();
    chassis.turn(88);
    scraper.set(true);
    wait(1000, msec);
    chassis.drive_timeout = 1000; chassis.move(7.5, 3);
    wait(100, msec);
    chassis.move(-13.5);
    scraper.set(false);
    chassis.drive_timeout = 2300;
    chassis.turn(213);
    
    // auto t2 = []() { wait(1000, msec); scraper.set(true); }; thread T2 = thread(t2); //800
    chassis.move(37, 3); //23, 26, 23
    wait(300, msec);
    
    // long goal and push
    chassis.drive_timeout = 1800;
    chassis.move(-41, 12);//v=7
    scraper.set(false);
    chassis.turn(-89);
    longGoal();
    l.setStopping(coast);
    r.setStopping(coast);
    chassis.move(13);
    // wait(4000, msec);
    // chassis.move(-10, 12);
    // chassis.drive_timeout = 5000;
    // chassis.move(20, 12);

}

void skills() {

    auto t = []() {intake.setMaxTorque(100, pct);}; thread T = thread(t);

    // match loader
    chassis.move(30.3);//32.3
    basket();
    chassis.turn(88);
    scraper.set(true);
    wait(1000, msec);
    chassis.drive_timeout = 1200; chassis.move(6.5, 3);
    wait(1500, msec);

    chassis.move(-13.5);
    chassis.move(14);
    wait(2000, msec);

    chassis.move(-13);
    scraper.set(false);
    chassis.turn(178);

    // chassis.move(10);

    double dist0 = dist.objectDistance(inches);
    std::cout << "DISTANCE: " << dist0 << std::endl;
    chassis.drive_settle_error = 0.2; chassis.drive_settle_time = 300; chassis.move(17.6 - dist0);
    wait(200, msec);

    chassis.turn(-90);
    chassis.move(11);
    longGoal();
    wait(4500, msec);

    chassis.move(-10);
    chassis.turn(-5.6);
    chassis.set_heading_constants(10.5, 0.4, 0, 1, 0);
    chassis.set_drive_exit_conditions(0.5, 200, 3000);
    chassis.move(-104, 10);

    double dist1 = dist.objectDistance(inches);
    std::cout << "DISTANCE: " << dist1 << std::endl;
    chassis.drive_settle_error = 0.2; chassis.drive_settle_time = 300; chassis.move(17 - dist1);
    wait(200, msec);

    chassis.turn(81);//83
    scraper.set(true);
    wait(1000, msec);
    basket();
    chassis.drive_timeout = 1200; chassis.move(15, 4);
    wait(1200, msec);

    chassis.move(-13.5);
    chassis.move(12.5, 4);
    wait(1200, msec);

    chassis.move(-13);
    scraper.set(false);
    chassis.turn(-7);

    // chassis.move(10);

    double dist2 = dist.objectDistance(inches);
    std::cout << "DISTANCE: " << dist2 << std::endl;
    chassis.drive_settle_error = 0.2; chassis.drive_settle_time = 300; chassis.move(15 - dist2);
    wait(200, msec);

    chassis.turn(-91);
    chassis.move(11.5);
    longGoal();
    wait(3000, msec);
    moveIntake(0, 0);
    chassis.move(-10);
    longGoal();
    chassis.move(10);
    wait(3000, msec);

    chassis.set_heading(-90);
    chassis.move(-11);
    chassis.turn(43);
    chassis.move(18);
    chassis.turn(23);
    chassis.move(12);
    outtake();
    chassis.turn(13);
    chassis.move(42);
    wait(300, msec);
    chassis.move(-10);
    

    //-11
    //132 from last ang
    //2 from prev ang
    //18 to not have scraper touch wall

    //-20s kinda thing (ang)
    // 12 fwd
    // -7 maybe?
    // bulldoze
    //

}