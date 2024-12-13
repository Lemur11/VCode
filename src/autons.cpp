#include "main.h"
#include "devices.h"
#include "motions.h"
#include "ladybrown.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include <cstdint>

// move pids
PID left_pid = PID(25, 0, 90);
PID right_pid = PID(25, 0, 90);

// turn pid
PID turn_pid = PID(100, 2, 200, 100000.0f, true);

void skills() {
    turn_pid.set_consts(250.0, 2.0, 200.0);
	turn(20, turn_pid, 1000);
	move(-450, left_pid, right_pid);
	// mogo get
	mogo.extend();
	pros::delay(500);
	turn_pid.set_consts(100.0, 2.0, 200.0);
	turn(231, turn_pid, 1500);
	intake.move_velocity(600);
	move(1200, left_pid, right_pid);
	turn_pid.set_consts(350.0, 2.0, 200.0);
	turn(-15, turn_pid, 1000);
	move(1000, left_pid, right_pid);
	turn(16, turn_pid, 1000);
	move(1450, left_pid, right_pid);
	turn_pid.set_consts(100.0, 2.0, 200.0);
	turn(-123, turn_pid, 1000);
	// raise lb
	move(950, left_pid, right_pid);
    lb.move(6000);
	turn_pid.set_consts(350.0, 2.0, 200.0);
	turn(46, turn_pid);
	// move(300, left_pid, right_pid, DEGREES, 1000);

	// wait for ring to get stuck
	while (!intake.is_over_current()) {
		pros::delay(20);
	}
	pros::delay(200);
	// stop intake
	intake.move_voltage(0);
	// score
    left_motors.move_voltage(5000);
    right_motors.move_voltage(5000);
	lb.move(17000, false);
    int stime = pros::millis();
    pros::delay(100);
    while (!lb.done()) {
        if ((pros::millis() - stime) > 2000) {
            break;
        }
        pros::delay(20);
    }
    left_motors.move_voltage(0);
    right_motors.move_voltage(0);
	lb.move(0);
	intake.move_voltage(12000);
	move(-550, left_pid, right_pid);
	turn(-80, turn_pid);
	move(1500, left_pid, right_pid);
	move(900, left_pid, right_pid);
    move(600, left_pid, right_pid, DEGREES, 1500);
    move(-810, left_pid, right_pid);
    intake.move_voltage(0);
    turn(90, turn_pid);
    move(500, left_pid, right_pid);
    turn(110, turn_pid);
    mogo.retract();
    move(-470, left_pid, right_pid);
    move(470, left_pid, right_pid);
    turn_to_heading(0, turn_pid);
}

void red_rush() {
    move(-2150, left_pid, right_pid, DEGREES, 100000, 500);
	while(mogod.get() > 190) {
		if (fabs((left_motor.get_position() + right_motor.get_position())/2) > 2100) {
			break;
		}
		pros::delay(20);
	}
	// left_motors.move_voltage(5000);
	// right_motors.move_voltage(5000);
	left_motors.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
	right_motors.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
	mogo.extend();
	left_motors.move_velocity(0);
	right_motors.move_velocity(0);
	left_motors.set_brake_mode_all(pros::E_MOTOR_BRAKE_COAST);
	right_motors.set_brake_mode_all(pros::E_MOTOR_BRAKE_COAST);
	// pros::delay(200);
	pros::delay(500);
    move(1000, left_pid, right_pid);
	intake.move_voltage(12000);
	pros::delay(5000);
	turn_to_heading(270, turn_pid);
	move(500, left_pid, right_pid, DEGREES, 1000);
	pros::delay(4000);
	turn_pid.set_consts(400.0, 2.0, 200.0);
	turn(40, turn_pid, 1000);
	doinker.extend();
	move(1600, left_pid, turn_pid);
	turn_pid.set_consts(400.0, 2.0, 200.0);
	turn(-114, turn_pid, 1000);
	move(150, left_pid, right_pid);
	turn_pid.set_consts(400.0, 2.0, 200.0);
	turn_to_heading(90, turn_pid, 700);
	move(-500, left_pid, right_pid, DEGREES, 1000);
	mogo.retract();
	move(385, left_pid, right_pid);
	turn_pid.set_consts(100.0, 2.0, 200.0);
	turn_to_heading(270, turn_pid);
	move(-1100, left_pid, right_pid);
	mogo.extend();
	pros::delay(4000);

}

