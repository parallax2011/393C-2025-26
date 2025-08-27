#include "vex.h"

void filterRing(float intakeTime) {
  wait(intakeTime, msec);//160

  moveIntake(-12);
  wait(250, msec);
  moveIntake(12);
}

void getRing(std::string targetColor, float intakeTime) {
  optic.integrationTime(5);
  while (1) {
    optic.setLight(ledState::on);
    optic.setLightPower(100);
  
    
    if (optic.isNearObject()) {
      // if we are on blue team
      if (targetColor == "red") {
        if ((optic.hue() > RED_LOWER_LIM) && (optic.hue() < RED_UPPER_LIM)) {
          filterRing(intakeTime);
        }
      }
      // if we are on red team
      else if (targetColor == "blue") {
        if ((optic.hue() > BLUE_LOWER_LIM) && (optic.hue() < BLUE_UPPER_LIM)) {
          filterRing(intakeTime);
        }
      }
    }
  }
}

void detectStopRing() {
  while (!optic.isNearObject()) {
    moveIntake(12);
    wait(5, msec);
  }
  moveIntake(0);
}

void detectRing() {
  int run_time = 0;
  while (!optic.isNearObject()) {
    if (run_time >= 3000) { // timeout
      break;
    }
    moveIntake(12);
    wait(1, msec);
    run_time += 1;
  }
}

void detectRedRing() {
  int run_time = 0;
  while (!((optic.hue() > RED_LOWER_LIM) && (optic.hue() < RED_UPPER_LIM))) {
    // if (run_time >= 3000) { // timeout
    //   break;
    // }
    moveIntake(12);
    //wait(1, msec);
    //run_time += 1;
  }


  // URBAD
}

void filterRed() { getRing("red", 130); }
void filterBlue() { getRing("blue", 130); }
void filterBlueSlow() { getRing("blue", 370); }