#include "vex.h"

using namespace std;

// JAR template drive setup
#pragma region
/**
 * Drive constructor for the chassis.
 * Even though there's only one constructor, there can be
 * huge differences in implementation depending on the drive style
 * selected.
 * 
 * @param drive_setup The style of drive, such as TANK_TWO_ROTATION.
 * @param DriveL Left motor group.
 * @param DriveR Right motor group.
 * @param gyro_port IMU port.
 * @param wheel_diameter Wheel diameter in inches.
 * @param wheel_ratio External drive gear ratio.
 * @param gyro_scale Scale factor in degrees.
 * @param DriveLF_port Left front port for holonomic drives.
 * @param DriveRF_port Right front port for holonomic drives.
 * @param DriveLB_port Left back port for holonomic drives.
 * @param DriveRB_port Right back port for holonomic drives.
 * @param ForwardTracker_port Port for the forward tracker.
 * @param ForwardTracker_diameter Diameter in inches.
 * @param ForwardTracker_center_distance Horizontal distance in inches.
 * @param SidewaysTracker_port Port for the sideways tracker.
 * @param SidewaysTracker_diameter Diameter in inches.
 * @param SidewaysTracker_center_distance Vertical distance in inches.
 */

Drive::Drive(enum::drive_setup drive_setup, motor_group DriveL, motor_group DriveR, 
int gyro_port, float wheel_diameter, float wheel_ratio, float gyro_scale, 
int DriveLF_port, int DriveRF_port, int DriveLB_port, int DriveRB_port, 
int ForwardTracker_port, float ForwardTracker_diameter, float ForwardTracker_center_distance, 
int SidewaysTracker_port, float SidewaysTracker_diameter, float SidewaysTracker_center_distance) :
  wheel_diameter(wheel_diameter),
  wheel_ratio(wheel_ratio),
  gyro_scale(gyro_scale),
  drive_in_to_deg_ratio(wheel_ratio/360.0*M_PI*wheel_diameter),
  ForwardTracker_center_distance(ForwardTracker_center_distance),
  ForwardTracker_diameter(ForwardTracker_diameter),
  ForwardTracker_in_to_deg_ratio(M_PI*ForwardTracker_diameter/360.0),
  SidewaysTracker_center_distance(SidewaysTracker_center_distance),
  SidewaysTracker_diameter(SidewaysTracker_diameter),
  SidewaysTracker_in_to_deg_ratio(M_PI*SidewaysTracker_diameter/360.0),
  drive_setup(drive_setup),
  DriveL(DriveL),
  DriveR(DriveR),
  Gyro(inertial(gyro_port)),
  DriveLF(abs(DriveLF_port), is_reversed(DriveLF_port)),
  DriveRF(abs(DriveRF_port), is_reversed(DriveRF_port)),
  DriveLB(abs(DriveLB_port), is_reversed(DriveLB_port)),
  DriveRB(abs(DriveRB_port), is_reversed(DriveRB_port)),
  R_ForwardTracker(ForwardTracker_port),
  R_SidewaysTracker(SidewaysTracker_port),
  E_ForwardTracker(ThreeWire.Port[to_port(ForwardTracker_port)]),
  E_SidewaysTracker(ThreeWire.Port[to_port(SidewaysTracker_port)])
{
    if (drive_setup == TANK_ONE_FORWARD_ENCODER || drive_setup == TANK_ONE_FORWARD_ROTATION || drive_setup == ZERO_TRACKER_ODOM){
      odom.setPhysicalDistances(ForwardTracker_center_distance, 0);
    } 
    if (drive_setup == TANK_ONE_SIDEWAYS_ENCODER || drive_setup == TANK_ONE_SIDEWAYS_ROTATION || 
    drive_setup == TANK_TWO_ENCODER || drive_setup == TANK_TWO_ROTATION ||
    drive_setup == HOLONOMIC_TWO_ENCODER || drive_setup == HOLONOMIC_TWO_ROTATION){
      odom.setPhysicalDistances(ForwardTracker_center_distance, SidewaysTracker_center_distance);
    }
}

void Drive::spinVolts(float lVel, float rVel){
  DriveL.spin(fwd, lVel, volt);
  DriveR.spin(fwd, rVel, volt);
}

void Drive::setTurn(float turn_max, float turn_kp, float ang_ki, float ang_kd, float ang_starti){
  this->turn_max = turn_max;
  this->turn_kp = turn_kp;
  this->ang_ki = ang_ki;
  this->ang_kd = ang_kd;
  this->ang_starti = ang_starti;
} 

void Drive::setLin(float lin_max, float lin_kp, float lin_ki, float lin_kd, float lin_starti){
  this->lin_max = lin_max;
  this->lin_kp = lin_kp;
  this->lin_ki = lin_ki;
  this->lin_kd = lin_kd;
  this->lin_starti = lin_starti;
} 

