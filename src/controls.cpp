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
  return input * pow(2.718, (t * (input - 100)) / 1000);
}

void arcadeControl() {
    int forward = controller1.Axis3.position();
    int rate = controller1.Axis1.position();
    //int turn = (abs(rate) * rate) / 100;
    int turn = int(pow(rate, 3) / pow(127, 2));
    l.spin(fwd, to_volt(forward + turn), volt);
    r.spin(fwd, to_volt(forward - turn), volt); 
}

void moveIntake(int inlv, int inuv) {
  inf.spin(fwd, inlv, volt);
  inb.spin(fwd, inuv, volt);
}

void intake() { hood.set(false); trapdoor.set(false); moveIntake(-12, -12); }
void scoreLowGoal() { hood.set(false); trapdoor.set(false); moveIntake(12, 12); }
void scoreMidGoal() { hood.set(false); trapdoor.set(true); moveIntake(-12, 6); }
void scoreLongGoal() { hood.set(true); trapdoor.set(true); moveIntake(-12, -12); }
void antiJam() { moveIntake(0, -12); }