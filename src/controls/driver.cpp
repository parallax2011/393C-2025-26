#include <vex.h>

void filterBlue() { detectBlock("blue"); }
void filterRed() { detectBlock("red"); }

void usercontrol(void) {


    l.setStopping(coast);
    r.setStopping(coast);
    inf.setMaxTorque(100, percent);
    inb.setMaxTorque(100, percent);

    //descorer.set(true); //represents auton timed out
 
    // optic.setLight(ledState::on);
    // optic.setLightPower(100);
    // optic.objectDetectThreshold(100);

    thread t_csr = thread(detectStop);
    // auto csb = []() {
    //     detectBlock("blue");
    // }; thread t_csb = thread(csb);

    while (1) {
        ctrls();
        // if (cont.ButtonDown.pressing()) { t_csr.interrupt(); }
    }
}