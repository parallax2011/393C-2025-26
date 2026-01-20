#pragma once
#include "vex.h"
#include "lib/drive.h"

class Drive;
extern Drive chassis;

void default_constants() {      
    // chassis.set_drive_constants(12, 1.2, 0, 4.5, 0); // 1.2,4.5
    // chassis.set_heading_constants(6, .4, 0, 1, 0);
    // chassis.set_turn_constants(12, 0.4, 0.03, 3.1, 15);
    // chassis.set_swing_constants(12, 1, 0.01, 6, 0);

    // chassis.set_drive_exit_conditions(0.5, 100, 2000);
    // chassis.set_turn_exit_conditions(0.5, 100, 1000);
    // chassis.set_swing_exit_conditions(1, 200, 3000);
}

void autoSKILLS() {

    // match loader 1
    std::cout << "-----------------------------------------" << std::endl;
    chassis.move(34); std::cout << (chassis.get_left_position_in() + chassis.get_right_position_in()) / 2 << std::endl;
    chassis.kTurn(-88.5, 12, .33, .035, 3.1, 15);
    std::cout << std::endl << "After turn:       " << imu.rotation() << " " << chassis.get_absolute_heading() - 360 << std::endl;
    auto task0 = []() {scraper.set(true); intake();}; thread t_task0 = thread(task0);
    wait(2000, msec);
    chassis.lin_timeout = 2000; chassis.lin_max = 6; chassis.arc(6, -87.8);
    wait(1500, msec);
    std::cout << "After loading:    " << imu.rotation() << " " << chassis.get_absolute_heading() - 360 << std::endl;

    // first scoring on long goal 1
    chassis.move(-10); 
    scraper.set(false);
    wait(200, msec);
    chassis.turn(0); std::cout << imu.rotation() << " " << chassis.get_absolute_heading() - 360 << std::endl;

    // arc code
    chassis.setLinPID(12, 1, 0, 7, 0); chassis.setThetaPID(10.5, 0.4, 0, 1, 0);
    auto task1 = []() {descorer.set(true);}; thread t_task1 = thread(task1);
    chassis.arc(75, 84.5);
    chassis.setLinPID(12, 1, 0, 7, 0); chassis.setThetaPID(8.5, 0.4, 0, 1, 0); chassis.arc(24, 180);

    auto task2 = []() {descorer.set(false);}; thread t_task2 = thread(task2);
    double dist1 = dist.objectDistance(inches); std::cout << "DISTANCE: " << dist1 << std::endl; chassis.move(18.5 - dist1);
    wait(200, msec);
    chassis.turn(90);
    auto task3 = []() {scoreLongGoal();}; thread t_task3 = thread(task3);
    chassis.setLinPID(12, 1, 0, 7, 0); chassis.setThetaPID(6, 0.4, 0, 1, 0); chassis.lin_timeout = 2000; chassis.move(-22, 4);
    wait(1000, msec);
    // chassis.setLinPID(12, 1, 0, 7, 0); chassis.setThetaPID(6, 0.4, 0, 1, 0); chassis.lin_timeout = 600; chassis.move(-20, 6);

    // match loader 2
    t_task3.interrupt(); auto task4 = []() {wait(50, msec); scraper.set(true); intake();}; thread t_task4 = thread(task4);
    chassis.move(27.5, 4);
    wait(1000, msec);

    // // match loader 2
    // chassis.set_drive_constants(12, 1, 0, 7, 0); // 1.2,4.5
    // chassis.set_heading_constants(6, 0.4, 0, 1, 0); // kp0.4, kd1

    // auto abdulasiz = []() { wait(300, msec); scraper.set(true);}; thread tabdulasiz = thread(abdulasiz);
    // chassis.lin_max = 6; chassis.arc(30, 90);
    // intake();
}
