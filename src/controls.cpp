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

void lowGoal() { moveIntake(-12, 0, 12); }
void basket() { moveIntake(12, 12, -12); }
void highGoal() { moveIntake(12, -12, 12); }
void longGoal() { moveIntake(12, 12, 12); }

// class Intake {
// public:

//     void move(float inlv, float inuv, float inbv) {
//         inl.spin(fwd, inlv, volt);
//         inu.spin(fwd, inuv, volt);
//         inb.spin(fwd, inbv, volt);
//     }

//     class Lower {
//     private:
//         motor& inl;
//     public:
//         Lower(motor& motorRef) : inl(motorRef) {}
//         void move(int volts) {
//             inl.spin(fwd, volts, volt);
//         }
//     };

//     class Upper {
//     private:
//         motor& inu;
//     public:
//         Upper(motor& motorRef) : inu(motorRef) {}
//         void move(int volts) {
//             inu.spin(fwd, volts, volt);
//         }
//     };

//     class Back {
//     private:
//         motor& inb;
//     public:
//         Back(motor& motorRef) : inb(motorRef) {}
//         void move(int volts) {
//             inb.spin(fwd, volts, volt);
//         }
//     };

//     Lower l;
//     Upper u;
//     Back b;

//     Intake(motor& inl, motor& inu, motor& inb)
//         : l(inl), u(inu), b(inb) {}
// };