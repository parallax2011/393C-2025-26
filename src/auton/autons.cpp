#pragma once
#include "vex.h"
#include "ROBOT.h"

class Drive;
extern Drive chassis;

void autoLSAWP() {
    
    // high goal
    //scoreMidGoal();

    chassis.setLin(12, 1, 0, 7, 0); chassis.setAng(6, 0.4, 0, 1, 0); chassis.arc(-39, -36);
    // chassis.move(-30.5);
    // chassis.right_swing_to_angle(28.8, 12, 1, 300, 1000, 1, 0, 5, 0);
    // std::cout << "After swing:     " << imu.rotation() << " " << chassis.getAbsTheta() - 360 << std::endl;
    hood.set(true); moveIntake(-6, -12);
    auto taska = []() { wait(300, msec); moveIntake(0, 0); }; thread t_taska = thread(taska);

}


void auto_left_4_5() {
    // settings
    std::cout << "-----------------------------------------" << std::endl;
    chassis.set_heading(-19); imu.setHeading(341, deg); imu.setRotation(-19, deg);

    // get first 3 blocks
    intake();
    chassis.move(33, 4, 3, 80, 2000); // chained; moves ~31.5 consistently
    
    // get 2 blocks under goal
    chassis.arc(22.5, -49.8, 3, 7, 3000); //21.65 dist
    
    // score 4 blocks on mid goal
    auto task0 = []() { 
        wait(350, msec); trapdoor.set(true); moveIntake(-12, 12); wait(300, msec); moveIntake(-12, 6);}; thread t_task0 = thread(task0);
    chassis.arc(-31, -124.8, 12, 6.8, 1700); wait(1200, msec);
    moveIntake(0, 0);

    // get 3 blocks in match loader
    chassis.move(48, 12, 3, 80, 2000); // chassis.move(48, -123.3, 12, 6, 3000);
    chassis.turn(-170.5, 12, 3, 100, 2000);
    scraper.set(true); intake(); wait(500, msec);
    chassis.move(12, 6); wait(400, msec);

    // score 4 blocks on long goal
    auto task1 = []() { 
        hood.set(true); wait(1000, msec); trapdoor.set(true); moveIntake(-12, -12); }; thread t_task1 = thread(task1);
    chassis.move(-28, 8);
    scraper.set(false);

    // push blocks in control zone
    chassis.set_heading(0);
    chassis.arc(19.4, -90, 6, 10, 3000); moveIntake(0, 0);
    chassis.arc(-22, 0, 5, 7.5, 3000);
    wait(100, msec);
    descorer.set(false);
    chassis.drive_stop(brake);

}

// void autoLeft() {
//     std::cout << "-----------------------------------------" << std::endl;
//     chassis.move(33);//33
//     chassis.ang_timeout = 2000; chassis.turn(-88.5); std::cout << "Angle: " << imu.rotation() << endl; //kTurn(95, 12, .33, .035, 3.1, 15);
//     auto taskA = []() {scraper.set(true); moveIntake(-12, -12); }; thread t_taskA = thread(taskA); wait(800, msec);
//     chassis.move(7.5, 5, 700);
//     wait(100, msec);
    
//     // // long goal
//     t_taskA.interrupt(); auto taskC = []() { wait(500, msec); scoreLongGoal(); }; thread t_taskC = thread(taskC);
//     chassis.arc(-27, -91, 6, 6, 2000);
//     wait(1400, msec);
//     chassis.set_heading(0);

//     // t_taskC.interrupt(); auto taskD = []() { wait(300, msec); scraper.set(false); intake(); }; thread t_taskD = thread(taskD);
//     auto taskD = []() { wait(300, msec); scraper.set(false); hood.set(false); }; thread t_taskD = thread(taskD);

//     chassis.arc(37, -125, 3, 4, 3000); t_taskC.interrupt(); wait(100, msec); trapdoor.set(false);
//     chassis.move(-10);
//     chassis.setTurn(12, 0.37, 0.03, 3.1, 15); chassis.turn(46.5);//43
//     chassis.move(-23);
//     t_taskD.interrupt(); hood.set(false); trapdoor.set(true); moveIntake(-12, 12); wait(1000, msec);

//     l.stop();
//     r.stop();
// }

// void autoRight() {
    
//     // match loader
//     std::cout << "-----------------------------------------" << std::endl;
//     chassis.move(33);//33
//     chassis.ang_timeout = 2000; chassis.turn(88.5); std::cout << "Angle: " << imu.rotation() << endl; //kTurn(95, 12, .33, .035, 3.1, 15);
//     auto taskA = []() {scraper.set(true); moveIntake(-12, -12); }; thread t_taskA = thread(taskA); wait(300, msec);
//     chassis.move(6, 6, 700);
    
//     // // long goal
//     t_taskA.interrupt(); auto taskC = []() { wait(500, msec); scoreLongGoal(); }; thread t_taskC = thread(taskC);
//     chassis.arc(-27, 91, 6, 6, 2000);
//     wait(1400, msec);
//     chassis.set_heading(0);

//     // t_taskC.interrupt(); auto taskD = []() { wait(300, msec); scraper.set(false); intake(); }; thread t_taskD = thread(taskD);
//     auto taskD = []() { wait(300, msec); scraper.set(false); hood.set(false); }; thread t_taskD = thread(taskD);

//     chassis.arc(43, 130, 3, 4, 3000); t_taskC.interrupt(); wait(100, msec); moveIntake(0, 0);
//     chassis.move(-10);
//     chassis.turn(124);
//     chassis.move(9);
//     t_taskD.interrupt(); hood.set(true); trapdoor.set(false); moveIntake(12, 12); wait(1000, msec);  

//     l.stop();
//     r.stop();
    
// }