#pragma once
#include "vex.h"

class pid
{
public:
  float error = 0;
  float kp = 0;
  float ki = 0;
  float kd = 0;
  float ksi = 0;
  float settle_error = 0;
  float settle_time = 0;
  float timeout = 0;
  float accumulated_error = 0;
  float previous_error = 0;
  float output = 0;
  float time_spent_settled = 0;
  float time_spent_running = 0;
  float update_period = 10;

  pid(float error, float kp, float ki, float kd, float ksi);

  pid(float error, float kp, float ki, float kd, float ksi, float settle_error, float settle_time, float timeout);

  pid(float error, float kp, float ki, float kd, float ksi, float settle_error, float settle_time, float timeout, float update_period);

  float calc(float error);

  bool is_settled();
};