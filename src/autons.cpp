#include "main.h"
#include "devices.h"
#include "ladybrown.h"
#include "pros/device.hpp"
#include "pros/rtos.hpp"

void skills() {
	/* 
	Initialization:
	- Line in the middle of double stacked delrin is on the right side (from driver perspective) of tile border
	- Front of robot touching alliance stake
	*/
	const int maxSpeed = 70;

	chassis.setPose({0, 0, 180});

	chassis.moveToPoint(0, 4, 1000, {.forwards=false});
	chassis.waitUntilDone();
	lb.move(18000);
	int stime = pros::millis();
	pros::delay(200);
	while (!lb.done()) {
		if (pros::millis() - stime > 3000) {
			break;
		}
		pros::delay(20);
	}
	lb.move(0, false);
	pros::delay(2000);
	lb.off();
	// chassis.turnToHeading(120, 4000, {.maxSpeed=maxSpeed});
	chassis.moveToPoint(-5, 22, 4000, {.forwards=false, .earlyExitRange=2});
	chassis.waitUntilDone();
	mogo.extend();
	pros::delay(500);
	// chassis.turnToHeading(0, 4000, {.maxSpeed=maxSpeed});
	// chassis.turnToPoint(-21, 59, 3000, {.maxSpeed=maxSpeed});
	// chassis.waitUntilDone();
	intake.move_velocity(600);
	chassis.moveToPoint(-19, 59, 3000);
	// chassis.turnToPoint(-41, 108.5, 1400);
	chassis.moveToPose(-42, 108.5, 0, 5000);
	// chassis.turnToPoint(-58, 68, 4000);
	chassis.moveToPose(-60, 68, 270, 4000);
	chassis.waitUntil(7);
	lb.move(4100);
	while (intake.get_actual_velocity() > 50) {
		pros::delay(50);
	}
	intake.move_velocity(0);
	chassis.moveToPoint((chassis.getPose().x-6.0), chassis.getPose().y, 4000);
	chassis.waitUntil(2);
	lb.move(18000, true);
	lb.move(0, true);
	lb.off();
}

void twelveInch() {
	chassis.setPose({0, 0, 0});
	chassis.moveToPoint(0, 12, 4000);
}

void test() {
	chassis.setPose({-48, 0, 0});
	chassis.moveToPoint(12, 12, 4000);
}