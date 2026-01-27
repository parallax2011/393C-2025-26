#pragma once
#include "vex.h"
#include "ROBOT.h"

class Drive;
extern Drive chassis;

void default_constants() {}

void autoSKILLS() {

    // match loader 1
    std::cout << "-----------------------------------------" << std::endl;
    chassis.move(33); std::cout << (chassis.getLeftPos() + chassis.getRightPos()) / 2 << std::endl;
    chassis.kTurn(-88.5, 12, .33, .035, 3.1, 15);
    std::cout << std::endl << "After turn:       " << imu.rotation() << " " << chassis.getAbsTheta() - 360 << std::endl;
    auto task0 = []() {scraper.set(true); intake();}; thread t_task0 = thread(task0);
    wait(600, msec);
    chassis.lin_timeout = 2000; chassis.lin_max = 6; chassis.arc(7.5, -87.8);
    wait(1500, msec);
    std::cout << "After loading:    " << imu.rotation() << " " << chassis.getAbsTheta() - 360 << std::endl;

    // first scoring on long goal 1
    chassis.move(-10); 
    scraper.set(false);
    wait(200, msec);
    chassis.turn(0); std::cout << imu.rotation() << " " << chassis.getAbsTheta() - 360 << std::endl;

    // arc code
    chassis.setLin(12, 1, 0, 7, 0); chassis.setAng(10.5, 0.4, 0, 1, 0);
    auto task1 = []() {descorer.set(true);}; thread t_task1 = thread(task1);
    chassis.arc(75, 84.5);
    chassis.setLin(12, 1, 0, 7, 0); chassis.setAng(8.5, 0.4, 0, 1, 0); chassis.arc(24, 180);

    auto task2 = []() {descorer.set(false);}; thread t_task2 = thread(task2);
    double dist1 = dist.objectDistance(inches); std::cout << "DISTANCE: " << dist1 << std::endl; chassis.move(20.3 - dist1);
    wait(200, msec);
    chassis.turn(90);
    auto task3 = []() {scoreLongGoal();}; thread t_task3 = thread(task3);
    chassis.setLin(12, 1, 0, 7, 0); chassis.setAng(6, 0.4, 0, 1, 0); chassis.lin_timeout = 2000; chassis.move(-22, 4);
    wait(1300, msec);

    // match loader 2
    t_task3.interrupt(); auto task4 = []() {wait(50, msec); scraper.set(true); intake();}; thread t_task4 = thread(task4);
    chassis.move(28.75, 4); // potentially add more
    wait(1500, msec);

    // 2nd score on long goal 1
    auto task5 = []() { hood.set(true); wait(1000, msec); trapdoor.set(true); moveIntake(-12, -12); }; thread t_task5 = thread(task5);
    chassis.move(-28.75, 6);
    wait(1300, msec);//1800
    chassis.set_heading(1.5); imu.resetHeading(); imu.resetRotation();

    // match loader 3

    // hood.set(true);
    chassis.lin_timeout = 2000; chassis.move(-10);
    chassis.move(15);
    chassis.turn(-88.5); //-1.5; check angle when uncommenting other code
    auto task5_5 = []() {scraper.set(false); intake(); wait(200, msec); }; thread t_task_5 = thread(task5_5);
    chassis.lin_timeout = 4000; chassis.move(-100);
    double dist2 = dist.objectDistance(inches); std::cout << "DISTANCE: " << dist2 << std::endl; chassis.move(19.5 - dist2); //20.3-dist2
    chassis.turn(0);
    auto task6 = []() {scraper.set(true); intake();}; thread t_task6 = thread(task6);
    wait(300, msec); //prev1500 and got 41pts
    chassis.move(26, 3); // potentially add more
    wait(1500, msec);
    // auto task7 = []() { hood.set(true); wait(300, msec); trapdoor.set(true); moveIntake(-12, -12); }; thread t_task7 = thread(task7);
    // chassis.lin_max = 6; chassis.setLin(12, 1, 0, 7, 0); chassis.setAng(6, 0.4, 0, 1, 0); chassis.lin_timeout = 2000; chassis.move(-28.75);//91.5
    // wait(1800, msec);
    chassis.move(-10); 
    scraper.set(false);
    wait(200, msec);
    chassis.turn(90); std::cout << imu.rotation() << " " << chassis.getAbsTheta() - 360 << std::endl;

    // arc code
    chassis.setLin(12, 1, 0, 7, 0); chassis.setAng(10.5, 0.4, 0, 1, 0);
    auto task8 = []() {descorer.set(true);}; thread t_task8 = thread(task8);
    chassis.arc(75, 169.5); //84.5 init
    chassis.setLin(12, 1, 0, 7, 0); chassis.setAng(8.5, 0.4, 0, 1, 0); chassis.arc(24, -92);

    auto task9 = []() {descorer.set(false);}; thread t_task9 = thread(task9);
    double dist3 = dist.objectDistance(inches); std::cout << "DISTANCE: " << dist3 << std::endl; chassis.move(19.6 - dist3);
    wait(200, msec);
    chassis.turn(178);
    auto task10 = []() {scoreLongGoal();}; thread t_task10 = thread(task10);
    chassis.setLin(12, 1, 0, 7, 0); chassis.setAng(6, 0.4, 0, 1, 0); chassis.lin_timeout = 2000; chassis.move(-22, 4);
    wait(1000, msec);

    // match loader 4
    t_task10.interrupt(); auto task11 = []() {wait(50, msec); scraper.set(true); intake();}; thread t_task11 = thread(task11);
    chassis.move(28.75, 4); // potentially add more
    wait(1500, msec);

    // 2nd score on long goal 2
    auto task70000 = []() { hood.set(true); wait(1500, msec); trapdoor.set(true); moveIntake(-12, -12); }; thread t_task70000 = thread(task70000);
    chassis.move(-28, 6);
    wait(1800, msec);
    chassis.set_heading(0); imu.resetHeading(); imu.resetRotation();
    scraper.set(false); wait(500, msec);

    // clearing park zone and parking
    intake();
    chassis.setLin(12, 1, 0, 7, 0); chassis.setAng(6, 0.4, 0, 1, 0); chassis.arc(50, 79);
    wait(500, msec);
    chassis.move(30);
}