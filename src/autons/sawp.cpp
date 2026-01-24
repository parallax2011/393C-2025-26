#pragma once
#include "vex.h"
#include "lib/drive.h"

class Drive;
extern Drive chassis;

void autoLSAWP() {
    
    // high goal
    //scoreMidGoal();

    chassis.setLinPID(12, 1, 0, 7, 0); chassis.setThetaPID(6, 0.4, 0, 1, 0); chassis.arc(-39, -36);
    // chassis.move(-30.5);
    // chassis.right_swing_to_angle(28.8, 12, 1, 300, 1000, 1, 0, 5, 0);
    // std::cout << "After swing:     " << imu.rotation() << " " << chassis.get_absolute_heading() - 360 << std::endl;
    hood.set(true); moveIntake(-6, -12);
    auto taska = []() { wait(300, msec); moveIntake(0, 0); }; thread t_taska = thread(taska);

}

void autoLeft() {
        std::cout << "-----------------------------------------" << std::endl;
    chassis.move(33);//33
    chassis.ang_timeout = 2000; chassis.turn(-88.5); std::cout << "Angle: " << imu.rotation() << endl; //kTurn(95, 12, .33, .035, 3.1, 15);
    auto taskA = []() {scraper.set(true); moveIntake(-12, -12); }; thread t_taskA = thread(taskA); wait(300, msec);
    chassis.move(6, 6, 700);
    wait(100, msec);
    
    // // long goal
    t_taskA.interrupt(); auto taskC = []() { wait(500, msec); scoreLongGoal(); }; thread t_taskC = thread(taskC);
    chassis.arc(-27, -91, 6, 6, 2000);
    wait(1400, msec);
    chassis.set_heading(0);

    // t_taskC.interrupt(); auto taskD = []() { wait(300, msec); scraper.set(false); intake(); }; thread t_taskD = thread(taskD);
    auto taskD = []() { wait(300, msec); scraper.set(false); hood.set(false); }; thread t_taskD = thread(taskD);

    chassis.arc(37, -125, 3, 4, 3000); t_taskC.interrupt(); wait(100, msec);
    chassis.move(-10);
    chassis.turn(43);
    chassis.move(-20);
    t_taskD.interrupt(); hood.set(false); trapdoor.set(true); moveIntake(-12, 12); wait(1000, msec);

    l.stop();
    r.stop();

}


void autoRight() {
    
    // match loader
    std::cout << "-----------------------------------------" << std::endl;
    chassis.move(33);//33
    chassis.ang_timeout = 2000; chassis.turn(88.5); std::cout << "Angle: " << imu.rotation() << endl; //kTurn(95, 12, .33, .035, 3.1, 15);
    auto taskA = []() {scraper.set(true); moveIntake(-12, -12); }; thread t_taskA = thread(taskA); wait(300, msec);
    chassis.move(6, 6, 700);
    
    // // long goal
    t_taskA.interrupt(); auto taskC = []() { wait(500, msec); scoreLongGoal(); }; thread t_taskC = thread(taskC);
    chassis.arc(-27, 91, 6, 6, 2000);
    wait(1400, msec);
    chassis.set_heading(0);

    // t_taskC.interrupt(); auto taskD = []() { wait(300, msec); scraper.set(false); intake(); }; thread t_taskD = thread(taskD);
    auto taskD = []() { wait(300, msec); scraper.set(false); hood.set(false); }; thread t_taskD = thread(taskD);

    chassis.arc(43, 130, 3, 4, 3000); t_taskC.interrupt(); wait(100, msec); moveIntake(0, 0);
    chassis.move(-10);
    chassis.turn(124);
    chassis.move(9);
    t_taskD.interrupt(); hood.set(true); trapdoor.set(false); moveIntake(12, 12); wait(1000, msec);  

    l.stop();
    r.stop();
    
}