void Drive::setAng(float theta_max, float theta_kp, float theta_ki, float theta_kd, float theta_starti){
  this->theta_max = theta_max;
  this->theta_kp = theta_kp;
  this->theta_ki = theta_ki;
  this->theta_kd = theta_kd;
  this->theta_starti = theta_starti;
}

void Drive::setSwing(float swing_max, float swing_kp, float swing_ki, float swing_kd, float swing_starti){
  this->swing_max = swing_max;
  this->swing_kp = swing_kp;
  this->swing_ki = swing_ki;
  this->swing_kd = swing_kd;
  this->swing_starti = swing_starti;
} 

void Drive::setTurnExits(float ang_settle_error, float ang_settle_time, float ang_timeout){
  this->ang_settle_error = ang_settle_error;
  this->ang_settle_time = ang_settle_time;
  this->ang_timeout = ang_timeout;
}

void Drive::setLinExits(float lin_settle_error, float lin_settle_time, float lin_timeout){
  this->lin_settle_error = lin_settle_error;
  this->lin_settle_time = lin_settle_time;
  this->lin_timeout = lin_timeout;
}

void Drive::setSwingExits(float swing_settle_error, float swing_settle_time, float swing_timeout){
  this->swing_settle_error = swing_settle_error;
  this->swing_settle_time = swing_settle_time;
  this->swing_timeout = swing_timeout;
}

/**
 * Gives the drive's absolute heading with Gyro correction.
 * 
 * @return Gyro scale-corrected heading in the range [0, 360).
 */

float Drive::getAbsTheta(){ 
  return( reduce_0_to_360( Gyro.rotation()*360.0/gyro_scale ) ); 
}

/**
 * Gets the motor group's position and converts to inches.
 * 
 * @return Left position in inches.
 */

float Drive::getLeftPos(){
  return( DriveL.position(deg)*drive_in_to_deg_ratio );
}

/**
 * Gets the motor group's position and converts to inches.
 * 
 * @return Right position in inches.
 */

float Drive::getRightPos(){
  return( DriveR.position(deg)*drive_in_to_deg_ratio );
}

/**
 * Stops both sides of the drive with the desired mode.
 * 
 * @param mode hold, brake, or stop
 */

void Drive::drive_stop(vex::brakeType mode){
  DriveL.stop(mode);
  DriveR.stop(mode);
}

/**
 * Turns the robot to a field-centric angle.
 * Optimizes direction, so it turns whichever way is closer to the 
 * current heading of the robot.
 * 
 * @param angle Desired angle in degrees.
 */

void Drive::turn(float angle){
  // if (angle <= 60) {
  //   chassis.ang_kd = 2.8;
  // } else if (angle <= 120) {
  //   chassis.ang_kd = 3.2;
  // } else if (angle <= 180) {
  //   chassis.ang_kd = 3.8;
  // }
  turn_to_angle(angle, turn_max, ang_settle_error, ang_settle_time, ang_timeout, turn_kp, ang_ki, ang_kd, ang_starti);
}

// void Drive::turn(float angle, float turn_max){
//   turn_to_angle(angle, turn_max, ang_settle_error, ang_settle_time, ang_timeout, turn_kp, ang_ki, ang_kd, ang_starti);
// }

void Drive::turn(float angle, float max) {
  turn_to_angle(angle, max, ang_settle_error, ang_settle_time, ang_timeout, turn_kp, ang_ki, ang_kd, ang_starti);
}

void Drive::turn(float angle, float max, float timeout) {
  turn_to_angle(angle, max, ang_settle_error, ang_settle_time, timeout, turn_kp, ang_ki, ang_kd, ang_starti);
}

void Drive::turn(float angle, float max, float settleError, float settleTime, float timeout) {
  turn_to_angle(angle, max, settleError, settleTime, timeout, turn_kp, ang_ki, ang_kd, ang_starti);
}
                                                          

void Drive::turn_to_angle(float angle, float turn_max, float ang_settle_error, float ang_settle_time, float ang_timeout){
  turn_to_angle(angle, turn_max, ang_settle_error, ang_settle_time, ang_timeout, turn_kp, ang_ki, ang_kd, ang_starti);
}

void Drive::turn_to_angle(float angle, float turn_max, float ang_settle_error, float ang_settle_time, float ang_timeout, float turn_kp, float ang_ki, float ang_kd, float ang_starti){
  pid pid_turn(reduce_negative_180_to_180(angle - getAbsTheta()), turn_kp, ang_ki, ang_kd, ang_starti, ang_settle_error, ang_settle_time, ang_timeout);
  while( !pid_turn.is_settled() ){
    // float absHeading = getAbsTheta();
    float error = reduce_negative_180_to_180(angle - getAbsTheta());
    float output = pid_turn.calc(error);
    output = clamp(output, -turn_max, turn_max);
    spinVolts(output, -output);
    //std::cout << "Ang: " << getAbsTheta() << std::endl;
    task::sleep(10);
  }
//   std::cout << "Ang: " << getAbsTheta() << std::endl;
}

