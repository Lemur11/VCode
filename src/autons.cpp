#include "devices.h"
#include "ladybrown.h"
#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/device.hpp"
#include "pros/motors.h"
#include "pros/rtos.hpp"

void skills() {
	// antiJam.store(true);

  // 10 degrees, kp = 7, kd = 20
  // 30 degrees, kp = 5, kd = 20
  antiJam = true;
  chassis.setPose(0, 0, 120);
  lb.lb_pid.set_consts(35.0, 0.0, 50.0);
  lb.move(21000);
  pros::delay(700);
  lb.lb_pid.set_consts(100.0, 0.0, 50.0);

  // First Mogo
  chassis.moveToPoint(-9, 5.5, 1000, {.forwards = false, .maxSpeed = 80});
  chassis.waitUntilDone();
  mogo.extend();
  intake.move_velocity(12000);
  lb.move(-2000);
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
  antiJam = false;
  lb.move(25);
  chassis.moveToPoint(-63.4, 77.6, 1000);

  chassis.angularPID.kP = 8;
  // chassis.turnToHeading(-18, 1000);
  chassis.turnToPoint(-54, 55.5, 1000, {.forwards = false});
  chassis.moveToPoint(-54, 55.5, 1000, {.forwards = false});

  chassis.angularPID.kP = 2.7;
  // chassis.turnToHeading(-104, 1000);
  chassis.turnToPoint(-70.5, 45.85, 1000);
  lb.move(80);
  chassis.moveToPoint(-70.5, 45.85, 1000, {.maxSpeed = 60});
  intake.move_velocity(0);
  chassis.waitUntilDone();
  pros::delay(700);
  lb.lb_pid.set_consts(300.0, 0.0, 50.0);
  lb.move(210);
  pros::delay(1000);
  lb.lb_pid.set_consts(100.0, 0.0, 50.0);
  lb.move(25);
  intake.move_velocity(12000);
  pros::delay(1500);
  lb.lb_pid.set_consts(300.0, 0.0, 50.0);
  intake.move_velocity(0);
  lb.move(210);
  pros::delay(1000);
  lb.lb_pid.set_consts(100.0, 0.0, 50.0);
  lb.move(-30);
  chassis.turnToPoint(-55.9, 47.1, 1000, {.forwards = false});
  intake.move_velocity(12000);
  chassis.moveToPoint(-55.9, 47.1, 1000, {.forwards = false});
  lb.off();
//   antiJam.store(true);
  antiJam = true;
  chassis.turnToPoint(-50, 21.6, 1000);
  chassis.moveToPoint(-50, 21.6, 1000);
  chassis.turnToPoint(-45, -14.5, 1000);
  chassis.moveToPoint(-45, -14.5, 3000, {.maxSpeed = 30});
  chassis.turnToPoint(-59.59, -5.25, 1000);
  chassis.moveToPoint(-59.59, -5.25, 1000);
  chassis.turnToPoint(-58, -24, 1000, {.forwards = false});
  chassis.moveToPoint(-58, -24, 1000, {.forwards = false});
  chassis.waitUntilDone();
  intake.move_velocity(0);
  mogo.retract();
  pros::delay(300);
  chassis.moveToPoint(-58, -15.65, 1000);

  left_motors.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  right_motors.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

  chassis.turnToPoint(32, -7.7, 1000, {.forwards = false, .maxSpeed = 80});
  chassis.moveToPoint(32, -7.7, 2200, {.forwards = false, .maxSpeed = 80});
  chassis.moveToPoint(35, -7.7, 1000, {.forwards = false, .maxSpeed = 60});
  chassis.waitUntilDone();
  mogo.extend();
  pros::delay(300);

  left_motors.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  right_motors.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);


  // ring
  intake.move_velocity(12000);
  chassis.turnToPoint(23.5, 16.6, 1000);
  chassis.moveToPoint(23.5, 16.6, 1000);
  chassis.turnToPoint(44.5, 22, 1000);
  chassis.moveToPoint(44.5, 22, 1000);
  chassis.turnToPoint(52, -7.3, 2000, {.maxSpeed = 60});
  chassis.moveToPoint(52, -7.3, 2000, {.maxSpeed = 60});

  chassis.turnToPoint(61.43, 7.4, 1000);
  chassis.moveToPoint(61.43, 7.4, 1000);
  chassis.waitUntilDone();

  pros::delay(150);
  intake.move_velocity(0);
  chassis.turnToPoint(65.7, 0, 1000, {.forwards=false});
  chassis.moveToPoint(65.7, 0, 1000, {.forwards=false});
  chassis.waitUntilDone();
  mogo.retract();
  pros::delay(300);


  // Second wallstake
  chassis.turnToPoint(27.2, 35, 2000);
  chassis.moveToPoint(27.2, 35, 2000, {.maxSpeed = 80});

  antiJam = false;
  lb.move(25);
  // 31.7, 83.8
  chassis.turnToPoint(34.5, 85.5, 2000);
  chassis.moveToPoint(34.5, 85.5, 2000, {.maxSpeed = 80});
  chassis.waitUntilDone();
  intake.move_velocity(0);
  lb.move(80);
  pros::delay(700);

  chassis.turnToPoint(36.2, 56.9, 1000, {.forwards=false});
  chassis.moveToPoint(36.2, 56.9, 1000, {.forwards=false});

  chassis.turnToPoint(59.9, 58.7, 1000);
  chassis.moveToPoint(59.9, 58.7, 1000);

  lb.lb_pid.set_consts(300.0, 0.0, 50.0);
  lb.move(210);
  pros::delay(2000);
  lb.lb_pid.set_consts(100.0, 0.0, 50.0);
  lb.move(25);
  intake.move_velocity(12000);
  pros::delay(2000);
  lb.lb_pid.set_consts(300.0, 0.0, 50.0);
  intake.move_velocity(0);
  lb.move(210);
  pros::delay(2000);
  lb.lb_pid.set_consts(100.0, 0.0, 50.0);
  lb.move(-30);
  lb.off();

  antiJam = true;

  chassis.turnToPoint(35.8, 54.6, 1000, {.forwards=false});
  chassis.moveToPoint(35.8, 54.6, 1000, {.forwards=false});

  chassis.turnToPoint(-15.6, 106.6, 1000);
  chassis.moveToPoint(-15.6, 106.6, 3000, {.maxSpeed= 80});

  chassis.turnToPoint(24, 121.8, 1000);
  chassis.moveToPoint(24, 121.8, 3000);



}



