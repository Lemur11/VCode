#include "ladybrown.h"
#include <cmath>

void LadyBrown::initialize() {
    update_task = std::make_unique<pros::Task>([this](){
        while(true) {
            update();
            pros::delay(10);
        }
    });
    lb_pid.set_prev(0);
}

void LadyBrown::update() {
    if (fabs(this->target - lady_brown.get_position()) < pos_deadzone && lb_pid.get_deriv() < vel_deadzone) {
        at_target = true;
    }
    else {
        at_target = false;
    }
    if (on) {
        double reading = lady_brown.get_position();
        printf("reading: %f\n", reading);
        float vol = lb_pid.cycle(target, reading);
        printf("Vol: %f\n", vol);
        float angle_rad = (114.0f - reading) * (M_PI / 180.0f);
        // printf("Angle rad: %f\n", angle_rad);
        // printf("FF: %f\n", ff_K * sin(angle_rad));
        lady_brown.move_voltage(vol + ff_K * sin(angle_rad));
    }
}

void LadyBrown::move(int target, bool blocking) {
    on = true;
    lb_pid.reset_sum();
    lb_pid.set_prev((target - lady_brown.get_position()));
    printf("Tar %d\n", target);
    this->target = target;
    if (blocking) {
        while (true) {
            if (fabs(this->target - lady_brown.get_position()) < pos_deadzone && lb_pid.get_deriv() < vel_deadzone) {
                break;
            }
            pros::delay(20);
        }
    }
}

void LadyBrown::off() {
    on = false;
    lady_brown.move_voltage(0);
}

bool LadyBrown::done() {
    return at_target;
}

bool LadyBrown::isOn() {
    return on;
}



