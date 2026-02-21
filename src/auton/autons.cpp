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
    // chassis.rightSwing(28.8, 12, 1, 300, 1000, 1, 0, 5, 0);
    // std::cout << "After swing:     " << imu.rotation() << " " << chassis.getAbsTheta() - 360 << std::endl;
    hood.set(true); moveIntake(-6, -12);
    auto taska = []() { wait(300, msec); moveIntake(0, 0); }; thread t_taska = thread(taska);

}

void autoRight() {
    chassis.move(33.6);
    chassis.turn(88.5);
    auto task0 = []() {scraper.set(true); intake();}; thread t_task0 = thread(task0);
    wait(600, msec);
    chassis.lin_timeout = 2000; chassis.lin_max = 6; chassis.arc(7, 88.5);
    wait(600, msec);

    auto task5 = []() { hood.set(true); wait(2000, msec); trapdoor.set(true); moveIntake(-12, -12); }; thread t_task5 = thread(task5);
    chassis.arc(-29, 91); wait(2000, msec);

    chassis.set_heading(0);
    chassis.arc(18, 90, 6, 10, 3000); moveIntake(0, 0);
    l.setStopping(brake); r.setStopping(brake);
    chassis.turn(180);
    scraper.set(false);
    chassis.move(27, 4);
    wait(100, msec);
    descorer.set(false);
    chassis.drive_stop(brake);

}

void autoLeft_4_5() {
    // settings
    std::cout << "-----------------------------------------" << std::endl;
    chassis.set_heading(-19); imu.setHeading(341, deg); imu.setRotation(-19, deg);

    // get first 3 blocks
    intake();
    chassis.move(36, 4, 3, 80, 2000); // chained
    wait(500, msec);

    // score 3 blocks
    auto task0 = []() { 
        wait(400, msec); trapdoor.set(true); wait(400, msec); moveIntake(-12, 12); }; thread t_task0 = thread(task0);
    chassis.arc(-16.3, -127.7, 3, 7.5, 3000); wait(400, msec);

    // get 3 blocks in match loader
    chassis.move(50, 12, 3, 80, 2000); // chassis.move(48, -123.3, 12, 6, 3000);
    chassis.turn(-170.5, 12, 2, 160, 2000);
    scraper.set(true); intake(); wait(400, msec);
    chassis.arc(9, -170.5, 6, 6, 2000); wait(400, msec);

    // score 4 blocks on long goal
    auto task1 = []() { 
        hood.set(true); wait(1000, msec); trapdoor.set(true); moveIntake(-12, -12); }; thread t_task1 = thread(task1);
    chassis.move(-30, 8);
    scraper.set(false);
    wait(1200, msec);

    // push blocks in control zone
    chassis.set_heading(0);
    chassis.arc(19.4, -90, 6, 10, 3000); moveIntake(0, 0);
    l.setStopping(brake); r.setStopping(brake);
    chassis.arc(-27, 0, 5, 7.5, 3000);
    wait(100, msec);
    descorer.set(false);
    chassis.drive_stop(brake);

}

void vectors() {
    std::cout << "-----------" << std::endl;
    std::cout << "Theta: " << imu.rotation() << std::endl;
    std::cout << "Pos: " << (chassis.getLeftPos() + chassis.getRightPos()) / 2 << std::endl;
    l.resetPosition(); r.resetPosition();
}

void autoRight4C() {
    // settings
    std::cout << "-----------------------------------------" << std::endl;
    Brain.Timer.reset();

    // intake 3 blocks <- match loader
    chassis.set_heading(180); imu.setHeading(180, deg); imu.setRotation(180, deg);

    chassis.setLin(12, 1, 0, 7.275, 0); chassis.setLinExits(1.5, 150, 2000); chassis.setAng(6, 0.4, 0, 1.5, 0);
    chassis.move(-30.5); vectors();
    chassis.setTurn(12, 0.37, 0.03, 2.9, 15); chassis.setTurnExits(1, 200, 2000);
    chassis.turn(88.5); vectors();
    scraper.set(true); intake(); wait(300, msec);
    chassis.arc(10, 88.5, 12, 6, 1000); vectors();

    // // score 4 blocks -> long goal
    auto taskA = []() { 
        wait(400, msec); hood.set(true); wait(650, msec); trapdoor.set(true); moveIntake(-12, -12); }; thread t_taskA = thread(taskA);
    chassis.arc(-28.2, 95.5, 12, 12, 3000); vectors(); //-28.2, 94, 12, 12, 3000 //o4
    wait(1650, msec);

    // push 4 blocks -> control zone
    chassis.set_heading(0); scraper.set(false);
    chassis.setAng(6, 0.4, 0, 2.6, 0); chassis.arc(12.9, 90, 9, 12, 3000); moveIntake(0, 0); hood.set(false); trapdoor.set(false); vectors();
    chassis.turn(177); vectors();
    chassis.move(25, 12);
    chassis.turn(150);
    wait(200, msec);
    chassis.drive_stop(brake);
}