void Drive::kTurn(float angle, float turn_max, float turn_kp, float ang_ki, float ang_kd, float ang_starti) {
  turn_to_angle(angle, turn_max, ang_settle_error, ang_settle_time, ang_timeout, turn_kp, ang_ki, ang_kd, ang_starti);
}     

/**
 * Drives the robot a given distance with a given heading.
 * Drive distance does not optimize for direction, so it won't try
 * to drive at the opposite heading from the one given to get there faster.
 * You can control the heading, but if you choose not to, it will drive with the
 * heading it's currently facing. It uses the average of the left and right
 * motor groups to calculate distance driven.
 * 
 * @param distance Desired distance in inches.
 * @param heading Desired heading in degrees.
 */

void Drive::move(float distance){
  drive_distance(distance, getAbsTheta(), lin_max, theta_max, lin_settle_error, lin_settle_time, lin_timeout, lin_kp, lin_ki, lin_kd, lin_starti, theta_kp, theta_ki, theta_kd, theta_starti);
}

// void Drive::arc(float distance, float heading, const ArcParams& p) {
//   drive_distance( distance, heading, p.linMax, p.angMax, lin_settle_error, lin_settle_time, p.timeout, lin_kp, lin_ki, lin_kd, lin_starti, theta_kp, theta_ki, theta_kd, theta_starti);
// }


void Drive::arc(float distance, float heading){
  drive_distance(distance, heading, lin_max, theta_max, lin_settle_error, lin_settle_time, lin_timeout, lin_kp, lin_ki, lin_kd, lin_starti, theta_kp, theta_ki, theta_kd, theta_starti);
}

void Drive::arc(float distance, float heading, float timeout){
  drive_distance(distance, heading, lin_max, theta_max, lin_settle_error, lin_settle_time, timeout, lin_kp, lin_ki, lin_kd, lin_starti, theta_kp, theta_ki, theta_kd, theta_starti);
}


void Drive::arc(float distance, float heading, float max, float thetaMax, float timeout){
  drive_distance(distance, heading, max, thetaMax, lin_settle_error, lin_settle_time, timeout, lin_kp, lin_ki, lin_kd, lin_starti, theta_kp, theta_ki, theta_kd, theta_starti);
}

void Drive::move(float distance, float max_voltage) {
  drive_distance(distance, getAbsTheta(), max_voltage, theta_max, lin_settle_error, lin_settle_time, lin_timeout, lin_kp, lin_ki, lin_kd, lin_starti, theta_kp, theta_ki, theta_kd, theta_starti);
}

void Drive::move(float distance, float max_voltage, float timeout) {
  drive_distance(distance, getAbsTheta(), max_voltage, theta_max, lin_settle_error, lin_settle_time, timeout, lin_kp, lin_ki, lin_kd, lin_starti, theta_kp, theta_ki, theta_kd, theta_starti);
}

void Drive::move(float distance, float max_voltage, float settleError, float settleTime, float timeout) {
  drive_distance(distance, getAbsTheta(), max_voltage, theta_max, settleError, settleTime, timeout, lin_kp, lin_ki, lin_kd, lin_starti, theta_kp, theta_ki, theta_kd, theta_starti);
}

void Drive::drive_distance(float distance, float heading, float lin_max, float theta_max){
  drive_distance(distance, heading, lin_max, theta_max, lin_settle_error, lin_settle_time, lin_timeout, lin_kp, lin_ki, lin_kd, lin_starti, theta_kp, theta_ki, theta_kd, theta_starti);
}

void Drive::drive_distance(float distance, float heading, float lin_max, float theta_max, float lin_settle_error, float lin_settle_time, float lin_timeout){
  drive_distance(distance, heading, lin_max, theta_max, lin_settle_error, lin_settle_time, lin_timeout, lin_kp, lin_ki, lin_kd, lin_starti, theta_kp, theta_ki, theta_kd, theta_starti);
}

void Drive::drive_distance(float distance, float heading, float lin_max, float theta_max, float lin_settle_error, float lin_settle_time, float lin_timeout, float lin_kp, float lin_ki, float lin_kd, float lin_starti, float theta_kp, float theta_ki, float theta_kd, float theta_starti){
  pid pid_lin(distance, lin_kp, lin_ki, lin_kd, lin_starti, lin_settle_error, lin_settle_time, lin_timeout);
  pid pid_theta(reduce_negative_180_to_180(heading - getAbsTheta()), theta_kp, theta_ki, theta_kd, theta_starti);
  float startAvgPosition = (getLeftPos() + getRightPos()) / 2.0;
  float avgPosition = startAvgPosition;

  while(pid_lin.is_settled() == false){
    // float absHeading = getAbsTheta();

    avgPosition = (getLeftPos()+getRightPos())/2.0;
    float lin_error = distance + startAvgPosition - avgPosition;
    
    float theta_error = reduce_negative_180_to_180(heading - getAbsTheta());
    float drive_output = pid_lin.calc(lin_error);
    float heading_output = pid_theta.calc(theta_error);

    drive_output = clamp(drive_output, -lin_max, lin_max);
    heading_output = clamp(heading_output, -theta_max, theta_max);

    //auto accelStart = std::chrono::high_resolution_clock::now();

    spinVolts(drive_output + heading_output, drive_output - heading_output);

    // if (distance > 0) {
    //     if (lf.direction() == vex::reverse or lm.direction() == vex::reverse or lb.direction() == vex::reverse or rf.direction() == vex::reverse or rm.direction() == vex::reverse or rb.direction() == vex::reverse) {
    //         settledState = 1; // entered settling/oscillation state
    //         initOvershoot = drive_error;
    //         auto accelEnd = std::chrono::high_resolution_clock::now();
    //         accelTime = accelEnd - accelStart;
    //     }
    // }

    task::sleep(10);
  }

}

