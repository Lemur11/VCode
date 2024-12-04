#include "main.h"
#include "pid.h"
void move(float target, PID &left_pid, PID &right_pid, int units=DEGREES, int timeout=10000);
void turn(float degrees, PID &turn_pid, int timeout=10000);