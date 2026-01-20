#pragma once
#include "vex.h"

enum drive_setup {ZERO_TRACKER_NO_ODOM, ZERO_TRACKER_ODOM, TANK_ONE_FORWARD_ENCODER, TANK_ONE_FORWARD_ROTATION, 
TANK_ONE_SIDEWAYS_ENCODER, TANK_ONE_SIDEWAYS_ROTATION, TANK_TWO_ENCODER, TANK_TWO_ROTATION, 
HOLONOMIC_TWO_ENCODER, HOLONOMIC_TWO_ROTATION};

/**
 * Drive class supporting tank and holo drive, with or without odom.
 * Eight flavors of odom and six custom motion algorithms.
 */

class Drive
{
private:
  float wheel_diameter;
  float wheel_ratio;
  float gyro_scale;
  float drive_in_to_deg_ratio;
  float ForwardTracker_center_distance;
  float ForwardTracker_diameter;
  float ForwardTracker_in_to_deg_ratio;
  float SidewaysTracker_center_distance;
  float SidewaysTracker_diameter;
  float SidewaysTracker_in_to_deg_ratio;
  vex:: triport ThreeWire = vex::triport(vex::PORT22);

public: 
  drive_setup drive_setup = ZERO_TRACKER_NO_ODOM;
  motor_group DriveL;
  motor_group DriveR;
  inertial Gyro;
  motor DriveLF;
  motor DriveRF;
  motor DriveLB;
  motor DriveRB;
  rotation R_ForwardTracker;
  rotation R_SidewaysTracker;
  encoder E_ForwardTracker;
  encoder E_SidewaysTracker;

  float ang_max;
  float ang_kp;
  float ang_ki;
  float ang_kd;
  float ang_starti;

  float ang_settle_error;
  float ang_settle_time;
  float ang_timeout;

  float lin_min;
  float lin_max;
  float lin_kp;
  float lin_ki;
  float lin_kd;
  float lin_starti;

  float lin_settle_error;
  float lin_settle_time;
  float lin_timeout;

  float theta_max;
  float theta_kp;
  float theta_ki;
  float theta_kd;
  float theta_starti;

  float swing_max;
  float swing_kp;
  float swing_ki;
  float swing_kd;
  float swing_starti;

  float swing_settle_error;
  float swing_settle_time;
  float swing_timeout;

  // float lift_max_voltage;
  // float lift_kp;
  // float lift_ki;
  // float lift_kd;
  // float lift_starti;

  // float lift_settle_error;
  // float lift_settle_time;
  // float lift_timeout;

  float boomerang_lead;
  float boomerang_setback;

  Drive(enum::drive_setup drive_setup, motor_group DriveL, motor_group DriveR, int gyro_port, float wheel_diameter, float wheel_ratio, float gyro_scale, int DriveLF_port, int DriveRF_port, int DriveLB_port, int DriveRB_port, int ForwardTracker_port, float ForwardTracker_diameter, float ForwardTracker_center_distance, int SidewaysTracker_port, float SidewaysTracker_diameter, float SidewaysTracker_center_distance);

  void drive_with_voltage(float left_voltage, float right_voltage);

  float get_absolute_heading();

  float get_left_position_in();

  float get_right_position_in();

  void setAngPID(float ang_max, float ang_kp, float ang_ki, float ang_kd, float ang_starti); 
  void setLinPID(float lin_max, float lin_kp, float lin_ki, float lin_kd, float lin_starti);
  void setThetaPID(float theta_max, float theta_kp, float theta_ki, float theta_kd, float theta_starti);
  void setSwingPID(float swing_max, float swing_kp, float swing_ki, float swing_kd, float swing_starti);
  //void set_lift_constants(float lift_max_voltage, float lift_kp, float lift_ki, float lift_kd, float lift_starti);

  void setAngExits(float ang_settle_error, float ang_settle_time, float ang_timeout);
  void setLinExits(float lin_settle_error, float lin_settle_time, float lin_timeout);
  void setSwingExits(float swing_settle_error, float swing_settle_time, float swing_timeout);
  //void set_lift_exit_conditions(float lift_settle_error, float lift_settle_time, float lift_timeout);

  void turn(float angle);
  //void turn(float angle, float ang_max);
  void kTurn(float angle, float ang_max, float ang_kp, float ang_ki, float ang_kd, float ang_starti);
  void turn(float angle, float type);
  void turn_to_angle(float angle, float ang_max, float ang_settle_error, float ang_settle_time, float ang_timeout);
  void turn_to_angle(float angle, float ang_max, float ang_settle_error, float ang_settle_time, float ang_timeout, float ang_kp, float ang_ki, float ang_kd, float ang_starti);

