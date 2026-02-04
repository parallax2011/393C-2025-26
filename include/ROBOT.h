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

  float turn_max;
  float turn_kp;
  float turn_ki;
  float turn_kd;
  float turn_ksi;

  float turn_settle_error;
  float turn_settle_time;
  float turn_timeout;

  float lin_min;
  float lin_max;
  float lin_kp;
  float lin_ki;
  float lin_kd;
  float lin_ksi;

  float lin_settle_error;
  float lin_settle_time;
  float lin_timeout;

  float ang_max;
  float ang_kp;
  float ang_ki;
  float ang_kd;
  float ang_ksi;

  float swing_max;
  float swing_kp;
  float swing_ki;
  float swing_kd;
  float swing_ksi;

  float swing_settle_error;
  float swing_settle_time;
  float swing_timeout;

  float boomerang_lead;
  float boomerang_setback;

  Drive(enum::drive_setup drive_setup, motor_group DriveL, motor_group DriveR, int gyro_port, float wheel_diameter, float wheel_ratio, float gyro_scale, int DriveLF_port, int DriveRF_port, int DriveLB_port, int DriveRB_port, int ForwardTracker_port, float ForwardTracker_diameter, float ForwardTracker_center_distance, int SidewaysTracker_port, float SidewaysTracker_diameter, float SidewaysTracker_center_distance);

  void spinVolts(float left, float right);

  float getAbsTheta();
  float getLeftPos();
  float getRightPos();

  void setTurn(float turn_max, float turn_kp, float turn_ki, float turn_kd, float turn_ksi); 
  void setLin(float lin_max, float lin_kp, float lin_ki, float lin_kd, float lin_ksi);
  void setAng(float ang_max, float ang_kp, float ang_ki, float ang_kd, float ang_ksi);
  void setSwing(float swing_max, float swing_kp, float swing_ki, float swing_kd, float swing_ksi);

  void setTurnExits(float turn_settle_error, float turn_settle_time, float turn_timeout);
  void setLinExits(float lin_settle_error, float lin_settle_time, float lin_timeout);
  void setSwingExits(float swing_settle_error, float swing_settle_time, float swing_timeout);

  void turn(float angle);
  void turn(float angle, float max);
  void turn(float angle, float max, float timeout);
  void turn(float angle, float max, float settleError, float settleTime, float timeout);
  void kTurn(float angle, float turn_max, float turn_kp, float turn_ki, float turn_kd, float turn_ksi);
  void turn_to_angle(float angle, float turn_max, float turn_settle_error, float turn_settle_time, float turn_timeout);
  void turn_to_angle(float angle, float turn_max, float turn_settle_error, float turn_settle_time, float turn_timeout, float turn_kp, float turn_ki, float turn_kd, float turn_ksi);

  void move(float dist);
  void move(float dist, float max);
  void move(float dist, float max, float timeout);
  void move(float dist, float max, float settleError, float settleTime, float timeout);

//   struct ArcParams {
//   float linMax  = 0;        // 0 means "use default"
//   float angMax  = 0;
//   float timeout = 0;
// };

  void arc(float distance, float heading);
//   void arc(float distance, float heading, const ArcParams& p);
  void arc(float distance, float heading, float timeout);
  void arc(float distance, float heading, float max, float thetaMax, float timeout);
  void drive_distance(float distance, float heading, float lin_max, float ang_max);
  void drive_distance(float distance, float heading, float lin_max, float ang_max, float lin_settle_error, float lin_settle_time, float lin_timeout);
  void drive_distance(float distance, float heading, float lin_max, float ang_max, float lin_settle_error, float lin_settle_time, float lin_timeout, float lin_kp, float lin_ki, float lin_kd, float lin_ksi, float ang_kp, float ang_ki, float ang_kd, float ang_ksi);

  void chainedArc(float dist, float heading, float distToChain);

  void leftSwing(float angle);
  void leftSwing(float angle, float swing_max, float swing_settle_error, float swing_settle_time, float swing_timeout, float swing_kp, float swing_ki, float swing_kd, float swing_ksi);
  void rightSwing(float angle);
  void rightSwing(float angle, float swing_max, float swing_settle_error, float swing_settle_time, float swing_timeout, float swing_kp, float swing_ki, float swing_kd, float swing_ksi);
  //void lift_to_position(float position, float lift_max_voltage, float lift_settle_error, float lift_settle_time, float lift_timeout, float lift_kp, float lift_ki, float lift_kd, float lift_ksi);

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
  void drive_to_point(float X_position, float Y_position, float lin_min, float lin_max, float ang_max);
  void drive_to_point(float X_position, float Y_position, float lin_min, float lin_max, float ang_max, float lin_settle_error, float lin_settle_time, float lin_timeout);
  void drive_to_point(float X_position, float Y_position, float lin_min, float lin_max, float ang_max, float lin_settle_error, float lin_settle_time, float lin_timeout, float lin_kp, float lin_ki, float lin_kd, float lin_ksi, float ang_kp, float ang_ki, float ang_kd, float ang_ksi);
  
  void drive_to_pose(float X_position, float Y_position, float angle);
  void drive_to_pose(float X_position, float Y_position, float angle, float lead, float setback, float lin_min);
  void drive_to_pose(float X_position, float Y_position, float angle, float lead, float setback, float lin_min, float lin_max, float ang_max);
  void drive_to_pose(float X_position, float Y_position, float angle, float lead, float setback, float lin_min, float lin_max, float ang_max, float lin_settle_error, float lin_settle_time, float lin_timeout);
  void drive_to_pose(float X_position, float Y_position, float angle, float lead, float setback, float lin_min, float lin_max, float ang_max, float lin_settle_error, float lin_settle_time, float lin_timeout, float lin_kp, float lin_ki, float lin_kd, float lin_ksi, float ang_kp, float ang_ki, float ang_kd, float ang_ksi);
  
  void turn_to_point(float X_position, float Y_position);
  void turn_to_point(float X_position, float Y_position, float extra_angle_deg);
  void turn_to_point(float X_position, float Y_position, float extra_angle_deg, float turn_max, float turn_settle_error, float turn_settle_time, float turn_timeout);
  void turn_to_point(float X_position, float Y_position, float extra_angle_deg, float turn_max, float turn_settle_error, float turn_settle_time, float turn_timeout, float turn_kp, float turn_ki, float turn_kd, float turn_ksi);
  
  void holonomic_drive_to_pose(float X_position, float Y_position);
  void holonomic_drive_to_pose(float X_position, float Y_position, float angle);
  void holonomic_drive_to_pose(float X_position, float Y_position, float angle, float lin_max, float ang_max);
  void holonomic_drive_to_pose(float X_position, float Y_position, float angle, float lin_max, float ang_max, float lin_settle_error, float lin_settle_time, float lin_timeout);
  void holonomic_drive_to_pose(float X_position, float Y_position, float angle, float lin_max, float ang_max, float lin_settle_error, float lin_settle_time, float lin_timeout, float lin_kp, float lin_ki, float lin_kd, float lin_ksi, float ang_kp, float ang_ki, float ang_kd, float ang_ksi);

  void arcade(int deadzone, bool curve, int power);
  void tank();
  void holonomic();
};

// chassis
void moveChassis(float left, float right);