/**
 * Turns to a given angle with only one side of the drivetrain.
 * Like turn_to_angle(), is optimized for turning the shorter
 * direction.
 * 
 * @param angle Desired angle in degrees.
 */

void Drive::leftSwing(float angle){
  leftSwing(angle, swing_max, swing_settle_error, swing_settle_time, swing_timeout, swing_kp, swing_ki, swing_kd, swing_starti);
}

void Drive::leftSwing(float angle, float swing_max, float swing_settle_error, float swing_settle_time, float swing_timeout, float swing_kp, float swing_ki, float swing_kd, float swing_starti){
  pid swingPID(reduce_negative_180_to_180(angle - getAbsTheta()), swing_kp, swing_ki, swing_kd, swing_starti, swing_settle_error, swing_settle_time, swing_timeout);
  while(swingPID.is_settled() == false){
    // float absHeading = getAbsTheta();
    float error = reduce_negative_180_to_180(angle - getAbsTheta());
    float output = swingPID.calc(error);
    output = clamp(output, -turn_max, turn_max);
    DriveL.spin(fwd, output, volt);
    DriveR.stop(hold);
    //std::cout << absHeading << '\n';
    task::sleep(10);
  }
}

void Drive::rightSwing(float angle){
  rightSwing(angle, swing_max, swing_settle_error, swing_settle_time, swing_timeout, swing_kp, swing_ki, swing_kd, swing_starti);
}

void Drive::rightSwing(float angle, float swing_max, float swing_settle_error, float swing_settle_time, float swing_timeout, float swing_kp, float swing_ki, float swing_kd, float swing_starti){
  pid swingPID(reduce_negative_180_to_180(angle - getAbsTheta()), swing_kp, swing_ki, swing_kd, swing_starti, swing_settle_error, swing_settle_time, swing_timeout);
  while(swingPID.is_settled() == false){
    // float absHeading = getAbsTheta();
    float error = reduce_negative_180_to_180(angle - getAbsTheta());
    float output = swingPID.calc(error);
    output = clamp(output, -turn_max, turn_max);
    DriveR.spin(vex::reverse, output, volt);
    DriveL.stop(hold);
    //std::cout << absHeading << '\n';
    task::sleep(10);
  }
}

void Drive::swing(int direction, float angle) {
  if (direction == LEFT) {
    leftSwing(angle);
  } else if (direction == RIGHT) {
    rightSwing(angle);
  }
}

/**
 * Depending on the drive style, gets the tracker's position.
 * 
 * @return The tracker position.
 */

float Drive::get_ForwardTracker_position(){
  if (drive_setup==ZERO_TRACKER_ODOM || drive_setup == TANK_ONE_SIDEWAYS_ENCODER || drive_setup == TANK_ONE_SIDEWAYS_ROTATION){
    return(getRightPos());
  }
  if (drive_setup==TANK_ONE_FORWARD_ENCODER || drive_setup == TANK_TWO_ENCODER || drive_setup == HOLONOMIC_TWO_ENCODER){
    return(E_ForwardTracker.position(deg)*ForwardTracker_in_to_deg_ratio);
  }else{
    return(R_ForwardTracker.position(deg)*ForwardTracker_in_to_deg_ratio);
  }
}

/**
 * Depending on the drive style, gets the tracker's position.
 * 
 * @return The tracker position.
 */

float Drive::get_SidewaysTracker_position(){
  if (drive_setup==TANK_ONE_FORWARD_ENCODER || drive_setup == TANK_ONE_FORWARD_ROTATION || drive_setup == ZERO_TRACKER_ODOM){
    return(0);
  }else if (drive_setup == TANK_TWO_ENCODER || drive_setup == HOLONOMIC_TWO_ENCODER || drive_setup == TANK_ONE_SIDEWAYS_ENCODER){
    return(E_SidewaysTracker.position(deg)*SidewaysTracker_in_to_deg_ratio);
  }else{
    return(R_SidewaysTracker.position(deg)*SidewaysTracker_in_to_deg_ratio);
  }
}

/**
 * Background task for updating the odometry.
 */