  void move(float distance);
  void arc(float distance, float heading);
  void move(float distance, float max_voltage);
  void move(float distance, float max_voltage, float timeout);
  void drive_distance(float distance, float heading, float lin_max, float theta_max);
  void drive_distance(float distance, float heading, float lin_max, float theta_max, float lin_settle_error, float lin_settle_time, float lin_timeout);
  void drive_distance(float distance, float heading, float lin_max, float theta_max, float lin_settle_error, float lin_settle_time, float lin_timeout, float lin_kp, float lin_ki, float lin_kd, float lin_starti, float theta_kp, float theta_ki, float theta_kd, float theta_starti);

  void left_swing_to_angle(float angle);
  void left_swing_to_angle(float angle, float swing_max, float swing_settle_error, float swing_settle_time, float swing_timeout, float swing_kp, float swing_ki, float swing_kd, float swing_starti);
  void right_swing_to_angle(float angle);
  void right_swing_to_angle(float angle, float swing_max, float swing_settle_error, float swing_settle_time, float swing_timeout, float swing_kp, float swing_ki, float swing_kd, float swing_starti);
  //void lift_to_position(float position, float lift_max_voltage, float lift_settle_error, float lift_settle_time, float lift_timeout, float lift_kp, float lift_ki, float lift_kd, float lift_starti);

  void swing(int direction, float angle);

  Odom odom;
  float get_ForwardTracker_position();
  float get_SidewaysTracker_position();
  void set_coordinates(float X_position, float Y_position, float orientation_deg);
  void set_heading(float orientation_deg);
  void position_track();
  static int position_track_task();
  vex::task odom_task;
  float get_X_position();
  float get_Y_position();

  void drive_stop(vex::brakeType mode);

  void drive_to_point(float X_position, float Y_position);
  void drive_to_point(float X_position, float Y_position, float lin_min, float lin_max, float theta_max);
  void drive_to_point(float X_position, float Y_position, float lin_min, float lin_max, float theta_max, float lin_settle_error, float lin_settle_time, float lin_timeout);
  void drive_to_point(float X_position, float Y_position, float lin_min, float lin_max, float theta_max, float lin_settle_error, float lin_settle_time, float lin_timeout, float lin_kp, float lin_ki, float lin_kd, float lin_starti, float theta_kp, float theta_ki, float theta_kd, float theta_starti);
  
  void drive_to_pose(float X_position, float Y_position, float angle);
  void drive_to_pose(float X_position, float Y_position, float angle, float lead, float setback, float lin_min);
  void drive_to_pose(float X_position, float Y_position, float angle, float lead, float setback, float lin_min, float lin_max, float theta_max);
  void drive_to_pose(float X_position, float Y_position, float angle, float lead, float setback, float lin_min, float lin_max, float theta_max, float lin_settle_error, float lin_settle_time, float lin_timeout);
  void drive_to_pose(float X_position, float Y_position, float angle, float lead, float setback, float lin_min, float lin_max, float theta_max, float lin_settle_error, float lin_settle_time, float lin_timeout, float lin_kp, float lin_ki, float lin_kd, float lin_starti, float theta_kp, float theta_ki, float theta_kd, float theta_starti);
  
  void turn_to_point(float X_position, float Y_position);
  void turn_to_point(float X_position, float Y_position, float extra_angle_deg);
  void turn_to_point(float X_position, float Y_position, float extra_angle_deg, float ang_max, float ang_settle_error, float ang_settle_time, float ang_timeout);
  void turn_to_point(float X_position, float Y_position, float extra_angle_deg, float ang_max, float ang_settle_error, float ang_settle_time, float ang_timeout, float ang_kp, float ang_ki, float ang_kd, float ang_starti);
  
  void holonomic_drive_to_pose(float X_position, float Y_position);
  void holonomic_drive_to_pose(float X_position, float Y_position, float angle);
  void holonomic_drive_to_pose(float X_position, float Y_position, float angle, float lin_max, float theta_max);
  void holonomic_drive_to_pose(float X_position, float Y_position, float angle, float lin_max, float theta_max, float lin_settle_error, float lin_settle_time, float lin_timeout);
  void holonomic_drive_to_pose(float X_position, float Y_position, float angle, float lin_max, float theta_max, float lin_settle_error, float lin_settle_time, float lin_timeout, float lin_kp, float lin_ki, float lin_kd, float lin_starti, float theta_kp, float theta_ki, float theta_kd, float theta_starti);

  void arcade(int deadzone, bool curve, int power);
  void tank();
  void holonomic();
};

// chassis
void moveChassis(float left, float right);