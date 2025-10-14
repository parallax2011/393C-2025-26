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

void ctrlPark() {
    state = !state;
    parker.set(state);
}

void arcade() {
  int forward = controller1.Axis3.position();
  int rate = controller1.Axis1.position();
  int turn = (abs(rate) * rate) / 100;
  l.spin(fwd, to_volt(forward + turn), volt);
  r.spin(fwd, to_volt(forward - turn), volt); 
}

void moveIntake(int inlv, int inuv, int inbv) {
  inl.spin(fwd, inlv, volt);
  inu.spin(fwd, inuv, volt);
  inb.spin(fwd, inbv, volt);
}

void lowGoal() { pto.set(false); moveIntake(-9, 0, 9); }
void basket() { pto.set(false); moveIntake(12, 12, -12); }
void highGoal() { pto.set(true); moveIntake(12, -12, 12); }
void manualSort() { moveIntake(12, -12, 0); }
void longGoal() { pto.set(false); moveIntake(12, 12, 12); }

void ctrlSort() {
    manualSort();
}