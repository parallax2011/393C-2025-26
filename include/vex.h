/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       Vex Robotics                                              */
/*    Created:      1 Feb 2019                                                */
/*    Description:  Default header for V5 projects                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//

#pragma once
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

// extra imports
#include <string>
#include <algorithm>
#include <array>
#include <iostream>
#include <sstream>
#include <vector>
#include <typeinfo>
#include <iomanip>

#include "v5.h"
#include "v5_vcs.h"

#include "config.h"
#include "calc/FPS.h"
#include "ROBOT.h"
#include "calc/calc.h"
#include "calc/PID.h"
#include "auton.h"
#include "controls.h"
#include "calc/optical.h"
#include "constants.h"
#include "gui.h"

class Drive;
extern Drive chassis;

//using namespace vex;
using namespace std;

void filter_block();
void filter_red();
void filter_blue();

#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)