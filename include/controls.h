#include "vex.h"

void ctrlScraper();
void ctrlDescorer();
void ctrlKillSwitch();

void arcade();
void arcade(int forward, int turn, bool enableTurnCurve, float deadbandWidth);
void moveIntake(int inlv, int inuv);

void outtake();

// void lowGoal();
void basket();
void highGoal();
void longGoal();

    
// public:
//   float error = 0;
//   float kp = 0;
//   float ki = 0;
//   float kd = 0;
//   float starti = 0;
//   float settle_error = 0;
//   float settle_time = 0;
//   float timeout = 0;
//   float accumulated_error = 0;
//   float previous_error = 0;
//   float output = 0;
//   float time_spent_settled = 0;
//   float time_spent_running = 0;
//   float update_period = 10;

//   PID(float error, float kp, float ki, float kd, float starti);

//   PID(float error, float kp, float ki, float kd, float starti, float settle_error, float settle_time, float timeout);

//   PID(float error, float kp, float ki, float kd, float starti, float settle_error, float settle_time, float timeout, float update_period);

//   float compute(float error);

//   bool is_settled();

// class Intake {
// public:

//     void move(float inlv, float inuv, float inbv);

//     class Lower {
//     private:
//         motor& inl;
//     public:
//         Lower(motor& motorRef) : inl(motorRef) {}
//         void move(int volts);
//     };

//     class Upper {
//     private:
//         motor& inu;
//     public:
//         Upper(motor& motorRef) : inu(motorRef) {}
//         void move(int volts);
//     };

//     class Back {
//     private:
//         motor& inb;
//     public:
//         Back(motor& motorRef) : inb(motorRef) {}
//         void move(int volts);
//     };

//     Lower l;
//     Upper u;
//     Back b;

// };