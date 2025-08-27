#pragma once
#include "vex.h"
#include "lib/drive.h"

class Drive;
extern Drive chassis;

void default_constants() {
    chassis.set_drive_constants(12, 1.2, 0, 8, 0);
    chassis.set_heading_constants(6, .4, 0, 1, 0);
    chassis.set_turn_constants(12, 0.4, 0.03, 3.2, 15);
    chassis.set_swing_constants(12, 1, 0.01, 6, 0);

    chassis.set_drive_exit_conditions(0.5, 100, 2000);
    chassis.set_turn_exit_conditions(0.5, 100, 1000);
    chassis.set_swing_exit_conditions(1, 200, 3000);
}