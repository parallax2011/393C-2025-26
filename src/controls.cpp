#include "vex.h"

bool state = false;

void controlMogo() {
  state = !state;
  mogo.set(state);
}

void controlDoink() {
  state = !state;
  doink.set(state);
}

void controlIntakePiston() {
  state = !state;
  intakePiston.set(state);
}

void arcade() {
  int forward = controller1.Axis3.position();
  int rate = controller1.Axis1.position();
  int turn = (abs(rate) * rate) / 100;
  l.spin(fwd, to_volt(forward + turn), volt);
  r.spin(fwd, to_volt(forward - turn), volt); 
}

void detectJam() {
    while (1) {
        if (abs(intake.velocity(pct)) <= 5) {
            moveIntake(-12);
            wait(300, msec);
            moveIntake(12);
        }
    }
}