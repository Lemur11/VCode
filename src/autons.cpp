#include "main.h"
#include "devices.h"
#include "ladybrown.h"
#include "pros/device.hpp"
#include "pros/rtos.hpp"

void skills() {
	chassis.setPose(0, 0, 0);
	intake.move_velocity(360);
	pros::delay(500);
	intake.move_velocity(0);
	chassis.moveToPoint(0, 10, 2000);
	chassis.turnToHeading(90, 1000);
	chassis.moveToPoint(-24, 8, 3000, {.forwards=false, .maxSpeed=100, .earlyExitRange=4});
	while (chassis.getPose().x > -21) {
		pros::delay(20);
	}
	mogo.extend();
	pros::delay(500);
	intake.move_velocity(600);
	chassis.turnToPoint(-42.3, 4.5, 1000);
	chassis.moveToPoint(-42.3, 4.5, 2000);
	chassis.moveToPoint(-54, 4, 2000);
	chassis.turnToHeading(141, 1000);
	chassis.moveToPoint(-42.7, -5.7, 2000);
	pros::delay(700);
	chassis.turnToHeading(38.3, 1000);
	chassis.moveToPoint(-46.4, -8.4, 2000, {.forwards=false});
	mogo.retract();
	pros::delay(500);
	chassis.moveToPoint(-39, 2.1, 2000);
	chassis.turnToPoint(-48.2, 56, 1000);
	chassis.moveToPoint(-48.2, 56, 2000, {.maxSpeed=100});
	lb.move(6400);
	chassis.turnToPoint(-67, 53, 1000);
	chassis.moveToPoint(-67, 53, 2000);
	lb.move(13000);
	pros::delay(800);
	lb.move(0);
}

void twelveInch() {
	chassis.setPose({0, 0, 0});
	chassis.moveToPoint(0, 12, 4000);
}

void test() {
	chassis.setPose({-48, 0, 0});
	chassis.moveToPoint(12, 12, 4000);
}