void Drive::position_track(){
  while(1){
    odom.updatePosition(get_ForwardTracker_position(), get_SidewaysTracker_position(), getAbsTheta());
    task::sleep(5);
  }
}

/**
 * Resets the robot's heading.
 * For example, at the beginning of auton, if your robot starts at
 * 45 degrees, so set_heading(45) and the robot will know which way 
 * it's facing.
 * 
 * @param orientation_deg Desired heading in degrees.
 */

void Drive::set_heading(float orientation_deg){
  Gyro.setRotation(orientation_deg*gyro_scale/360.0, deg);
}

/**
 * Resets the robot's coordinates and heading.
 * This is for odom-using robots to specify where the bot is at the beginning
 * of the match.
 * 
 * @param X_position Robot's x in inches.
 * @param Y_position Robot's y in inches.
 * @param orientation_deg Desired heading in degrees.
 */

void Drive::set_coordinates(float X_position, float Y_position, float orientation_deg){
  odom.setPosition(X_position, Y_position, orientation_deg, get_ForwardTracker_position(), get_SidewaysTracker_position());
  set_heading(orientation_deg);
  odom_task = task(position_track_task);
}

/**
 * Gets the robot's x.
 * 
 * @return The robot's x position in inches.
 */

float Drive::get_X_position(){
  return(odom.X_position);
}

/**
 * Gets the robot's y.
 * 
 * @return The robot's y position in inches.
 */

float Drive::get_Y_position(){
  return(odom.Y_position);
}

/**
 * Drives to a specified point on the field.
 * Uses the double-PID method, with one for driving and one for heading correction.
 * The drive error is the euclidean distance to the desired point, and the heading error
 * is the turn correction from the current heading to the desired point. Uses optimizations
 * like driving backwards whenever possible and scaling the drive output with the cosine
 * of the angle to the point.
 * 
 * @param X_position Desired x position in inches.
 * @param Y_position Desired y position in inches.
 */

void Drive::drive_to_point(float X_position, float Y_position){
  drive_to_point(X_position, Y_position, lin_min, lin_max, theta_max, lin_settle_error, lin_settle_time, lin_timeout, lin_kp, lin_ki, lin_kd, lin_starti, theta_kp, theta_ki, theta_kd, theta_starti);
}

void Drive::drive_to_point(float X_position, float Y_position, float lin_min, float lin_max, float theta_max){
  drive_to_point(X_position, Y_position, lin_min, lin_max, theta_max, lin_settle_error, lin_settle_time, lin_timeout, lin_kp, lin_ki, lin_kd, lin_starti, theta_kp, theta_ki, theta_kd, theta_starti);
}

void Drive::drive_to_point(float X_position, float Y_position, float lin_min, float lin_max, float theta_max, float lin_settle_error, float lin_settle_time, float lin_timeout){
  drive_to_point(X_position, Y_position, lin_min, lin_max, theta_max, lin_settle_error, lin_settle_time, lin_timeout, lin_kp, lin_ki, lin_kd, lin_starti, theta_kp, theta_ki, theta_kd, theta_starti);
}

void Drive::drive_to_point(float X_position, float Y_position, float lin_min, float lin_max, float theta_max, float lin_settle_error, float lin_settle_time, float lin_timeout, float lin_kp, float lin_ki, float lin_kd, float lin_starti, float theta_kp, float theta_ki, float theta_kd, float theta_starti){
  pid drivePID(hypot(X_position-get_X_position(),Y_position-get_Y_position()), lin_kp, lin_ki, lin_kd, lin_starti, lin_settle_error, lin_settle_time, lin_timeout);
  float start_angle_deg = to_deg(atan2(X_position-get_X_position(),Y_position-get_Y_position()));
  pid headingPID(start_angle_deg-getAbsTheta(), theta_kp, theta_ki, theta_kd, theta_starti);
  bool line_settled = false;
  bool prev_line_settled = is_line_settled(X_position, Y_position, start_angle_deg, get_X_position(), get_Y_position());
  while(!drivePID.is_settled()){
    line_settled = is_line_settled(X_position, Y_position, start_angle_deg, get_X_position(), get_Y_position());
    if(line_settled && !prev_line_settled){ break; }
    prev_line_settled = line_settled;

    float drive_error = hypot(X_position-get_X_position(),Y_position-get_Y_position());
    float heading_error = reduce_negative_180_to_180(to_deg(atan2(X_position-get_X_position(),Y_position-get_Y_position()))-getAbsTheta());
    float drive_output = drivePID.calc(drive_error);

    float heading_scale_factor = cos(to_rad(heading_error));
    drive_output*=heading_scale_factor;
    heading_error = reduce_negative_90_to_90(heading_error);
    float heading_output = headingPID.calc(heading_error);
    
    if (drive_error<lin_settle_error) { heading_output = 0; }

    drive_output = clamp(drive_output, -fabs(heading_scale_factor)*lin_max, fabs(heading_scale_factor)*lin_max);
    heading_output = clamp(heading_output, -theta_max, theta_max);

    drive_output = clamp_min_voltage(drive_output, lin_min);

    spinVolts(left_voltage_scaling(drive_output, heading_output), right_voltage_scaling(drive_output, heading_output));
    task::sleep(10);
  }
}

