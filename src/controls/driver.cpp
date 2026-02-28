#include <vex.h>

void filterBlue() { detectBlock('b'); }
void filterRed() { detectBlock('r'); }

void usercontrol(void) {


    l.setStopping(coast);
    r.setStopping(coast);
    inf.setMaxTorque(100, percent);
    inb.setMaxTorque(100, percent);

    //descorer.set(true); //represents auton timed out
 
    // optic.setLight(ledState::on);
    // optic.setLightPower(100);
    // optic.objectDetectThreshold(100);

    auto cs = []() { detectBlock('r'); }; 
    thread tcs = thread(cs);

    //thread t_csr = thread(detectStop);
    // thread cst = thread(autoSort);

    while (1) {
        ctrls();
        // if (cont.ButtonDown.pressing()) { t_csr.interrupt(); }
    }
}