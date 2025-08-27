#include <vex.h>

void liftVertical() {
    moveLift(350, 100);
}


void skills() {

    chassis.set_drive_constants(12, 1.2, 0, 10, 0);
    chassis.set_drive_exit_conditions(.75, 100, 1300);

    chassis.set_turn_constants(12, 0.4, 0.03, 3, 15);
    chassis.set_turn_exit_conditions(.5, 100, 3000);

    // preload -> ally stake
    moveLift(LIFT_GRAB_POS, 100);
    moveIntake(12);
    wait(500, msec);
    moveIntake(0);
    moveLift(LIFT_SCORE_POS, 100);
    wait(500, msec);

    // mogo 1
    chassis.move(-7.1);//-8.75
    thread liftreset = thread(lift_reset); //thread lr = thread(liftNonReset);
    chassis.turn(-90);
    chassis.move(-18, 3);
    mogo.set(true);
    chassis.drive_settle_error = 0.5;
    wait(200, msec);
    moveIntake(12);

    // ring 2
    chassis.turn_max_voltage = 6; chassis.turn(163); //chassis.turn(163, 6);
    chassis.move(21, 12);
    wait(500, msec);

    // ring 3
    chassis.turn_max_voltage = 12; chassis.turn(147); //chassis.turn(147);
    chassis.move(34.75, 12);//34
    chassis.turn(90); //chassis.turn(90);
    thread xk = thread(lift_grab);
    chassis.drive_timeout = 1000;
    chassis.move(15.8, 12);
    chassis.drive_timeout = 2000;
    wait(1000, msec);
    moveIntake(0);
    moveLift(520, 100);

    // ring 4/5/6
    chassis.move(-10.3, 12);//=11
    thread lr2 = thread(liftVertical);
    chassis.turn(0); //chassis.turn(0);
    moveIntake(12);
    chassis.move(43, 4);
    chassis.move(15, 3);
    wait(700, msec);

    // ring 6
    chassis.turn(125); //chassis.turn(125);
    //thread liftreset2 = thread(liftVertical);
    chassis.move(13);

    // unclamp mogo 1 -> corner
    chassis.turn(-155); //chassis.turn(-160, 12);
    wait(500, msec);
    mogo.set(false);
    chassis.move(-8.5);//-10
    moveIntake(-12);

    // mogo 2
    chassis.move(5.5);//7.5
    chassis.turn(90); //chassis.turn(90);
    ///chassis.set_heading_constants(0, 0, 0, 0, 0);
    chassis.move(-60, 12);
    chassis.move(-16.5, 3);
    mogo.set(true);
    wait(200, msec);

    // ring 1
    moveIntake(12);
    chassis.turn(-170); //chassis.turn(-170);
    chassis.set_heading_constants(6, .4, 0, 1, 0);
    chassis.move(16, 12);
    
    // ring 2 -> wall stake
    chassis.turn(-147); //chassis.turn(-147);
    chassis.move(39, 12);//38.1//37.1
    chassis.turn(-90); //chassis.turn(-90);
    thread xk2 = thread(lift_grab);
    chassis.drive_timeout = 1000;
    lift.setTimeout(1500, msec);
    chassis.move(16.2, 12);
    chassis.drive_timeout = 2000;
    //lift.setTimeout(1500, msec);
    wait(1000, msec);
    moveIntake(0);
    moveLift(520, 100);

    // ring 3/4/5
    chassis.move(-11.5, 12);//-10.75
    thread lr3 = thread(liftVertical);
    chassis.turn(0); //chassis.turn(0);
    moveIntake(12);
    chassis.move(43, 4);
    chassis.move(15, 3);
    wait(700, msec);

    // ring 6
    chassis.turn(-130); //chassis.turn(-130, 12);
    //thread liftreset3 = thread(lift_reset);
    chassis.move(15);

    // unclamp mogo 2 -> corner
    chassis.turn(160); //chassis.turn(160, 12);
    chassis.move(-10);
    moveIntake(-12);
    mogo.set(false);

    // ally stake ring
    chassis.move(43, 12);
    moveIntake(12);
    thread xk3 = thread(lift_grab);
    chassis.turn(180);
    chassis.move(43, 12);
    wait(500, msec);
    
    // mogo 3 clamp
    chassis.turn(-65);
    chassis.move(-35, 12);
    chassis.move(-15, 3.5);
    mogo.set(true);

    // ring -> ally stake
    chassis.move(-3.5);
    chassis.turn(180);
    chassis.move(2.5);
    moveIntake(0);
    lift_score();
    wait(500, msec);

    // ring 1 -> mogo 3
    chassis.move(-5.7);
    chassis.turn(-90);
    thread liftreset4 = thread(lift_reset);
    thread intakeStart = thread(intakeMaxFWD);
    chassis.move(44);
    wait(1000, msec);
    
    // unclamp mogo 3
    chassis.turn(50);
    wait(500, msec);
    moveIntake(-12);
    mogo.set(false);
    chassis.drive_timeout = 600;
    chassis.move(-19.5);

    // push mogo 4 -> corner
    chassis.drive_timeout = 1000;
    chassis.move(25);
    chassis.turn(-70);
    chassis.drive_timeout = 5000;
    chassis.move(-100);
}