/**
 * Drives to a specified point and orientation on the field.
 * Uses a boomerang controller. The carrot point is back from the target
 * by the same distance as the robot's distance to the target, times the lead. The
 * robot always tries to go to the carrot, which is constantly moving, and the
 * robot eventually gets into position. The heading correction is optimized to only
 * try to reach the correct angle when drive error is low, and the robot will drive 
 * backwards to reach a pose if it's faster. .5 is a reasonable value for the lead. 
 * The setback parameter is used to glide into position more effectively. It is
 * the distance back from the target that the robot tries to drive to first.
 * 
 * @param X_position Desired x position in inches.
 * @param Y_position Desired y position in inches.
 * @param angle Desired orientation in degrees.
 * @param lead Constant scale factor that determines how far away the carrot point is. 
 * @param setback Distance in inches from target by which the carrot is always pushed back.
 * @param lin_min Minimum voltage on the drive, used for chaining movements.
 */

void Drive::drive_to_pose(float X_position, float Y_position, float angle){
  drive_to_pose(X_position, Y_position, angle, boomerang_lead, boomerang_setback, lin_min, lin_max, theta_max, lin_settle_error, lin_settle_time, lin_timeout, lin_kp, lin_ki, lin_kd, lin_starti, theta_kp, theta_ki, theta_kd, theta_starti);
}

void Drive::drive_to_pose(float X_position, float Y_position, float angle, float lead, float setback, float lin_min){
  drive_to_pose(X_position, Y_position, angle, lead, setback, lin_min, lin_max, theta_max, lin_settle_error, lin_settle_time, lin_timeout, lin_kp, lin_ki, lin_kd, lin_starti, theta_kp, theta_ki, theta_kd, theta_starti);
}

void Drive::drive_to_pose(float X_position, float Y_position, float angle, float lead, float setback, float lin_min, float lin_max, float theta_max){
  drive_to_pose(X_position, Y_position, angle, lead, setback, lin_min, lin_max, theta_max, lin_settle_error, lin_settle_time, lin_timeout, lin_kp, lin_ki, lin_kd, lin_starti, theta_kp, theta_ki, theta_kd, theta_starti);
}


void Drive::drive_to_pose(float X_position, float Y_position, float angle, float lead, float setback, float lin_min, float lin_max, float theta_max, float lin_settle_error, float lin_settle_time, float lin_timeout){
  drive_to_pose(X_position, Y_position, angle, lead, setback, lin_min, lin_max, theta_max, lin_settle_error, lin_settle_time, lin_timeout, lin_kp, lin_ki, lin_kd, lin_starti, theta_kp, theta_ki, theta_kd, theta_starti);
}

void Drive::drive_to_pose(float X_position, float Y_position, float angle, float lead, float setback, float lin_min, float lin_max, float theta_max, float lin_settle_error, float lin_settle_time, float lin_timeout, float lin_kp, float lin_ki, float lin_kd, float lin_starti, float theta_kp, float theta_ki, float theta_kd, float theta_starti){
  float target_distance = hypot(X_position-get_X_position(),Y_position-get_Y_position());
  pid drivePID(target_distance, lin_kp, lin_ki, lin_kd, lin_starti, lin_settle_error, lin_settle_time, lin_timeout);
  pid headingPID(to_deg(atan2(X_position-get_X_position(),Y_position-get_Y_position()))-getAbsTheta(), theta_kp, theta_ki, theta_kd, theta_starti);
  bool line_settled = is_line_settled(X_position, Y_position, angle, get_X_position(), get_Y_position());
  bool prev_line_settled = is_line_settled(X_position, Y_position, angle, get_X_position(), get_Y_position());
  bool crossed_center_line = false;
  bool center_line_side = is_line_settled(X_position, Y_position, angle+90, get_X_position(), get_Y_position());
  bool prev_center_line_side = center_line_side;
  while(!drivePID.is_settled()){
    line_settled = is_line_settled(X_position, Y_position, angle, get_X_position(), get_Y_position());
    if(line_settled && !prev_line_settled){ break; }
    prev_line_settled = line_settled;

    center_line_side = is_line_settled(X_position, Y_position, angle+90, get_X_position(), get_Y_position());
    if(center_line_side != prev_center_line_side){
      crossed_center_line = true;
    }

    target_distance = hypot(X_position-get_X_position(),Y_position-get_Y_position());

    float carrot_X = X_position - sin(to_rad(angle)) * (lead * target_distance + setback);
    float carrot_Y = Y_position - cos(to_rad(angle)) * (lead * target_distance + setback);

    float drive_error = hypot(carrot_X-get_X_position(),carrot_Y-get_Y_position());
    float heading_error = reduce_negative_180_to_180(to_deg(atan2(carrot_X-get_X_position(),carrot_Y-get_Y_position()))-getAbsTheta());

    if (drive_error<lin_settle_error || crossed_center_line || drive_error < setback) { 
      heading_error = reduce_negative_180_to_180(angle-getAbsTheta()); 
      drive_error = target_distance;
    }
    
    float drive_output = drivePID.calc(drive_error);

    float heading_scale_factor = cos(to_rad(heading_error));
    drive_output*=heading_scale_factor;
    heading_error = reduce_negative_90_to_90(heading_error);
    float heading_output = headingPID.calc(heading_error);

    drive_output = clamp(drive_output, -fabs(heading_scale_factor)*lin_max, fabs(heading_scale_factor)*lin_max);
    heading_output = clamp(heading_output, -theta_max, theta_max);

    drive_output = clamp_min_voltage(drive_output, lin_min);

    spinVolts(left_voltage_scaling(drive_output, heading_output), right_voltage_scaling(drive_output, heading_output));
    task::sleep(10);
  }
}

