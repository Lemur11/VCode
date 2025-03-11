#include "main.h"
#include "devices.h"
#include "ladybrown.h"
#include "pros/device.hpp"
#include "pros/rtos.hpp"

void skills() {
	chassis.setPose(0, 0, 0);
	// 

	lb.move(800);
	pros::delay(700);

	chassis.moveToPoint(0, -6.5, 4000);
	pros::delay(1000);
	lady_brown.move_voltage(-12000); // Fix this
	pros::delay(600);

	chassis.turnToHeading(270, 4000);
	// chassis.turnToPoint(16, -6.5, 4000, {.forwards = false});

	pros::delay(1000);
	// TUNE THIS POINT
	chassis.moveToPoint(16, -6.5, 4000, {.forwards = false}); 
	pros::delay(1000);

	mogo.extend();
	

}

void twelveInch() {
	chassis.setPose({0, 0, 0});
	chassis.moveToPoint(0, 12, 4000);
}

void test() {
	chassis.setPose({-48, 0, 0});
	chassis.moveToPoint(12, 12, 4000);
}