void red_rush2() {
	move(-1500, left_pid, right_pid, DEGREES, 1000);
	turn_pid.set_consts(400.0, 2.0, 200.0);
	turn_to_heading(-27, turn_pid);
	left_motor.tare_position();
	right_motor.tare_position();
	left_motors.move_velocity(-100);
	right_motors.move_velocity(-100);
	while (mogod.get() > 190) {
		if (fabs((left_motor.get_position() + right_motor.get_position())/2) > 1000) {
			break;
		}
		pros::delay(20);
	}
	left_motors.move_velocity(0);
	right_motors.move_velocity(0);
	mogo.extend();
	turn_to_heading(10, turn_pid);
	if (mogod.get() > 180) {
		//
	}
	else {
	intake.move_velocity(600);
	move(360, left_pid, right_pid);
	turn_to_heading(340, turn_pid);
	while (intakeD.get() > 40) {
		pros::delay(20);
	}
	pros::delay(1000);
	move(1850, left_pid, right_pid, DEGREES, 700);
	doinker.extend();
	turn(-30, turn_pid, 500);
	move(500, left_pid, right_pid, DEGREES, 500);
	turn_pid.set_consts(200.0, 2.0, 200.0);
	turn(-100, turn_pid, 1000);
	doinker.retract();
	turn_to_heading(130, turn_pid, 1200);
	mogo.retract();
	move(-500, left_pid, right_pid, DEGREES, 600);
	move(1000, left_pid, right_pid);
	turn(180, turn_pid, 1000);
	move(-650, left_pid, right_pid);
	left_motor.tare_position();
	right_motor.tare_position();
	left_motors.move_velocity(-100);
	right_motors.move_velocity(-100);
	while (mogod.get() > 180) {
		pros::delay(20);
	}
	mogo.extend();
	left_motors.move_velocity(0);
	right_motors.move_velocity(0);
	float moved = left_motor.get_position();
	printf("Moved %f\n", moved);
	move(-moved, left_pid, right_pid);
	turn(97, turn_pid);
	left_motors.move_voltage(400);
	right_motors.move_voltage(400);
	while (intakeD.get() > 40) {
		pros::delay(20);
	}
	pros::delay(100);
	left_motors.move_velocity(0);
	right_motors.move_velocity(0);
	intake.move_velocity(0);
	// move(1800, left_pid, right_pid);
	}

}


void red_awp() {
	move(300, left_pid, right_pid, DEGREES, 1000);
	lb.move(18000);
	int stime = pros::millis();
	while (!lb.done()) {
		if (pros::millis() - stime > 3000) {
			break;
		}
		pros::delay(20);
	}
	lb.move(0);
	move(-1220, left_pid, right_pid);
	turn_pid.set_consts(300.0, 2.0, 200.0);
	turn(48, turn_pid, 1000);
	move(-1000, left_pid, right_pid);
	mogo.extend();
	move(500, left_pid, right_pid);
	pros::delay(500);
	turn_pid.set_consts(200.0, 2.0, 200.0);
	turn(130, turn_pid, 1500);
	intake.move_velocity(600);
	move(1460, left_pid, right_pid, DEGREES, 2000);
	pros::delay(1500);
	move(-1020, left_pid, right_pid);
	turn(-48, turn_pid, 1000);
	move(1000, left_pid, right_pid);
	pros::delay(700);
	turn(170, turn_pid, 1500);
	move(2000, left_pid, right_pid);
}

void blue_awp() {
	move(300, left_pid, right_pid, DEGREES, 1000);
	lb.move(18000);
	int stime = pros::millis();
	while (!lb.done()) {
		if (pros::millis() - stime > 3000) {
			break;
		}
		pros::delay(20);
	}
	lb.move(0);
	move(-1170, left_pid, right_pid);
	turn_pid.set_consts(300.0, 2.0, 200.0);
	turn_to_heading(-57, turn_pid, 1000);
	move(-1200, left_pid, right_pid);
	mogo.extend();
	pros::delay(500);
	move(700, left_pid, right_pid);
	turn_pid.set_consts(200.0, 2.0, 200.0);
	turn(-145, turn_pid, 1500);
	intake.move_voltage(12000);
	move(1460, left_pid, right_pid, DEGREES, 2000);
	pros::delay(1500);
	move(-1020, left_pid, right_pid);
	turn(48, turn_pid, 1000);
	move(1000, left_pid, right_pid);
	pros::delay(700);
	turn(-170, turn_pid, 1500);
	move(2000, left_pid, right_pid);
}

void blue_2ring() {
	left_pid.set_consts(15, 0, 90);
	right_pid.set_consts(15, 0, 90);
	move(-1600, left_pid, right_pid, DEGREES, 4000, 300);
	mogo.extend();
	pros::delay(500);
	intake.move_voltage(12000);
	turn_to_heading(300, turn_pid, 1000);
	move(1230, left_pid, right_pid, DEGREES, 2000);
	pros::delay(1000);
	turn(-170, turn_pid, 1500);
	move(2000, left_pid, right_pid);
}

void red_mogo() {
	left_pid.set_consts(15, 0, 90);
	right_pid.set_consts(15, 0, 90);
	move(-1600, left_pid, right_pid, DEGREES, 4000, 300);
	pros::delay(500);
	mogo.extend();
	pros::delay(700);
	intake.move_voltage(12000);
	turn_to_heading(60, turn_pid, 1000);
	move(1230, left_pid, right_pid, DEGREES, 2000);
	while (intakeD.get() > 40) {
		pros::delay(20);
	}
	pros::delay(400);
	intake.move_voltage(0);
	turn(-70, turn_pid);
}

void test() {
	move(48, left_pid, right_pid, INCHES);
}