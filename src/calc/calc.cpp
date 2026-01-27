#include "vex.h"

float reduce_0_360(float angle) {
  while(!(angle >= 0 && angle < 360)) {
    if( angle < 0 ) { angle += 360; }
    if(angle >= 360) { angle -= 360; }
  }
  return(angle);
}

float reduce_neg180_180(float angle) {
  while (!(angle >= -180 && angle < 180)) {
    if (angle < -180) { angle += 360; }
    if (angle >= 180) { angle -= 360; }
  }
  return(angle);
}

float reduce_negative_90_to_90(float angle) {
  while (!(angle >= -90 && angle < 90)) {
    if (angle < -90 ) { angle += 180; }
    if (angle >= 90) { angle -= 180; }
  }
  return(angle);
}

float toRad(float angle_deg) {
  return (angle_deg/(180.0/M_PI));
}

float toDeg(float angle_rad) {
  return (angle_rad*(180.0/M_PI));
}

float restrict(float input, float min, float max) {
  if (input > max ) { return(max); }
  if (input < min) { return(min); }
  return (input);
}

bool isReversed(double input){
  if (input < 0) return(true);
  return(false);
}

float toVolt(float percent){
  return (percent*12.0/100.0);
}

int toPort(int port){
  if(port > 8 || port < 1){
    return(0);
  }
  return(port-1); // -converts an input port to a triport
                  // -does error checking to prevent invalid values from being
                  // passed to the triport array
}

float deadband(float input, float width) { // deadzone function for controller
  if (std::fabs(input) < width) {
    return (0);
  }
  return (input);
}

/**
 * Settling control for odometry functions.
 * Draws a line perpendicular to the line from the robot to the desired 
 * endpoint, and checks if the robot has crossed that line. Allows for
 * very quick settling, and thereby chaining for fast motion control.
 */

bool isLineSettled(float desired_X, float desired_Y, float desired_angle_deg, float current_X, float current_Y){
  return( (desired_Y-current_Y) * cos(toRad(desired_angle_deg)) <= -(desired_X-current_X) * sin(toRad(desired_angle_deg)) );
}

/**
 * Voltage scaling to keep from applying more than 12 volts to either side of the drive.
 * Divides both drive and heading output proportionally to get a similar result to the
 * desired one.
 */

float leftVoltageScaling(float drive_output, float heading_output){
  float ratio = std::max(std::fabs(drive_output+heading_output), std::fabs(drive_output-heading_output))/12.0;
  if (ratio > 1) {
    return (drive_output+heading_output)/ratio;
  }
  return drive_output+heading_output;
}

/**
 * Voltage scaling to keep from applying more than 12 volts to either side of the drive.
 * Divides both drive and heading output proportionally to get a similar result to the
 * desired one.
*/

float rightVoltageScaling(float drive_output, float heading_output){
  float ratio = std::max(std::fabs(drive_output+heading_output), std::fabs(drive_output-heading_output))/12.0;
  if (ratio > 1) {
    return (drive_output-heading_output)/ratio;
  }
  return drive_output-heading_output;
}

/**
 * Brings an output up to the minimum voltage if it's too slow.
 * Used for minimum voltage calculations for movement chaining.
 * Has no effect on 0 voltage output, because how do we know 
 * which way it's supposed to be going?
 */

float restrictMinVoltage(float drive_output, float lin_min){
  if(drive_output < 0 && drive_output > -lin_min){
      return -lin_min;
  }
  if(drive_output > 0 && drive_output < lin_min){
    return lin_min;
  }
  return drive_output;
}