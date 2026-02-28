#include "vex.h"

//-------------------------------------------------------------------------
// pneumatics
//-------------------------------------------------------------------------
bool active = false;

// void ctrlScraper() {
//     active = !active;
//     scraper.set(active);
// }

// void ctrlDescorer() {
//     active = !active;
//     descorer.set(active);
// }

//-------------------------------------------------------------------------
// chassis control
//-------------------------------------------------------------------------

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

//-------------------------------------------------------------------------
// intake
//-------------------------------------------------------------------------
void moveIntake(int inlv, int inuv) {
  inf.spin(fwd, inlv, volt);
  inb.spin(fwd, inuv, volt);
}

enum IntakeState { //intake constructor
    INTAKE_OFF,
    INTAKE_IN,
    SCORE_LOW,
    SCORE_MID,
    SCORE_LONG,
    SORT,
    INDEX,
    ANTI_JAM
};

IntakeState intakeState = INTAKE_OFF; //initial state
bool intakeLock = false;

void intake() { hood.set(false); trapdoor.set(false); moveIntake(-12, -12); }
void scoreLowGoal() { hood.set(false); trapdoor.set(false); moveIntake(12, 12); }
void scoreMidGoal() { hood.set(false); trapdoor.set(true); moveIntake(-12, 12); }
void scoreLongGoal() { hood.set(true); trapdoor.set(true); moveIntake(-12, -12); }
void antiJam() { moveIntake(0, -12); }

void mansort() { hood.set(false); trapdoor.set(false); moveIntake(-12, 12); }

void indexer() { hood.set(true); trapdoor.set(true); moveIntake(-12, 1); }

//-------------------------------------------------------------------------
// optical detection in intake control
//-------------------------------------------------------------------------
int ejectTime = 0; //time since opp block detected
int ejectInterval = 20; //added to each ejection cycle
int maxEjectLimit = 525; //default if this is exceeded

void detectBlock(char oppsColor) {

    optic.integrationTime(5);
    bool prevDetected = false;

    while (1) {

        bool detectedOpp = false; //always go back to no opps detected

        if (optic.isNearObject()) {

            if (oppsColor == 'r') {
                detectedOpp = (optic.hue() > RED_LOWER_LIM) && (optic.hue() < RED_UPPER_LIM); //constants.h
            } else if (oppsColor == 'b') {
                detectedOpp = (optic.hue() > BLUE_LOWER_LIM) && (optic.hue() < BLUE_UPPER_LIM);
            }

            //detect on edge
            if (detectedOpp and !prevDetected) {
                intakeLock = true;
            }
            prevDetected = detectedOpp;

        } else {
            prevDetected = false;
        }

        wait(10, msec);
    }
}

void detectOrig() {
    while (1) {
        if (optic.isNearObject()) {
            break;
        }
    }
    double hue = optic.hue();

    if (hue > RED_LOWER_LIM && hue < RED_UPPER_LIM) {
        opp = 'b';
    }
    else if (hue > BLUE_LOWER_LIM && hue < BLUE_UPPER_LIM) {
        opp = 'r';
    }
    else {
        opp = 'n';
    }
}

void autoSort() {
    // while (1) {
    //     if (optic.isNearObject()) {
    //         break;
    //     }
    // }
    // double hue = optic.hue();
    // std::string opps = "none";

    // if (hue > RED_LOWER_LIM && hue < RED_UPPER_LIM) {
    //     opps = "blue";
    // } else if (hue > BLUE_LOWER_LIM && hue < BLUE_UPPER_LIM) {
    //     opps = "red";
    // }

    // while (1) {
    //     detectBlock(opps);
    // }
}

void detectStop() {
    if (optic.isNearObject()) {
        if ((optic.hue() > RED_LOWER_LIM) && (optic.hue() < RED_UPPER_LIM)) {
            wait(100, msec);
            intakeLock = true;
        } else if ((optic.hue() > BLUE_LOWER_LIM) && (optic.hue() < BLUE_UPPER_LIM)) {
            intakeLock = false;
        }
    }
}

// void filterBlue() { detectBlock("blue"); }
// void filterRed() { detectBlock("red"); }

void ctrls() {
    bool R1 = cont.ButtonR1.pressing(); bool R2 = cont.ButtonR2.pressing(); bool L1 = cont.ButtonL1.pressing();
    bool A = cont.ButtonA.pressing(); bool X = cont.ButtonX.pressing();
    bool B = cont.ButtonB.pressing();

    // chassis
    arcade();
    //moveIntake(cont.Axis3.position(), cont.Axis2.position());

    // intake
    if (R1 and L1)             intakeState = SCORE_LOW;
    else if (R1 and !L1)       intakeState = INTAKE_IN;
    else if (R2 and L1)        intakeState = SCORE_MID;
    else if (R2 and !L1)       intakeState = SCORE_LONG;
    else if (X)                intakeState = ANTI_JAM;
    else if (A)                intakeState = INDEX;
    else if (B)                intakeState = SORT;
    else                       intakeState = INTAKE_OFF;

    // intake decision tree
    if (intakeLock) {
        ejectTime += ejectInterval; //add more time to ejection if opp block still detected
        
        if (auton != 8) { moveIntake(-12, 12); 
        } else { moveIntake(0, 0); }

        if (ejectTime >= maxEjectLimit) {
            intakeLock = false;
            ejectTime = 0;
        }

    } else {
        switch(intakeState) {
            case INTAKE_IN:
                intake(); break;
            case SCORE_LOW:
                scoreLowGoal(); break;
            case SCORE_MID:
                scoreMidGoal(); break;
            case SCORE_LONG:
                scoreLongGoal(); break;
            case ANTI_JAM:
                antiJam(); break;
            case SORT:
                mansort(); break;
            case INDEX:
                indexer(); break;
            default:
                moveIntake(0,0);
        }
    }
    wait(20, msec);
}   