#include "main.h"
#include "devices.h"
#include "ladybrown.h"
#include "pros/device.hpp"
#include "pros/rtos.hpp"

void skills() {

// 10 degrees, kp = 7, kd = 20
// 30 degrees, kp = 5, kd = 20 
		

	chassis.setPose(0, 0, 120);
	lb.lb_pid.set_consts(35.0, 0.0, 50.0);
	lb.move(330);
	pros::delay(700);
	lb.lb_pid.set_consts(100.0, 0.0, 50.0);

	// First Mogo
	chassis.moveToPoint(-9, 5.5, 1000, {.forwards=false, .maxSpeed=80});
	chassis.waitUntilDone();
	mogo.extend();
	// intake.move_velocity(12000);
	lb.move(-30);
	pros::delay(300);

	// First ring
	chassis.angularPID.kP = 2;
	// chassis.turnToHeading(-23, 1000);
	chassis.turnToPoint(-28, 32.85, 1000);
	chassis.moveToPoint(-28, 32.85, 1000);

	// // Second ring
	chassis.angularPID.kP = 6;
	// chassis.turnToHeading(-44, 1000);
	chassis.turnToPoint(-53, 55.5, 1000);
	chassis.moveToPoint(-53, 55.5, 1000);
		
	chassis.turnToPoint(-63.4, 77.6, 1000);
	// chassis.turnToHeading(-25, 1000);
	// lb.move(270);
	chassis.moveToPoint(-63.4, 77.6, 1000);
	// intake.move_velocity(0);


	chassis.angularPID.kP = 8;
	// chassis.turnToHeading(-18, 1000);
	chassis.turnToPoint(-54, 55.5, 1000, {.forwards = false});
	chassis.moveToPoint(-54, 55.5, 1000, {.forwards = false});

	chassis.angularPID.kP = 2.7;
	// chassis.turnToHeading(-104, 1000);
	chassis.turnToPoint(-70.5, 45.85, 1000);

	// intake.move_velocity(12000);
	chassis.moveToPoint(-70.5, 43, 1000, {.maxSpeed = 60});
	left_motors.move_velocity(12000);
	right_motors.move_velocity(12000);
	pros::delay(1000);
	left_motors.move_velocity(0);
	right_motors.move_velocity(0);
	// intake.move_velocity(0);
	lb.move(190);


	pros::delay(2000);



	chassis.angularPID.kP = 3;

	// chassis.setPose(0,0,0);



	// Three rings in a row

	chassis.moveToPoint(-58.5, 44.6, 1000, {.forwards=false});

	// chassis.turnToPoint(-91.75, -7, 1000);
	// chassis.moveToPoint(-91.75, -7, 1000);
	// chassis.moveToPoint(-46, 1, 1000, {.forwards = false});
	// chassis.turnToPoint(-46, 13, 1000);
	// chassis.moveToPoint(-46, 13, 1000);

	
	// lb.move(200);
	// chassis.setPose(-72, 72, -90);
	// pros::delay(500);






	// Three rings in a row
	// chassis.moveToPoint(-56.65, 49.3, 1000, {.forwards=false});
	// chassis.turnToHeading(-186, 1000);
	// chassis.moveToPoint(-53.9, -7.94, 1000);

	// chassis.setPose(0, 0, -90);

	// 

	// chassis.turnToPoint(-20, 34.8, 1000);
	// chassis.moveToPoint(-20, 34.8, 1000);
	// lb.off();
	// chassis.turnToPoint(-40.5, 53.3, 1000);
	// chassis.moveToPoint(-40.5, 53.3, 1000, {.minSpeed=40, .earlyExitRange=2});
	// chassis.turnToPoint(-53, 79.6, 1000);
	// chassis.moveToPoint(-53, 79.6, 1000);
	// pros::delay(500);
	// chassis.moveToPoint(-41.9, 53.7, 1000, {.forwards=false});
	// chassis.turnToPoint(-63, 50, 1000);
	// lb.move(24);
	// chassis.moveToPoint(-63, 50, 1000);
	// chassis.waitUntilDone();
	// pros::delay(1000);
	// intake.move_velocity(0);
	// lb.move(210);
	// pros::delay(700);
	// lb.move(-30);
	// chassis.moveToPoint(-46.2, 50.3, 1000, {.forwards=false});
	// chassis.turnToPoint(-47.1, 25.7, 1000);
	// lb.off();
	// intake.move_voltage(12000);
	// chassis.moveToPoint(-47.1, 25.7, 1000);
	// chassis.turnToPoint(-42.6, -7.3, 1000);
	// chassis.moveToPoint(-42.6, -7.3, 1000);
	// chassis.turnToPoint(-54.4, 0.4, 1000);
	// chassis.moveToPoint(-54.4, 0.4, 1000);
	// chassis.turnToPoint(-52.45, -11.85, 1000, {.forwards=false});
	// chassis.moveToPoint(-52.45, -11.85, 1000, {.forwards=false});


	

}

void twelveInch() {
	chassis.setPose({0, 0, 0});
	chassis.moveToPoint(0, 12, 4000);
}

void test() {
	chassis.setPose({-48, 0, 0});
	chassis.moveToPoint(12, 12, 4000);
}