/**
 * Turns to a specified point on the field.
 * Functions similarly to turn_to_angle() except with a point. The
 * extra_angle_deg parameter turns the robot extra relative to the 
 * desired target. For example, if you want the back of your robot
 * to point at (36, 42), you would run turn_to_point(36, 42, 180).
 * 
 * @param X_position Desired x position in inches.
 * @param Y_position Desired y position in inches.
 * @param extra_angle_deg Angle turned past the desired heading in degrees.
 */

void Drive::turn_to_point(float X_position, float Y_position){
  turn_to_point(X_position, Y_position, 0, turn_max, ang_settle_error, ang_settle_time, ang_timeout, turn_kp, ang_ki, ang_kd, ang_starti);
}

void Drive::turn_to_point(float X_position, float Y_position, float extra_angle_deg){
  turn_to_point(X_position, Y_position, extra_angle_deg, turn_max, ang_settle_error, ang_settle_time, ang_timeout, turn_kp, ang_ki, ang_kd, ang_starti);
}

void Drive::turn_to_point(float X_position, float Y_position, float extra_angle_deg, float turn_max, float ang_settle_error, float ang_settle_time, float ang_timeout){
  turn_to_point(X_position, Y_position, extra_angle_deg, turn_max, ang_settle_error, ang_settle_time, ang_timeout, turn_kp, ang_ki, ang_kd, ang_starti);
}

void Drive::turn_to_point(float X_position, float Y_position, float extra_angle_deg, float turn_max, float ang_settle_error, float ang_settle_time, float ang_timeout, float turn_kp, float ang_ki, float ang_kd, float ang_starti){
  pid turnPID(reduce_negative_180_to_180(to_deg(atan2(X_position-get_X_position(),Y_position-get_Y_position())) - getAbsTheta()), turn_kp, ang_ki, ang_kd, ang_starti, ang_settle_error, ang_settle_time, ang_timeout);
  while(turnPID.is_settled() == false){
    float error = reduce_negative_180_to_180(to_deg(atan2(X_position-get_X_position(),Y_position-get_Y_position())) - getAbsTheta() + extra_angle_deg);
    float output = turnPID.calc(error);
    output = clamp(output, -turn_max, turn_max);
    spinVolts(output, -output);
    task::sleep(10);
  }
}

/**
 * Drives and turns simultaneously to a desired pose.
 * Uses two PID loops, one drive and one heading to drive and turn
 * at the same time. Optimized to turn the quicker direction and only
 * exits once both PID loops have settled. It uses the heading constants
 * for heading but the turn exit conditions to settle.
 * 
 * @param X_position Desired x position in inches.
 * @param Y_position Desired y position in inches.
 * @param angle Desired ending angle in degrees.
 */

void Drive::holonomic_drive_to_pose(float X_position, float Y_position){
  holonomic_drive_to_pose(X_position, Y_position, getAbsTheta(), lin_max, theta_max, lin_settle_error, lin_settle_time, lin_timeout, lin_kp, lin_ki, lin_kd, lin_starti, theta_kp, theta_ki, theta_kd, theta_starti);
}

void Drive::holonomic_drive_to_pose(float X_position, float Y_position, float angle){
  holonomic_drive_to_pose(X_position, Y_position, angle, lin_max, theta_max, lin_settle_error, lin_settle_time, lin_timeout, lin_kp, lin_ki, lin_kd, lin_starti, theta_kp, theta_ki, theta_kd, theta_starti);
}

void Drive::holonomic_drive_to_pose(float X_position, float Y_position, float angle, float lin_max, float theta_max){
  holonomic_drive_to_pose(X_position, Y_position, angle, lin_max, theta_max, lin_settle_error, lin_settle_time, lin_timeout, lin_kp, lin_ki, lin_kd, lin_starti, theta_kp, theta_ki, theta_kd, theta_starti);
}

