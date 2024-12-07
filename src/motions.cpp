#include "main.h"
#include "motions.h"
#include "devices.h"
#include "pros/rtos.hpp"
#include "utils.h"


void move(float target, PID &left_pid, PID &right_pid, int units, int timeout, int exit_dist) {
    target = target * units;

	// reset motor encoder readings
	left_motor.tare_position();
	right_motor.tare_position();

	// debug
	printf("Target: %f\n", target); 

	// get initial readings and set prev err
	float l_reading = left_motor.get_position();
	float r_reading = right_motor.get_position();
	left_pid.set_prev(target - l_reading);
	right_pid.set_prev(target - r_reading);
	
	// loop
	int stime = pros::millis();
	while (true) {
		// exit condition
		if (exit_dist != 0) {
			if (fabs((l_reading + r_reading)/2 - target) < exit_dist) {
				break;
			}
		}

		if (pros::millis() - stime > timeout) {
			break;
		}

		if (fabs((l_reading + r_reading)/2 - target) < 20 && fabs(left_pid.get_deriv()) < 0.2 && fabs(right_pid.get_deriv()) < 0.2) {
			break;
		}
		// get readings
		l_reading = left_motor.get_position();
		r_reading = right_motor.get_position();
		
		//debug
		pros::lcd::print(1, "Left: %f\nRight: %f", l_reading, r_reading);

		// pid calc and move
		left_motors.move_voltage(left_pid.cycle(target, l_reading));
		right_motors.move_voltage(right_pid.cycle(target, r_reading));

		pros::delay(20);
	};
	// stop motors
	left_motors.move_voltage(0);
	right_motors.move_voltage(0);
}


void turn(float degrees, PID &turn_pid, int timeout) {
	printf("Turning\n");
	float turn_factor = 1;
	
	// initial readings
	float reading = (float)imu.get_heading();
	float target = target_cal(reading + degrees);
	printf("Target: %f\n", target);
	float err = wrap(target, reading);
	
	// set pid prev error to prevent massive deriv at start
	turn_pid.set_prev(-err);

	float turn_vol;

	int stime = pros::millis();
	while (true) {
		// loop end control
		if (pros::millis() - stime > timeout) {
			break;
		}

		if (fabs(err) < 4 && fabs(turn_pid.get_deriv()) < 0.5) {
			break;
		}
		// get heading
		reading = (float)imu.get_heading();
		pros::lcd::print(1, "HEAD: %f", reading);

		// if dc imu stop turning
		if (!imu.is_installed()) {
			pros::lcd::print(5, "IMU ERR");
			break;
		}
		// pid calculation
		err = wrap(target, reading);
		turn_vol = turn_pid.cycle(0, err);


		// move motors
		left_motors.move_voltage(-turn_vol * turn_factor);
		right_motors.move_voltage(turn_vol * turn_factor);

		pros::delay(60);
	}
	// stop motors
	left_motors.move_velocity(0);
	right_motors.move_velocity(0);
}

void turn_to_heading(float degrees, PID &turn_pid, int timeout) {
	printf("Turning\n");
	float turn_factor = 1;
	
	// initial readings
	float reading = (float)imu.get_heading();
	float target = degrees;
	printf("Target: %f\n", target);
	float err = wrap(target, reading);
	
	// set pid prev error to prevent massive deriv at start
	turn_pid.set_prev(-err);

	float turn_vol;

	int stime = pros::millis();
	while (true) {
		// loop end control
		if (pros::millis() - stime > timeout) {
			break;
		}

		if (fabs(err) < 4 && fabs(turn_pid.get_deriv()) < 0.5) {
			break;
		}
		// get heading
		reading = (float)imu.get_heading();
		pros::lcd::print(1, "HEAD: %f", reading);

		// if dc imu stop turning
		if (!imu.is_installed()) {
			pros::lcd::print(5, "IMU ERR");
			break;
		}
		// pid calculation
		err = wrap(target, reading);
		turn_vol = turn_pid.cycle(0, err);


		// move motors
		left_motors.move_voltage(-turn_vol * turn_factor);
		right_motors.move_voltage(turn_vol * turn_factor);

		pros::delay(60);
	}
	// stop motors
	left_motors.move_velocity(0);
	right_motors.move_velocity(0);
}