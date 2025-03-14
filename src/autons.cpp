#include "devices.h"
#include "ladybrown.h"
#include "main.h"
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
  chassis.moveToPoint(-9, 5.5, 1000, {.forwards = false, .maxSpeed = 80});
  chassis.waitUntilDone();
  mogo.extend();
  intake.move_velocity(12000);
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
  intake.move_velocity(0);

  chassis.angularPID.kP = 8;
  // chassis.turnToHeading(-18, 1000);
  chassis.turnToPoint(-54, 55.5, 1000, {.forwards = false});
  chassis.moveToPoint(-54, 55.5, 1000, {.forwards = false});

  chassis.angularPID.kP = 2.7;
  // chassis.turnToHeading(-104, 1000);
  chassis.turnToPoint(-70.5, 45.85, 1000);

  intake.move_velocity(12000);
  chassis.moveToPoint(-70.5, 43, 1000, {.maxSpeed = 60});
  left_motors.move_velocity(12000);
  right_motors.move_velocity(12000);
  pros::delay(1000);
  left_motors.move_velocity(0);
  right_motors.move_velocity(0);
  intake.move_velocity(0);
  lb.move(190);
  pros::delay(1000);
}

void twelveInch() {
  chassis.setPose({0, 0, 0});
  chassis.moveToPoint(0, 12, 4000);
}

void test() {
  chassis.setPose({-48, 0, 0});
  chassis.moveToPoint(12, 12, 4000);
}