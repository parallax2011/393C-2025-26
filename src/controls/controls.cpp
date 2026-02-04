#include "vex.h"

bool active = false;

void ctrlScraper() {
    active = !active;
    scraper.set(active);
}

void ctrlDescorer() {
    active = !active;
    descorer.set(active);
}

void arcadeCont() {
  int forward = cont.Axis3.position();
  int rate = cont.Axis1.position();
  int turn = (abs(rate) * rate) / 100;
  l.spin(fwd, to_volt(forward + turn), volt);
  r.spin(fwd, to_volt(forward - turn), volt); 
}

float expoCurve(float input, float t) { // expo-curves for joystick inputs; t = constant
  return input * pow(2.718, (t * (input - 100)) / 1000);
}

void arcade() {
    int forwardp = cont.Axis3.position();
    int rate = cont.Axis1.position();
    // int turn = (abs(rate) * rate) / 100;
    int turnp = int(pow(rate, 3) / pow(100, 2));
    // int turn = (abs(rate) * pow(rate, 3)) / pow(100, 3);
    l.spin(fwd, to_volt(forwardp + turnp), volt);
    r.spin(fwd, to_volt(forwardp - turnp), volt); 
}

void moveIntake(int inlv, int inuv) {
  inf.spin(fwd, inlv, volt);
  inb.spin(fwd, inuv, volt);
}

void intakeStick() {
    float intakef = cont.Axis3.position();
    float intakeb = cont.Axis2.position();
    moveIntake(intakef, intakeb);
}

void intake() { hood.set(false); trapdoor.set(false); moveIntake(-12, -12); }
void scoreLowGoal() { hood.set(false); trapdoor.set(false); moveIntake(12, 12); }
void scoreMidGoal() { hood.set(false); trapdoor.set(true); moveIntake(-12, 12); }
void scoreLongGoal() { hood.set(true); trapdoor.set(true); moveIntake(-12, -12); }
void antiJam() { moveIntake(0, -12); }

void ctrls() {
    bool R1 = cont.ButtonR1.pressing(); bool R2 = cont.ButtonR2.pressing(); bool L1 = cont.ButtonL1.pressing();
    bool B = cont.ButtonB.pressing(); bool X = cont.ButtonX.pressing();

    arcade(); // chassis
    // intakeStick();

    // intake
    if (R1 and L1)             { scoreLowGoal(); }
    else if (R1 and !L1)       { intake(); }
    else if (R2 and L1)        { scoreMidGoal(); }
    else if (R2 and !L1)       { scoreLongGoal(); }
    else if (B)                { hood.set(true); trapdoor.set(false); moveIntake(-12, -12); } // manual sorting
    else if (X)                { trapdoor.set(true); moveIntake(12, 12); } // antijam
    else                       { moveIntake(0, 0); }

    wait(20, msec);
}