void r7() {

    // settings
    chassis.setLin(12, 1, 0, 7.275, 0); chassis.setLinExits(1.5, 150, 2000); chassis.setAng(6, 0.4, 0, 1.5, 0);
    chassis.setTurn(12, 0.37, 0.03, 2.9, 15); chassis.setTurnExits(1, 200, 2000);

    // intake 3 blocks
    intake();
    chassis.arc(36, 57, 4, 1.75, 2000); vectors();
    wait(500, msec);
    descorer.set(true);

    // match loader
    chassis.turn(-45); vectors();
    chassis.move(-31); vectors(); //-31
    chassis.turn_kd = 3.1; chassis.turn(184); vectors(); chassis.turn_kd = 2.9; //kd1 = 3.1
    scraper.set(true); vectors();
    chassis.move(17.6, 12); vectors();
    wait(500, msec);

    // score on long goal
    auto taskA = []() { 
        wait(400, msec); hood.set(true); wait(400, msec); trapdoor.set(true); moveIntake(-12, -12); }; thread t_taskA = thread(taskA);
    chassis.move(-28); vectors(); //          up here 650
    wait(2800, msec);

    // push 7 blocks in
    chassis.set_heading(0); scraper.set(false);
    chassis.setAng(6, 0.4, 0, 2.6, 0); chassis.arc(12.9, 90, 12, 10, 3000); 
    float dist1 = dist.objectDistance(inches);
    chassis.move(29.85 - dist1); vectors();
    moveIntake(0, 0); hood.set(false); trapdoor.set(false); vectors();
    chassis.turn(177); vectors(); descorer.set(false);
    chassis.move(32, 12);//25
    wait(200, msec);
    chassis.drive_stop(brake);


    // chassis.setAng(1, 1, 0, 2.6, 0);
    // chassis.arc(28, 23, 5, 0.75, 5000); vectors();
}

void autoLeft_6_3() {
    // settings
    std::cout << "-----------------------------------------" << std::endl;

    Brain.Timer.reset();

    // get first 3 blocks
    intake();
    chassis.lin_settle_error = 3; chassis.lin_settle_time = 80; 
    chassis.arc(33, -30, 4, 3, 2000); vectors(); 

    // get 2 blocks under goal
    chassis.lin_settle_error = 1.5; chassis.lin_settle_time = 300; chassis.ang_kd = 1.5;
    chassis.arc(23.2, -60, 3, 7, 3000); vectors(); //21.65 dist vector
    // chassis.lin_settle_error = 1; chassis.lin_settle_time = 300; chassis.move(3); vectors();
    // chassis.leftSwing(-50);
    wait(500, msec);

    // score 4 blocks on mid goal
    auto task0 = []() { 
        wait(650, msec); trapdoor.set(true); moveIntake(-12, 12); wait(150, msec); }; thread t_task0 = thread(task0);
    chassis.ang_kd = 1.8, chassis.arc(-29.5, -124.8, 12, 6.4, 1600); wait(600, msec); //29.5


    std::cout << "Time: " << Brain.Timer.time(sec) << std::endl;
    
}

void auto_left_4_5() {
    // settings
    std::cout << "-----------------------------------------" << std::endl;
    chassis.set_heading(-19); imu.setHeading(341, deg); imu.setRotation(-19, deg);

    // get first 3 blocks
    intake();
    chassis.move(33, 4, 3, 80, 2000); // chained; moves ~31.5 consistently
    
    // get 2 blocks under goal
    chassis.arc(22.5, -49.8, 3, 7, 2400); //21.65 dist
    trapdoor.set(true);
    
    // score 4 blocks on mid goal
    auto task0 = []() { 
        wait(650, msec); moveIntake(-8, -8); wait(150, msec); hood.set(true); }; thread t_task0 = thread(task0);
    chassis.ang_kd = 1.8, chassis.arc(-29.5, -124.8, 12, 6.4, 1600); wait(600, msec); //29.5

    // get 3 blocks in match loader
    moveIntake(0, 0);
    chassis.move(50.2, 12, 1.5, 300, 2000); // prev dist = 48, 47.75 chassis.move(48, -123.3, 12, 6, 3000);
    chassis.turn(-170.5, 12, 0.8, 300, 2000);
    scraper.set(true); intake(); wait(400, msec);
    chassis.arc(13, -170.5, 6, 6, 1200); //wait(400, msec); //12

    // score 4 blocks on long goal
    auto task1 = []() { 
        wait(400, msec); hood.set(true); wait(400, msec); trapdoor.set(true); moveIntake(-12, -12); }; thread t_task1 = thread(task1);
    chassis.move(-28, 8);
    scraper.set(false);
    wait(1350, msec);

    // push blocks in control zone
    chassis.set_heading(0);
    chassis.arc(20.4, -90, 6, 10, 3000); moveIntake(0, 0); //DIST=19.4
    l.setStopping(brake); r.setStopping(brake);
    chassis.arc(-27, 0, 5, 7.5, 3000);
    wait(100, msec);
    descorer.set(false);
    chassis.drive_stop(brake);
}

// void autoLeft() {
//     std::cout << "-----------------------------------------" << std::endl;
//     chassis.move(33);//33
//     chassis.turn_timeout = 2000; chassis.turn(-88.5); std::cout << "Angle: " << imu.rotation() << endl; //kTurn(95, 12, .33, .035, 3.1, 15);
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
//     chassis.turn_timeout = 2000; chassis.turn(88.5); std::cout << "Angle: " << imu.rotation() << endl; //kTurn(95, 12, .33, .035, 3.1, 15);
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