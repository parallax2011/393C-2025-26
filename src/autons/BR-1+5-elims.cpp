#include <vex.h>

void blue_right_1_5_elims() {
    std::cout << "AUTON BEGIN" << endl;

    chassis.turn_kd = 3.8;
    chassis.turn_settle_error = 1;//1
    chassis.turn_settle_time = 200;//200

    intake.setMaxTorque(100, pct);
    thread COLOR_SORT_FILTER_RED = thread(filterRed);

    // PRELOAD -> ALLIANCE STAKE
    thread liftGrabThread = thread(lift_grab);
    moveIntake(12);
    
    auto move_5_5in = []() { chassis.move(7.5); }; 
    thread move_5_5 = thread(move_5_5in);

    wait(500, msec);
    moveIntake(0);
    moveLift(LIFT_SCORE_POS, 100);
    wait(150, msec);

    // CLAMP MOGO
    chassis.move(-41, 5);
    thread liftResetThread = thread(lift_reset);
    mogo.set(true);
    wait(500, msec);
    moveIntake(12);

    // rings 1/2
    chassis.drive_settle_error = 1.2; //
    chassis.drive_settle_time = 50;
    chassis.turn_settle_error = 3; 
    chassis.turn_settle_time = 50; 
    chassis.turn(-164);
    chassis.move(14);
    wait(300, msec);
    chassis.set_heading_constants(11, 1, 0, 6.5, 0);
    chassis.arc(17, -120);

    // ring 3
    chassis.drive_kd = 10;
    chassis.set_heading_constants(11, 0.5, 0, 6.5, 0);
    chassis.arc(-29, 180);
    chassis.drive_kd = 8;
    chassis.turn_kd = 3.2;
    chassis.turn_settle_error = 3; 
    chassis.turn_settle_time = 25; 
    chassis.turn(-119);
    chassis.drive_settle_error = 1; //1.2
    chassis.drive_settle_time = 200;//50 
    chassis.move(10.5);

    // corner ring 1
    chassis.turn_settle_error = 0.5;
    chassis.turn_settle_time = 100;
    chassis.turn(-59.5);
    chassis.drive_settle_error = 1.2; //1.2
    chassis.drive_settle_time = 50;//50 
    chassis.drive_timeout = 1300;
    chassis.move(36, 8);
    chassis.drive_timeout = 700;
    chassis.move(12, 12);//4.5, 5, 7

    // ring next to ally stake
    chassis.move(-13.5, 12);
    chassis.turn(60, 6);
    intakePiston.set(true);
    chassis.move(30);
    chassis.move(15, 3);
    chassis.set_drive_constants(8.5, 1.2, 0, 8, 0);
    chassis.set_heading_constants(12, 0.5, 0, 6.5, 0);
    intakePiston.set(false);
    wait(80, msec);
    chassis.move(-10, 8);

    // end
    wait(200, msec);
    l.stop();
    r.stop();
    COLOR_SORT_FILTER_RED.interrupt();
}