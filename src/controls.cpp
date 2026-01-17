#include "vex.h"

bool state = false;

void ctrlScraper() {
    state = !state;
    scraper.set(state);
}

void ctrlDescorer() {
    state = !state;
    descorer.set(state);
}

void arcade() {
  int forward = controller1.Axis3.position();
  int rate = controller1.Axis1.position();
  int turn = (abs(rate) * rate) / 100;
  l.spin(fwd, to_volt(forward + turn), volt);
  r.spin(fwd, to_volt(forward - turn), volt); 
}

float expoCurve(float input, float t) { // expo-curves for joystick inputs; t = constant
  return input * pow(M_E, (t * (input - 100)) / 1000);
}

// customizable arcade control function with turn curving and deadbands
void arcade(int forward, int turn, bool enableTurnCurve, float deadbandWidth) {
    // applying deadbands to both joystick inputs
    forward = deadband(forward, deadbandWidth);
    turn = deadband(turn, deadbandWidth);

    if (enableTurnCurve) {       
        turn = expoCurve(turn, 15); // applying exponential curve to turn input
    } else {
        turn = (abs(turn) * turn) / 100; // applying quadratic curve to turn input
    }

    // calculating drive power and converting joystick units (%) to motor units (volts)
    l.spin(fwd, to_volt(forward + turn), volt); // left group
    r.spin(fwd, to_volt(forward - turn), volt); // right group
}

void moveIntake(int inlv, int inuv) {
  inf.spin(fwd, inlv, volt);
  inb.spin(fwd, inuv, volt);
}

void intake() { hood.set(false); trapdoor.set(false); moveIntake(-12, -12); }
void scoreLowGoal() { }
void scoreMidGoal() { hood.set(false); trapdoor.set(true); moveIntake(-12, 6); }
void scoreLongGoal() { hood.set(true); trapdoor.set(true); moveIntake(-12, -12); }
void antiJam() { moveIntake(0, -12); }