#include "vex.h"

pid::pid(float error, float kp, float ki, float kd, float ksi) :
    error(error),
    kp(kp),
    ki(ki),
    kd(kd),
    ksi(ksi)
{};

pid::pid(float error, float kp, float ki, float kd, float ksi, 
         float settle_error, float settle_time, float timeout):
    error(error),
    kp(kp),
    ki(ki),
    kd(kd),
    ksi(ksi),
    settle_error(settle_error),
    settle_time(settle_time),
    timeout(timeout)
{};

pid::pid(float error, float kp, float ki, float kd, float ksi, 
         float settle_error, float settle_time, float timeout, float update_period):
    error(error),
    kp(kp),
    ki(ki),
    kd(kd),
    ksi(ksi),
    settle_error(settle_error),
    settle_time(settle_time),
    timeout(timeout),
    update_period(update_period)
{};

float pid::calc(float error) {
    if (fabs(error) < ksi) {
        accumulated_error += error;
    }
    // Checks if the error has crossed 0, and if it has, it eliminates the integral term.
    if ((error > 0 && previous_error < 0) || (error < 0 && previous_error > 0)) { 
        accumulated_error = 0; 
    }

    output = kp * error + ki * accumulated_error + kd * (error - previous_error);

    previous_error = error;

    if (fabs(error) < settle_error) {
        time_spent_settled += 10;
    } else {
        time_spent_settled = 0;
    }

    time_spent_running += 10;

    return output;
}

bool pid::is_settled() {
    if (time_spent_running > timeout && timeout != 0) {
        return(true);
    } // If timeout does equal 0, the move will never actually time out. Setting timeout to 0 is the 
        // equivalent of setting it to infinity.
    if (time_spent_settled > settle_time){
        return(true);
    }
    return(false);
}