void redRight() {
	chassis.setPose(0, 0, 0);
  // pros::delay(2000);
	lb.lb_pid.set_consts(1.4, 0.0, 1.5);
	lb.move(16000);
	pros::delay(700);
  lb.lb_pid.set_consts(2.3, 0.0, 1.5);

	// First Mogo
	chassis.moveToPoint(0, -10, 1000, {.forwards = false});
	chassis.turnToPoint(11.9, -33.5, 1000, {.forwards=false});
	chassis.moveToPoint(11.9, -33.5, 1000, {.forwards = false, .maxSpeed = 80});
	chassis.waitUntilDone();
	mogo.extend();
  lb.move(-2000);
	pros::delay(300);
  intake.move_velocity(12000);


	chassis.turnToPoint(-4.25, -55, 1000);
	chassis.moveToPoint(-4.25, -55, 1000);

	chassis.turnToPoint(-43.25, -40, 1000);
  antiJam = true;
	chassis.moveToPoint(-43.25, -40, 1000, {.maxSpeed = 60});
	chassis.waitUntilDone();
	pros::delay(1000);
	chassis.moveToPoint(-47.64, -37.74, 	1000);
  pros::delay(3000);
  chassis.turnToPoint(11.9, -33.5, 1000);
	chassis.moveToPoint(11.9, -33.5, 1000);
  chassis.waitUntilDone();
  lb.move(12000);
	
	
}

void redLeft(){
	chassis.setPose(0, 0, 0);
  // pros::delay(2000);
  lb.lb_pid.set_consts(1.4, 0.0, 1.5);	lb.move(16000);
	pros::delay(700);
  lb.lb_pid.set_consts(2.3, 0.0, 1.5);

	// First Mogo
	chassis.moveToPoint(0, -10, 1000, {.forwards = false});
	chassis.turnToPoint(-11.9, -33.5, 1000, {.forwards=false});
	chassis.moveToPoint(-11.9, -33.5, 1000, {.forwards = false, .maxSpeed = 80});
	chassis.waitUntilDone();
	mogo.extend();
  lb.move(-2000);
	pros::delay(500);
  intake.move_velocity(12000);
  pros::delay(300);

	chassis.turnToPoint(9.9, -52, 1000);
  chassis.moveToPoint(9.9, -52, 1000);


	chassis.turnToPoint(53.25, -15, 1000);
  antiJam = true;
	chassis.moveToPoint(53.25, -15, 1000, {.maxSpeed = 60});
	chassis.waitUntilDone();
	pros::delay(1000);
	chassis.moveToPoint(50.5, -26.2, 	1000);
  pros::delay(3000);
  chassis.turnToPoint(28.4, -44.5, 1000);
  chassis.moveToPoint(28.4, -44.5, 1000);
  mogo.retract();
  chassis.turnToPoint(13.2, -59.1, 1000, {.forwards=false});
  chassis.moveToPoint(13.2, -59.1, 1000, {.forwards=false});

  // chassis.turnToPoint(-11.9, -33.5, 1000);
	// chassis.moveToPoint(-11.9, -33.5, 1000);
  // chassis.waitUntilDone();
  // lb.move(12000);

	
}


