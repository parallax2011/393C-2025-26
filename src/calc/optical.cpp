#include "vex.h"

void filter_block() {}

void getBlock(std::string targetColor) {
    // initialization
    optic.integrationTime(5);
    while (1) {
        optic.setLight(ledState::on);
        optic.setLightPower(100);
    
        if (optic.isNearObject()) {
            if (optic.isNearObject()) {
                // if we are on blue team
                if (targetColor == "red") {
                    if ((optic.hue() > RED_LOWER_LIM) && (optic.hue() < RED_UPPER_LIM)) {
                        if ((optic.hue() > RED_LOWER_LIM) && (optic.hue() < RED_UPPER_LIM)) {
                            filter_block();
                        }
                    }
                }

                // if we are on red team
                else if (targetColor == "blue") {
                    if ((optic.hue() > BLUE_LOWER_LIM) && (optic.hue() < BLUE_UPPER_LIM)) {
                        if ((optic.hue() > BLUE_LOWER_LIM) && (optic.hue() < BLUE_UPPER_LIM)) {
                            filter_block();
                        }
                    }
                }
            }
        } else {

        }
    }
}

void filterBlue() { getBlock("blue"); }
void filterRed() { getBlock("red"); }