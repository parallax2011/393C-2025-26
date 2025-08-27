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

#include "robot-config.h"
#include "lib/odom.h"
#include "lib/drive.h"
#include "lib/util.h"
#include "lib/PID.h"
#include "autons.h"
#include "controls.h"
#include "optical.h"
#include "constants.h"

class Drive;
extern Drive chassis;

//using namespace vex;
using namespace std;

#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)