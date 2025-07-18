#include "vex.h"

/**
 * Resets the constants for auton movement.
 * Modify these to change the default behavior of functions like
 * drive_distance(). For explanations of the difference between
 * drive, heading, turning, and swinging, as well as the PID and
 * exit conditions, check the docs.
 */
void default_constants(){
  // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
  chassis.set_drive_constants(12, 2.9, 0, 12.5, 0);
  chassis.set_heading_constants(6, .5, 0.1, 8, 0);
  chassis.set_turn_constants(12, .2, 0, 1.5, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);

  // Each exit condition set is in the form of (settle_error, settle_time, timeout).
  chassis.set_drive_exit_conditions(1, 500 , 5000);
  chassis.set_turn_exit_conditions(.75, 300, 3000);
  chassis.set_swing_exit_conditions(1, 300, 3000);
}

/**
 * Sets constants to be more effective for odom movements.
 * For functions like drive_to_point(), it's often better to have
 * a slower max_voltage and greater settle_error than you would otherwise.
 */
void odom_constants(){
  default_constants();
  chassis.heading_max_voltage = 10;
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 0.5;
  chassis.boomerang_lead = 0;
  chassis.drive_min_voltage = 0;
}

/**
 * The expected behavior is to return to the start position.
 */
void drive_test(){
  chassis.drive_distance(4);
  chassis.drive_distance(10);
  chassis.drive_distance(16);
  chassis.drive_distance(-30);
  chassis.drive_stop(brake);
}

/**
 * The expected behavior is to return to the start angle, after making a complete turn.
 */
void turn_test(){
  chassis.turn_to_angle(5);
  chassis.turn_to_angle(30);
  chassis.turn_to_angle(90);
  chassis.turn_to_angle(225);
  chassis.turn_to_angle(0);
}

/**
 * Should swing in a fun S shape.
 */
void swing_test(){
  chassis.left_swing_to_angle(90);
  chassis.right_swing_to_angle(0);
}

/**
 * A little of this, a little of that; it should end roughly where it started.
 */
void full_test(){
  chassis.drive_distance(24);
  chassis.turn_to_angle(-45);
  chassis.drive_distance(-36);
  chassis.right_swing_to_angle(-90);
  chassis.drive_distance(24);
  chassis.turn_to_angle(0);
}

/**
 * Doesn't drive the robot, but just prints coordinates to the Brain screen 
 * so you can check if they are accurate to life. Push the robot around and
 * see if the coordinates increase like you'd expect.
 */
void odom_test(){
  chassis.set_coordinates(0, 0, 0);
  while(1){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(5,20, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(5,40, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(5,60, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(5,80, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(5,100, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    task::sleep(20);
  }
}

/**
 * Test auton to set up the constants
 */
void tank_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0,0);
  chassis.drive_to_point(0,60);
  chassis.drive_stop(brake);
  Brain.Screen.clearScreen();
  Brain.Screen.printAt(5,20, "X: %f", chassis.get_X_position());
  Brain.Screen.printAt(5,40, "Y: %f", chassis.get_Y_position());
  Brain.Screen.printAt(5,60, "Heading: %f", chassis.get_absolute_heading());
  Brain.Screen.printAt(5,80, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
  Brain.Screen.printAt(5,100, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
  chassis.drive_stop(brake);
  wait(.5, seconds);

  chassis.drive_to_point(0,0);
  Brain.Screen.clearScreen();
  Brain.Screen.printAt(5,20, "X: %f", chassis.get_X_position());
  Brain.Screen.printAt(5,40, "Y: %f", chassis.get_Y_position());
  Brain.Screen.printAt(5,60, "Heading: %f", chassis.get_absolute_heading());
  Brain.Screen.printAt(5,80, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
  Brain.Screen.printAt(5,100, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
  chassis.drive_stop(brake);

  chassis.turn_to_angle(0);
  odom_test();
}


void turn_test1(){
  chassis.set_heading(0);
  chassis.turn_to_angle(90);
  chassis.turn_to_angle(180);
  chassis.turn_to_angle(270);
  chassis.turn_to_angle(360);
  task::sleep(500);
  chassis.turn_to_angle(180);
  chassis.turn_to_angle(0);
  chassis.turn_to_angle(270);
}


/**
 * Drives in a square while making a full turn in the process. Should
 * end where it started.
 */
void holonomic_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.holonomic_drive_to_pose(0, 18, 90);
  chassis.holonomic_drive_to_pose(18, 0, 180);
  chassis.holonomic_drive_to_pose(0, 18, 270);
  chassis.holonomic_drive_to_pose(0, 0, 0);
}

/**
 grab 3 middle balls
 score in low middle goal
 grab 3 from chute
 score long goal
 grab other middle 3
 (maybe) grab 3 from chute
 score on long goal
 push teamate
 */
void solo_winpoint(){
  
}

/**
  rush middle 2 balls
  score in middle shaft
  grab 3 from the match load chute
  grab pile of 3 and score in middle
  empty chute of opponent cubes
*/
void low_goal_rush(){

}

/**
  rush middle 2 balls
  score in middle shaft
  grab 3 from the match load chute
  grab pile of 3 and score in middle
  empty chute of opponent cubes
 */
void high_goal_rush(){

}

/**
  clear red park zone
  6 from red, low chute
  score on long goal
  all 6 middle red
  6 from red, high chute
  score all in long goal
  6 from blue, low chute
  clear blue park zone
  6 from blue, high chute
  score all but 1 in long goal
  grab 6 from middle
  score 7 in middle high goal
  park
 **/
void auton_skills(){

}