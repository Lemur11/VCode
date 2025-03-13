#include "main.h"
#include "devices.h"
#include "ladybrown.h"
#include "pros/device.hpp"
#include "pros/rtos.hpp"

void skills() {
	chassis.setPose(0, 0, 0);
	

	// chassis.angularPID.kD = 23.5; // For large turns
	chassis.moveToPoint(0, -10, 1000, {.forwards = false});
	chassis.turnToHeading(-90, 1000);
	// chassis.turnToPoint(10, -10, 1000, {.forwards = false});
	// // chassis.angularPID.kD = 10; // For small turns

	// // lb.move(800);
	// // pros::delay(700);

	// chassis.moveToPoint(0, -4.4, 4000, {.forwards = false});
	// // pros::delay(300);
	// // lady_brown.move_voltage(-12000); // Fix this
	// // pros::delay(600);

	// // 9. 1
	// chassis.turnToPoint(13.2, -9.1, 4000, {.forwards = false});
	// chassis.moveToPoint(13.2, -9.1, 4000, {.forwards = false, .earlyExitRange=7}); 
	// mogo.extend();
	// pros::delay(500);
	

}

void twelveInch() {
	chassis.setPose({0, 0, 0});
	chassis.moveToPoint(0, 12, 4000);
}

void test() {
	chassis.setPose({-48, 0, 0});
	chassis.moveToPoint(12, 12, 4000);
}