#include "main.h"
#include "devices.h"
#include "ladybrown.h"
#include "pros/device.hpp"
#include "pros/rtos.hpp"

void skills() {
	chassis.setPose(0, 0, 120);
	lb.lb_pid.set_consts(35.0, 0.0, 50.0);
	lb.move(330);
	pros::delay(700);
	lb.lb_pid.set_consts(100.0, 0.0, 50.0);
	chassis.moveToPoint(-9, 5.5, 1000, {.forwards=false, .maxSpeed=80});
	// chassis.turnToHeading(chassis.getPose().theta + 5, 1000);
	chassis.waitUntilDone();
	mogo.extend();
	intake.move_velocity(12000);
	lb.move(-30);
	pros::delay(300);
	chassis.turnToPoint(-20, 34.8, 1000);
	chassis.moveToPoint(-20, 34.8, 1000);
	lb.off();
	chassis.turnToPoint(-40.5, 53.3, 1000);
	chassis.moveToPoint(-40.5, 53.3, 1000, {.minSpeed=40, .earlyExitRange=2});
	chassis.turnToPoint(-53, 79.6, 1000);
	chassis.moveToPoint(-53, 79.6, 1000);
	pros::delay(500);
	chassis.moveToPoint(-41.9, 53.7, 1000, {.forwards=false});
	chassis.turnToPoint(-63, 50, 1000);
	lb.move(24);
	chassis.moveToPoint(-63, 50, 1000);
	chassis.waitUntilDone();
	pros::delay(1000);
	intake.move_velocity(0);
	lb.move(210);
	pros::delay(700);
	lb.move(-30);
	chassis.moveToPoint(-46.2, 50.3, 1000, {.forwards=false});
	chassis.turnToPoint(-47.1, 25.7, 1000);
	lb.off();
	intake.move_voltage(12000);
	chassis.moveToPoint(-47.1, 25.7, 1000);
	chassis.turnToPoint(-42.6, -7.3, 1000);
	chassis.moveToPoint(-42.6, -7.3, 1000);
	chassis.turnToPoint(-54.4, 0.4, 1000);
	chassis.moveToPoint(-54.4, 0.4, 1000);
	chassis.turnToPoint(-52.45, -11.85, 1000, {.forwards=false});
	chassis.moveToPoint(-52.45, -11.85, 1000, {.forwards=false});


	

}

void twelveInch() {
	chassis.setPose({0, 0, 0});
	chassis.moveToPoint(0, 12, 4000);
}

void test() {
	chassis.setPose({-48, 0, 0});
	chassis.moveToPoint(12, 12, 4000);
}