void Drive::holonomic_drive_to_pose(float X_position, float Y_position, float angle, float lin_max, float theta_max, float lin_settle_error, float lin_settle_time, float lin_timeout){
  holonomic_drive_to_pose(X_position, Y_position, angle, lin_max, theta_max, lin_settle_error, lin_settle_time, lin_timeout, lin_kp, lin_ki, lin_kd, lin_starti, theta_kp, theta_ki, theta_kd, theta_starti);
}

void Drive::holonomic_drive_to_pose(float X_position, float Y_position, float angle, float lin_max, float theta_max, float lin_settle_error, float lin_settle_time, float lin_timeout, float lin_kp, float lin_ki, float lin_kd, float lin_starti, float theta_kp, float theta_ki, float theta_kd, float theta_starti){
  pid drivePID(hypot(X_position-get_X_position(),Y_position-get_Y_position()), lin_kp, lin_ki, lin_kd, lin_starti, lin_settle_error, lin_settle_time, lin_timeout);
  pid turnPID(angle-getAbsTheta(), theta_kp, theta_ki, theta_kd, theta_starti, ang_settle_error, ang_settle_time, ang_timeout);
  while( !(drivePID.is_settled() && turnPID.is_settled()) ){
    float drive_error = hypot(X_position-get_X_position(),Y_position-get_Y_position());
    float turn_error = reduce_negative_180_to_180(angle-getAbsTheta());

    float drive_output = drivePID.calc(drive_error);
    float turn_output = turnPID.calc(turn_error);

    drive_output = clamp(drive_output, -lin_max, lin_max);
    turn_output = clamp(turn_output, -theta_max, theta_max);

    float heading_error = atan2(Y_position-get_Y_position(), X_position-get_X_position());

    DriveLF.spin(fwd, drive_output*cos(to_rad(getAbsTheta()) + heading_error - M_PI/4) + turn_output, volt);
    DriveLB.spin(fwd, drive_output*cos(-to_rad(getAbsTheta()) - heading_error + 3*M_PI/4) + turn_output, volt);
    DriveRB.spin(fwd, drive_output*cos(to_rad(getAbsTheta()) + heading_error - M_PI/4) - turn_output, volt);
    DriveRF.spin(fwd, drive_output*cos(-to_rad(getAbsTheta()) - heading_error + 3*M_PI/4) - turn_output, volt);
    task::sleep(10);
  }
}

/**
 * Controls a chassis with left stick throttle and right stick turning.
 * Default deadband is 5.
 */

void Drive::arcade(int deadzone, bool curve, int power) {
  
  float throttle;
  float turn;

  if (deadzone <= 0) {
    throttle = controller(primary).Axis3.value();
    turn = controller(primary).Axis1.value();
  } else {
    throttle = deadband(controller(primary).Axis3.value(), deadzone);
    turn = deadband(controller(primary).Axis1.value(), deadzone);
  }

  if (curve) {
    if (power == 2) {
        turn = (abs(turn) * turn) / 100;
    } else if (power == 3) {
        turn = (pow(turn, 3) / 100);
    } else if (power >= 4) {
        // t=40
        turn = std::exp(((std::abs(turn)-100) * 40)/1000) * turn;
    }
  }

  DriveL.spin(fwd, to_volt(throttle + turn), volt);
  DriveR.spin(fwd, to_volt(throttle - turn), volt);
}

/**
 * Controls a chassis with left stick throttle and strafe, and right stick turning.
 * Default deadband is 5.
 */

void Drive::holonomic(){
  float throttle = deadband(controller(primary).Axis3.value(), 5);
  float turn = deadband(controller(primary).Axis1.value(), 5);
  float strafe = deadband(controller(primary).Axis4.value(), 5);
  DriveLF.spin(fwd, to_volt(throttle+turn+strafe), volt);
  DriveRF.spin(fwd, to_volt(throttle-turn-strafe), volt);
  DriveLB.spin(fwd, to_volt(throttle+turn-strafe), volt);
  DriveRB.spin(fwd, to_volt(throttle-turn+strafe), volt);
}

/**
 * Controls a chassis with left stick left drive and right stick right drive.
 * Default deadband is 5.
 */

void Drive::tank(){
  float leftthrottle = deadband(controller(primary).Axis3.value(), 5);
  float rightthrottle = deadband(controller(primary).Axis2.value(), 5);
  DriveL.spin(fwd, to_volt(leftthrottle), volt);
  DriveR.spin(fwd, to_volt(rightthrottle), volt);
}

/**
 * Tracking task to run in the background.
 */

int Drive::position_track_task(){
  chassis.position_track();
  return(0);
}

#pragma endregion

void moveChassis(float left, float right) {
  l.spin(fwd, left, volt);
  r.spin(fwd, right, volt);
}

float curve(float i, float scale) {
  if (scale != 0)
    return (pow(2.718, (scale * ((std::fabs(i) - 100))) / 1000 ) * i);
  return i;
}