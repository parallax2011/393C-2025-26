#include <vex.h>

void usercontrol(void) {

    l.setStopping(coast);
    r.setStopping(coast);
    inf.setMaxTorque(100, percent);
    inb.setMaxTorque(100, percent);

    optic.setLight(ledState::on);
    optic.setLightPower(100);
    optic.objectDetectThreshold(50);

    thread tColorSortAlg1 = thread(filterRed);

    while (1) {
        ctrls();
    }
}