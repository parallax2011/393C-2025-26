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

void left2() {
    chassis.set_drive_exit_conditions(1.5, 200, 2000);
    chassis.set_turn_exit_conditions(1, 200, 1000); //0.5,300,2000

    auto t = []() {intake.setMaxTorque(100, pct);}; thread T = thread(t);

    chassis.set_drive_exit_conditions(0.5, 200, 2000);
    chassis.set_turn_constants(12, 0.3, 0, 2, 15);

    chassis.drive_max_voltage = 7;

    // match loader
    chassis.drive_timeout = 900;//timeout=900 for v=12
    chassis.move(32.3, 12); //straight=32.3
    chassis.drive_timeout = 2000;
    basket();
    // wait(300, msec);
    // auto t1 = []() { scraper.set(true); }; thread T1 = thread(t1);
    chassis.turn_timeout = 700;
    chassis.turn(-83);
    chassis.turn_timeout = 1000;
    scraper.set(true);
    wait(300, msec);
    chassis.drive_timeout = 1000;
    chassis.move(12, 4);//v=4

    // go to field 3 blocks
    chassis.drive_timeout = 2000;
    chassis.move(-15, 12);//v=7
    scraper.set(false);
    chassis.turn(-206);
    auto t2 = []() { wait(1200, msec); scraper.set(true); }; thread T2 = thread(t2); //800
    chassis.move(37, 5.5); //23, 26, 23
    wait(300, msec);
    
    // long goal and push
    chassis.move(-38, 12);//v=7
    scraper.set(false);
    chassis.turn(93);
    longGoal();
    chassis.move(9);
    wait(4000, msec);
    chassis.move(-10, 12);
    chassis.drive_timeout = 5000;
    chassis.move(20, 12);
}

void right2() {
    chassis.set_drive_exit_conditions(1.5, 200, 2000);
    chassis.set_turn_exit_conditions(1, 200, 1000); //0.5,300,2000

    auto t = []() {intake.setMaxTorque(100, pct);}; thread T = thread(t);

    chassis.set_drive_exit_conditions(0.5, 200, 2000);
    chassis.set_turn_constants(12, 0.3, 0, 2, 15);

    chassis.drive_max_voltage = 7;

    // match loader
    chassis.drive_timeout = 900;//timeout=900 for v=12
    chassis.move(30.8, 12); //straight=32.3
    chassis.drive_timeout = 2000;
    basket();
    // wait(300, msec);
    // auto t1 = []() { scraper.set(true); }; thread T1 = thread(t1);
    chassis.turn_timeout = 700;
    chassis.turn(85);
    chassis.turn_timeout = 1000;
    scraper.set(true);
    wait(300, msec);
    chassis.drive_timeout = 1100;
    chassis.move(15, 4);//v=4

    // go to field 3 blocks
    chassis.drive_timeout = 2000;
    chassis.move(-15, 12);//v=7
    scraper.set(false);
    chassis.turn(210);
    auto t2 = []() { wait(1200, msec); scraper.set(true); }; thread T2 = thread(t2); //800
    chassis.move(37, 5.5); //23, 26, 23
    wait(300, msec);
    
    // long goal and push
    chassis.move(-38, 12);//v=7
    scraper.set(false);
    chassis.turn(-93);
    longGoal();
    chassis.move(12);
    wait(4000, msec);
    chassis.move(-10, 12);
    chassis.drive_timeout = 5000;
    chassis.move(20, 12);
}

void LEFT_6LG_DESCORE() {
    chassis.set_drive_exit_conditions(0.75, 200, 2000);
    chassis.set_turn_exit_conditions(0.5, 300, 2000);

    chassis.set_heading(-27);
    //auto t = []() {intake.setMaxTorque(100, pct);}; thread T = thread(t);
    basket();

    // blocks 1-3
    auto t2 = []() { wait(1050, msec); scraper.set(true); }; thread T2 = thread(t2); //800
    chassis.move(23, 4); //26, 23
    wait(200, msec);

    // match loader
    chassis.turn(-117.5);
    chassis.set_drive_exit_conditions(0.5, 300, 2000);
    chassis.move(31.2, 12); //42, 40, 30
    chassis.turn(-180); //-176.5, //-178.5
    chassis.set_drive_exit_conditions(0.75, 200, 2000);

    // blocks 4-6
    chassis.drive_timeout = 1000;
    chassis.move(19, 6); //23, 21, 18, v=10
    wait(500, msec); // could take this out
    chassis.drive_timeout = 2000;

    // long goal
    chassis.move(-20);
    scraper.set(false);
    // auto t3 = []() { wait(200, msec); longGoal(); }; thread T3 = thread(t3); //800
    chassis.turn(4); //8, 4
    //chassis.drive_timeout = 2500;
    chassis.drive_timeout = 600;
    longGoal();
    chassis.move(5.5); //6, 6.5, 7.5, 8.5, // 143, 11, 8.5
    wait(1900, msec);
    chassis.drive_timeout = 2000;

    // descore
    chassis.move(-2);
    chassis.drive_max_voltage = 12;
    chassis.set_drive_constants(9, 1.2, 0, 4.5, 0);
    setHeadingConst(9, 0.3, 2); //2.1, 1.7
    chassis.arc(-18.5, 90); //-19.2, -25, -22, -18.5
    chassis.turn(2);
    chassis.move(26.5, 7);
    descorer.set(true);

    // end
    wait(500, msec);
    l.stop();
    r.stop();
}