void redNeg() {
  /// ALSO BLUE POS!!
  chassis.setPose(0, 0, 0);
  lb.lb_pid.set_consts(1.4, 0.0, 1.5);	lb.move(16000);
	pros::delay(700);
	lb.lb_pid.set_consts(2.3, 0.0, 1.5);


	// First Mogo
	chassis.moveToPoint(0, -10, 1000, {.forwards = false});
	chassis.turnToPoint(-11.9, -33.5, 1000, {.forwards=false});
	chassis.moveToPoint(-11.9, -33.5, 1000, {.forwards = false, .maxSpeed = 80});
	chassis.waitUntilDone();
	mogo.extend();
	pros::delay(400);
  lb.move(-2000);
  chassis.turnToPoint(-10.3, -54.85, 1000);
  intake.move_velocity(12000);

  chassis.moveToPoint(-10.3, -54.85, 1000);
  chassis.moveToPoint(-7.47, -38.6, 1000, {.forwards = false});
  chassis.turnToPoint(8.4, -49.1, 1000);
  chassis.moveToPoint(8.4, -49.1, 1000);
  chassis.turnToPoint(1.8, -60.88, 1000);
  chassis.moveToPoint(1.8, -60.88, 1000);
  chassis.moveToPoint(19.5, -32, 1000);
  chassis.turnToPoint(43.7, -32, 1000);
  chassis.moveToPoint(43.7, -32, 1000);
  chassis.moveToPoint(49.6, -31.9, 1000);
  chassis.turnToPoint(-11.8, -40.1, 1000);
  chassis.moveToPoint(-11.8, -40.1, 1000);
  chassis.waitUntilDone();
  lb.move(12000);
}

void blueNeg() {
  chassis.setPose(0, 0, 0);
  lb.lb_pid.set_consts(1.4, 0.0, 1.5);	lb.move(16000);
	pros::delay(700);
  lb.lb_pid.set_consts(2.3, 0.0, 1.5);

	// First Mogo
	chassis.moveToPoint(0, -10, 1000, {.forwards = false});
	chassis.turnToPoint(11.9, -34.5, 600, {.forwards=false});
	chassis.moveToPoint(11.9, -34.5, 1000, {.forwards = false, .maxSpeed = 80});
	chassis.waitUntilDone();
	mogo.extend();
	pros::delay(700);

  lb.move(-2000);
  chassis.turnToPoint(10.3, -65.85, 1000);
  intake.move_velocity(12000);
  pros::delay(200);
  antiJam = true;
  chassis.moveToPoint(10.3, -65.85, 1000);
  chassis.moveToPoint(7.47, -48.6, 1000, {.forwards = false});
  chassis.turnToPoint(-8.4, -59.1, 1000);
  chassis.moveToPoint(-8.4, -59.1, 1000);
  chassis.turnToPoint(5, -73.88, 1000);
  chassis.moveToPoint(5, -73.88, 1000);
  chassis.moveToPoint(-19.5, -32, 1000);
  chassis.turnToPoint(-53.7, -32, 1000);
  chassis.moveToPoint(-53.7, -32, 1000);
  chassis.moveToPoint(-59.6, -31.9, 1000);
  pros::delay(3000);
  chassis.turnToPoint(11.8, -40.1, 1000);
  chassis.moveToPoint(11.8, -40.1, 1000);
  chassis.waitUntilDone();
  lb.move(12000);
}


void twelveInch() {
  chassis.setPose({0, 0, 0});
  chassis.moveToPoint(0, 12, 4000);
}

void test() {
  chassis.setPose({0, 0, 0});
  lb.lb_pid.set_consts(300.0, 0.0, 50.0);
  lb.move(210);
  pros::delay(2000);
  lb.lb_pid.set_consts(100.0, 0.0, 50.0);
  lb.move(25);
  intake.move_velocity(12000);
  pros::delay(2000);
  lb.lb_pid.set_consts(300.0, 0.0, 50.0);
  intake.move_velocity(0);
  lb.move(210);
  pros::delay(2000);
  lb.lb_pid.set_consts(100.0, 0.0, 50.0);
  lb.move(-30);
  lb.off();
}