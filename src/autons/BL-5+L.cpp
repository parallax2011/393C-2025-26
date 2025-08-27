#include <vex.h>

void blue_left_5_ladder() {

    //moveLift(500, 100);
    //wait(2000, msec);
    
    chassis.turn_kd = 3.8;
    chassis.turn_settle_error = 1;//1
    chassis.turn_settle_time = 200;//200

    intake.setMaxTorque(100, pct);
    thread COLOR_SORT_FILTER_RED = thread(filterRed);

    // clamp mogo
    chassis.move(-23, 9);
    mogo.set(true);
    wait(200, msec);

    // preload & ring 2
    chassis.turn_settle_error = 0.5;//1
    chassis.turn_settle_time = 100;//200
    chassis.turn(108);
    moveIntake(12);
    chassis.move(26);
    wait(300, msec);

    // corner ring 1
    chassis.turn(22);
    auto liftVert = []() { moveLift(500, 100); };
    thread liftUp = thread(liftVert);
    chassis.drive_timeout = 1500;
    chassis.move(36, 8);
    chassis.drive_timeout = 700;
    moveIntake(12);
    chassis.move(12, 12);//4.5, 5, 7

    // corner ring 2
    // chassis.move(-6.5, 12);//-4.5
    // intakePiston.set(true);
    // wait(250, msec);
    // chassis.drive_timeout = 1500;
    // chassis.move(6.75, 3);//5.5
    // intakePiston.set(false);
    // chassis.move(-8.5, 12);
    // wait(200, msec);
    // intakePiston.set(true);
    // chassis.drive_timeout = 1200;
    // wait(300, msec);
    // chassis.move(6.75, 3);
    // intakePiston.set(false);

    // // 2 stack ring
    // chassis.move(-12.5, 12);
    // chassis.turn(-90);
    // intakePiston.set(true);
    // chassis.move(40);
    // chassis.move(5, 6);
    // intakePiston.set(false);
    // chassis.move(-10, 8);

    chassis.move(-12);
    chassis.turn(-158);
    thread liftDown = thread(lift_reset);
    auto dropGoal = []() { wait(250, msec); mogo.set(false); };
    thread t_dropGoal = thread(dropGoal);
    chassis.move(20);
    
    wait(300, msec);
    chassis.turn(-22);

    // chassis.move(-11.5, 12);
    // //doink.set(true);
    // chassis.turn(-90, 12);
    // intakePiston.set(true);
    // chassis.move(30);
    // //doink.set(false);
    // chassis.move(15, 3);
    // chassis.set_drive_constants(8.5, 1.2, 0, 8, 0);
    // chassis.set_heading_constants(12, 0.5, 0, 6.5, 0);
    // intakePiston.set(false);
    // lift.setStopping(brake);
    // auto liftToLadder = []() { moveLift(500, 100); };
    // thread liftThread = thread(liftToLadder);
    // chassis.move(-10, 8);
    
    // // ladder touch
    // chassis.set_drive_constants(10, 1.2, 0, 8, 0);
    // chassis.set_heading_constants(12, 0.5, 0, 6.5, 0);
    // chassis.arc(17, -158);

    // // ladder touch
    // chassis.set_drive_constants(9, 1.2, 0, 8, 0);
    // chassis.set_heading_constants(12, 0.5, 0, 6.5, 0);
    // chassis.arc(-37, 40);
    // moveIntake(0);

    // end
    wait(200, msec);
    l.stop(brake);
    r.stop(brake);
    COLOR_SORT_FILTER_RED.interrupt();
}