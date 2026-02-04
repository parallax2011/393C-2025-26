#include <vex.h>

void menu() {
    Brain.Screen.clearScreen();
    Brain.Screen.setFont(prop30);
    Brain.Screen.setPenColor(color(180, 180, 180));
    Brain.Screen.printAt(5, 30, "Battery: %d%%", Brain.Battery.capacity());
    Brain.Screen.setFont(prop20);
    // Brain.Screen.drawLine(300, 0, 300, 40);
    Brain.Screen.setPenColor(color(0, 150, 0));
    Brain.Screen.drawRectangle(305, 0, 170, 40, color(0, 150, 0));
    Brain.Screen.setPenColor(black);
    Brain.Screen.printAt(365, 25, false, "SKILLS");
    Brain.Screen.setPenColor(color(180, 180, 180));
    Brain.Screen.setFont(prop30);
    Brain.Screen.drawLine(0, 40, 480, 40);
    Brain.Screen.setPenColor(color(180, 0, 0));
    Brain.Screen.drawRectangle(10, 50, 220, 85, color(180, 0, 0));
    Brain.Screen.setPenColor(black);
    Brain.Screen.printAt(60, 100, false, "LEFT 6+3");
    Brain.Screen.setPenColor(color(0, 0, 180));
    Brain.Screen.drawRectangle(250, 50, 220, 85, color(0, 0, 180));
    Brain.Screen.setPenColor(black);
    Brain.Screen.printAt(290, 100, false, "RIGHT 6+3");
    Brain.Screen.setPenColor(color(0, 150, 0));
    Brain.Screen.drawRectangle(10, 145, 220, 85, color(180, 0, 0));
    Brain.Screen.setPenColor(black);
    Brain.Screen.printAt(50, 195, false, "SOLO AWP");
    Brain.Screen.setPenColor(color(0, 0, 180));
    Brain.Screen.drawRectangle(250, 145, 220, 85, color(0, 0, 180));
    Brain.Screen.setPenColor(black);
    Brain.Screen.printAt(320, 195, false, "LEFT 9");
    Brain.Screen.setPenColor(color(180, 180, 180));
}

//     cont.Screen.clearScreen(); cont.Screen.setCursor(1, 1); cont.Screen.print("IMU Calibrated");

//     int xLastTouch = Brain.Screen.xPosition();
//     int yLastTouch = Brain.Screen.yPosition();
//     menu();
//     while (Brain.Screen.xPosition() == xLastTouch && Brain.Screen.yPosition() == yLastTouch) {
//         vex::task::sleep(20);
//     }
//     bool k = true;

//     while (k) {
//         if ((Brain.Screen.xPosition() >= 10 && Brain.Screen.xPosition() <= 230) && (Brain.Screen.yPosition() >= 50 && Brain.Screen.yPosition() <= 135)) {
//             auton = 0;
//             k = false;
//         } else if ((Brain.Screen.xPosition() >= 250 && Brain.Screen.xPosition() <= 470) && (Brain.Screen.yPosition() >= 50 && Brain.Screen.yPosition() <= 135)) {
//             auton = 1;
//             k = false;
//         } else if ((Brain.Screen.xPosition() >= 10 && Brain.Screen.xPosition() <= 230) && (Brain.Screen.yPosition() >= 145 && Brain.Screen.yPosition() <= 230)) {
//             auton = 2;
//             k = false;
//         } else if ((Brain.Screen.xPosition() >= 250 && Brain.Screen.xPosition() <= 470) && (Brain.Screen.yPosition() >= 145 && Brain.Screen.yPosition() <= 230)) {
//             auton = 3;
//             k = false;
//         } else if ((Brain.Screen.xPosition() >= 305 && Brain.Screen.xPosition() <= 475) && (Brain.Screen.yPosition() >= 0 && Brain.Screen.yPosition() <= 40)) {
//             auton = 4;
//             k = false;
//         }
//   }

//   Brain.Screen.clearScreen(); Brain.Screen.setFont(mono60);
//   cont.Screen.clearScreen(); cont.Screen.setCursor(1, 1);

//   if (auton == 0) { Brain.Screen.printAt(100, 140, "LEFT 6+3"); cont.Screen.print("LEFT 6+3"); }
//   else if (auton == 1) { Brain.Screen.printAt(100, 140, "RIGHT 6+3"); cont.Screen.print("RIGHT 6+3"); }
//   else if (auton == 2) { Brain.Screen.printAt(100, 140, "SOLO AWP"); cont.Screen.print("SOLO AWP"); }
//   else if (auton == 3) { Brain.Screen.printAt(100, 140, "LEFT 9"); cont.Screen.print("LEFT 9"); }
//   else if (auton == 4) { Brain.Screen.printAt(100, 140, "SKILLS"); cont.Screen.print("SKILLS"); } else { }


void preAuton() {
    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();

    cont.Screen.clearScreen();
    cont.Screen.setCursor(1, 1);
    cont.Screen.print("Calibrating");
    // Gyro.calibrate(2000);
    imu.calibrate(3000);
    wait(3000, msec);

    //defaultConstants();
    //thread TLM = thread(telemetry);

    optic.setLight(ledState::on);
    optic.setLightPower(100);
    optic.objectDetectThreshold(10);
    
}

void batteryCheck() {
    while(1) {
        Brain.Screen.setPenColor(vex::black);
        Brain.Screen.setFont(vex::fontType::mono60);

        if(Brain.Battery.capacity() > 60) {
            Brain.Screen.clearScreen(vex::green);
            Brain.Screen.setFillColor(vex::green);

        } else if (Brain.Battery.capacity() > 30) {
            Brain.Screen.clearScreen(vex::yellow);
            Brain.Screen.setFillColor(vex::yellow);

        } else {
            Brain.Screen.setFillColor(vex::red);
            Brain.Screen.clearScreen(vex::red);
        }
        Brain.Screen.printAt(60, 80, "%d %", Brain.Battery.capacity());
        this_thread::sleep_for(100);
  }
}
