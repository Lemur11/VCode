#include "ladybrown.h"
#include <cmath>

LadyBrown::LadyBrown() : 
    lb_pid(3.0, 0.02, 3.0) 
    {
    update_task = std::make_unique<pros::Task>([this](){
        while(true) {
            update();
            pros::delay(10);
        }
    });
    lb_pid.set_prev(0);
}

void LadyBrown::update() {
    if (fabs(this->target - rot.get_position()) < pos_deadzone && lb_pid.get_deriv() < vel_deadzone) {
        at_target = true;
    }
    else {
        at_target = false;
    }
    if (on) {
        int reading = rot.get_position();
        lady_brown.move_voltage(lb_pid.cycle(target, reading));
    }
}

void LadyBrown::move(int target, bool blocking) {
    on = true;
    lb_pid.reset_sum();
    lb_pid.set_prev((target - rot.get_position()));
    printf("Tar %d\n", target);
    this->target = target;
    if (blocking) {
        while (true) {
            if (fabs(this->target - rot.get_position()) < pos_deadzone && lb_pid.get_deriv() < vel_deadzone) {
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