void RIGHT_DESCORE() {
    chassis.drive_stop(hold);
    chassis.set_drive_exit_conditions(0.75, 200, 2000);
    chassis.set_turn_exit_conditions(0.5, 300, 2000);

    chassis.set_heading(27);
    //auto t = []() {intake.setMaxTorque(100, pct);}; thread T = thread(t);
    basket();

    // blocks 1-3
    auto t2 = []() { wait(1050, msec); scraper.set(true); }; thread T2 = thread(t2); //800
    chassis.move(23, 4); //26, 23
    wait(200, msec);

    // match loader
    chassis.turn(117.5);
    chassis.set_drive_exit_conditions(0.5, 300, 2000);

    //chassis.set_drive_exit_conditions(0.5, 300, 2000);
    chassis.move(30.5, 12); //42, 40, 30
    chassis.turn(178.5);
    //chassis.set_drive_exit_conditions(0.75, 200, 2000);

    // blocks 4-6
    chassis.drive_timeout = 1000;
    // chassis.set_drive_exit_conditions(0.5, 300, 2000);
    chassis.move(19, 6.5); //23, 21, 18, v=10
    chassis.set_drive_exit_conditions(0.75, 200, 2000);
    wait(500, msec); // could take this out
    chassis.drive_timeout = 2000;

    // long goal
    chassis.move(-20);
    scraper.set(false);
    // auto t3 = []() { wait(200, msec); longGoal(); }; thread T3 = thread(t3); //800
    chassis.turn(-4); //8, 4
    //chassis.drive_timeout = 2500;
    chassis.drive_timeout = 600;
    longGoal();
    chassis.move(5.6); //6, 6.5, 7.5, 8.5, // 143, 11, 8.5
    wait(2500, msec);
    chassis.drive_timeout = 2000;

    // descore
    chassis.move(-2);
    chassis.drive_max_voltage = 12;
    chassis.set_drive_constants(9, 1.2, 0, 4.5, 0);
    setHeadingConst(9, 0.3, 2); //2.1, 1.7
    chassis.arc(-18, 90); //-19.2, -25, -22, -18.5
    chassis.turn(-2);
    chassis.move(23.5, 7);
    descorer.set(true);

    // end
    wait(500, msec);
    l.stop();
    r.stop();
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
    chassis.move(30);
    scraper.set(false);
    chassis.turn(0);
    chassis.move(9);
    longGoal();
    wait(2300, msec);

    // descore
    chassis.move(-2);
    chassis.drive_max_voltage = 12;
    chassis.set_drive_constants(9, 1.2, 0, 4.5, 0);
    chassis.drive_timeout = 3000;
    setHeadingConst(9, 0.3, 1.7);
    chassis.arc(-18.5, 90);
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
    chassis.set_turn_exit_conditions(1, 200, 1000); //0.5,300,2000

    auto t = []() {intake.setMaxTorque(100, pct);}; thread T = thread(t);

    chassis.set_drive_exit_conditions(0.5, 200, 2000);
    chassis.set_turn_constants(12, 0.3, 0, 2, 15);

    chassis.drive_max_voltage = 7;

    // match loader
    chassis.move(32.3);
    basket();
    wait(300, msec);
    // auto t1 = []() { scraper.set(true); }; thread T1 = thread(t1);
    chassis.turn(-83);
    scraper.set(true);
    wait(300, msec);
    chassis.move(12, 4);
    wait(1800, msec);

    // score 6 blocks -> long goal
    chassis.move(-15);
    wait(300, msec);
    scraper.set(false);
    wait(20, msec);
    chassis.turn(88);
    longGoal();
    chassis.move(13.5, 7);
    wait(2000, msec); //3200

    // get blocks, round 2
    chassis.move(-2);
    moveIntake(0, 0, 0);
    chassis.drive_max_voltage = 12;
    chassis.set_drive_constants(9, 1.2, 0, 4.5, 0);
    chassis.drive_timeout = 3000;
    setHeadingConst(9, 0.3, 1.7);
    chassis.arc(-34, 0); //-37
    chassis.turn(88);//90
    chassis.set_drive_constants(12, 1.2, 0, 4.5, 0); // 1.2,4.5
    chassis.drive_timeout = 2000;
    setHeadingConst(6, 0.4, 1);
    basket();
    chassis.drive_timeout = 4000;
    chassis.move(82, 5);

    // wall reset 1
    chassis.turn(180);
    chassis.drive_timeout = 2750;
    chassis.move(-60, 4);
    chassis.set_heading(0);
    chassis.drive_timeout = 2000;
    chassis.move(20.7, 4);

    // get 6 blocks from match loader 2
    chassis.turn(-90);
    scraper.set(true);
    chassis.move(20, 4);//12,8
    wait(1800, msec);

    // score blocks -> long goal
    chassis.move(-15);
    wait(300, msec);
    scraper.set(false);
    wait(20, msec);
    chassis.turn(98.5);
    chassis.set_heading(0);
    longGoal();
    chassis.move(7.7, 7);
    wait(5000, msec);

    // clear blue park zone
    // chassis.move(-10);
    // chassis.turn(-57);
    // chassis.move(16);
    // chassis.turn(-3);
    // lowGoal(); // outtake
    // chassis.move(43);

    // going towards blue park zone
    chassis.move(-10);
    chassis.turn(-130);
    chassis.move(28);
    chassis.turn(-110);
    wait(200, msec);

    // clear blue park zone
    moveIntake(-12, 0, 0);
    chassis.move(75);//v=10
    chassis.turn(0);
    chassis.move(-10);
    chassis.set_heading(0);
    chassis.drive_timeout = 3000;
    basket();
    chassis.move(135, 8);
    chassis.turn(75);
    moveIntake(-12, 0, 0);
    chassis.drive_timeout = 5000;
    chassis.move(50);
}