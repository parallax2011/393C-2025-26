#include <vex.h>

void usercontrol(void) {

    l.setStopping(coast);
    r.setStopping(coast);
    inf.setMaxTorque(100, percent);
    inb.setMaxTorque(100, percent);

    descorer.set(true); //represents auton timed out

    optic.setLight(ledState::on);
    optic.setLightPower(100);
    optic.objectDetectThreshold(100);

    auto csr = []() { 
        detectBlock("blue");
    }; thread t_csr = thread(csr);
    // auto csb = []() { 
    //     detectBlock("blue");
    // }; thread t_csb = thread(csb);

    while (1) {
        ctrls();
    }
}