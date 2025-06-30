#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen.
brain  Brain;

motor leftTop = motor(PORT3, false);
motor leftMiddle = motor(PORT2, true);
motor leftBottom = motor(PORT1, true);
motor rightTop = motor(PORT6, false);
motor rightMiddle = motor(PORT5, true);
motor rightBottom = motor(PORT4, false);

motor topIntake = motor(PORT10, false);
motor bottomIntake = motor(PORT11, false);

controller Controller1 = controller();

//The motor constructor takes motors as (port, ratio, reversed), so for example
//motor LeftFront = motor(PORT1, ratio6_1, false);

//Add your devices below, and don't forget to do the same in robot-config.h:


void vexcodeInit( void ) {
  // nothing to initialize
}