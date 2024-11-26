#include "main.h"
#include "pid.h"
#include "utils.h"
#include <algorithm>

PID::PID(float p, float i, float d) {
    kp = p;
    kd = d;
    ki = i;
};

float PID::cycle(float reference, float reading) {
    error = reference - reading;
    // if (sgn(error) != sgn(prev_error)) {
    //     err_sum = error;
    // }
    // else {
    //     err_sum += error;
    // }
    err_sum += error;
    err_sum = std::clamp(err_sum, -30000.0f, 45000.0f);
    delta = error - prev_error;
    prev_error = error;

    vol = kp * error + err_sum * ki + delta * kd;
    vol = std::clamp(vol, -12000.0f, 12000.0f);
    // printf("%f\n", err_sum);
    printf("%f\n", reading);
    // printf("%f\n", error);
    return vol;
}

void PID::set_prev(float val) {
    prev_error = val;
}

void PID::reset_sum() {
    err_sum = 0;
}

float PID::get_prev() {
    return prev_error;
}

float PID::get_deriv() {
    return delta;
}