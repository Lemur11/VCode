#include "main.h"
#include "devices.h"
#include "motions.h"
#include "ladybrown.h"

// move pids
PID left_pid = PID(25, 0, 90);
PID right_pid = PID(25, 0, 90);

// turn pid
PID turn_pid = PID(100, 2, 200, 100000.0f, true);

LadyBrown& lb = LadyBrown::getInstance();

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
	turn(-120, turn_pid, 1000);
	// raise lb
	lb.move(6000);
	move(980, left_pid, right_pid);
	turn_pid.set_consts(350.0, 2.0, 200.0);
	turn(46, turn_pid);
	move(300, left_pid, right_pid, DEGREES, 1000);

	// wait for ring to get stuck
	while (!intake.is_over_current()) {
		pros::delay(20);
	}
	pros::delay(200);
	// stop intake
	intake.move_voltage(0);
	// score
	lb.move(17000, true);
	lb.move(0);
	intake.move_voltage(12000);
	move(-450, left_pid, right_pid);
	turn(-85, turn_pid);
	move(1700, left_pid, right_pid);
	move(900, left_pid, right_pid);
}