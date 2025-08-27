#include <vex.h>

void red_sawp() {

    // start
    std::cout << "AUTON BEGIN" << endl;

    chassis.turn_kd = 3.8;
    chassis.turn_settle_error = 1;//1
    chassis.turn_settle_time = 200;//200

    intake.setMaxTorque(100, pct);
    thread COLOR_SORT_FILTER_BLUE = thread(filterBlue);

    // preload -> alliance stake
    thread t_liftGrab = thread(lift_grab);
    moveIntake(12);
    
    auto moveToAllyStake = []() { chassis.move(7.5); }; 
    thread t_moveToAllyStake = thread(moveToAllyStake);

    wait(500, msec);
    moveIntake(0);
    moveLift(LIFT_SCORE_POS, 100);
    wait(150, msec);

    // clamp goal 1
    chassis.move(-38, 7);
    thread liftResetThread = thread(lift_reset);
    mogo.set(true);
    wait(500, msec);
    
    // ring 1 -> goal 1
    chassis.turn_settle_error = 3;
    chassis.turn_settle_time = 50;
    chassis.turn(114);
    moveIntake(12);
    chassis.move(18);

    // ring 2 -> goal 1
    chassis.turn(140);
    chassis.move(-32);
    intakePiston.set(true);
    chassis.turn(-20);
    chassis.move(7, 3);
    intakePiston.set(false);
    wait(200, msec);
    chassis.move(-10, 8);

    // clamp goal 2
    mogo.set(false);
    moveIntake(0);
    chassis.move(20);
    chassis.turn(74);
    chassis.move(-28, 6);
    mogo.set(true);
    wait(200, msec);

    // ring 3 -> goal 2
    chassis.turn(-65);
    moveIntake(12);
    chassis.move(20);
    wait(500, msec);

    // ladder touch
    chassis.set_drive_constants(6, 1.2, 0, 8, 0);
    chassis.set_heading_constants(9, 0.5, 0, 6.5, 0);
    chassis.arc(-30, -37);

    // end
    wait(200, msec);
    l.stop();
    r.stop();
    COLOR_SORT_FILTER_BLUE.interrupt();
}

void blue_sawp() {
    // start
    std::cout << "AUTON BEGIN" << endl;

    chassis.turn_kd = 3.8;
    chassis.turn_settle_error = 1;//1
    chassis.turn_settle_time = 200;//200

    intake.setMaxTorque(100, pct);
    thread COLOR_SORT_FILTER_RED = thread(filterRed);

    // preload -> alliance stake
    thread t_liftGrab = thread(lift_grab);
    moveIntake(12);
    
    auto moveToAllyStake = []() { chassis.move(7.5); }; 
    thread t_moveToAllyStake = thread(moveToAllyStake);

    wait(500, msec);
    moveIntake(0);
    moveLift(LIFT_SCORE_POS, 100);
    wait(150, msec);

    // clamp goal 1
    chassis.move(-38, 7);
    thread liftResetThread = thread(lift_reset);
    mogo.set(true);
    wait(500, msec);
    
    // ring 1 -> goal 1
    chassis.turn_settle_error = 3;
    chassis.turn_settle_time = 50;
    chassis.turn(114);
    moveIntake(12);
    chassis.move(18);

    // ring 2 -> goal 1
    chassis.turn(140);
    chassis.move(-32);
    intakePiston.set(true);
    chassis.turn(-20);
    chassis.move(7, 3);
    intakePiston.set(false);
    wait(200, msec);
    chassis.move(-10, 8);

    // clamp goal 2
    mogo.set(false);
    moveIntake(0);
    chassis.move(20);
    chassis.turn(74);
    chassis.move(-28, 6);
    mogo.set(true);
    wait(200, msec);

    // ring 3 -> goal 2
    chassis.turn(-65);
    moveIntake(12);
    chassis.move(20);
    wait(500, msec);

    // ladder touch
    chassis.set_drive_constants(6, 1.2, 0, 8, 0);
    chassis.set_heading_constants(9, 0.5, 0, 6.5, 0);
    chassis.arc(-30, -37);

    // end
    wait(200, msec);
    l.stop();
    r.stop();
    COLOR_SORT_FILTER_RED.interrupt();
}