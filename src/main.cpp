#include "main.h"
#include "devices.h"
#include "ladybrown.h"
#include "utils.h"
#include "motions.h"
#include <cstdio>


// init lady brown class and state var
LadyBrown lb = LadyBrown();
lady_brown_state_enum lady_brown_state = lady_brown_state_enum::NORMAL;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	// imu calibration
	imu.reset(true);
	imu.tare();

	// reset motors and motor encoders
	left_motors.set_gearing_all(pros::E_MOTOR_GEARSET_06);
	right_motors.set_gearing_all(pros::E_MOTOR_GEARSET_06);
	left_motor.set_gearing(pros::E_MOTOR_GEARSET_06);
	right_motor.set_gearing(pros::E_MOTOR_GEARSET_06);
	left_motor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
	right_motor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
	left_motor.tare_position();
	right_motor.tare_position();

	rot.reset();
	rot.reset_position();

	lady_brown.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

	// lady_brown.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	int intake_vel = 600;
	left_motors.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	right_motors.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

	int cur_target;
	int reading;
	int lb_vol;

	move(1000);
	turn(90);
	move(1000);
	turn(90);
	move(1000);
	turn(90);
	move(1000);
	turn(90);

	printf("OPCONTROL\n");
	while (true) {
		// Arcade control scheme with deadzones
		int dir = joystick(controller.get_analog(ANALOG_LEFT_Y));    // Gets amount forward/backward from left joystick
		int turn_p = joystick(controller.get_analog(ANALOG_RIGHT_X));  // Gets the turn left/right from right joystick
		left_motors.move(dir + turn_p);                      // Sets left motor voltage
		right_motors.move(dir - turn_p);                     // Sets right motor voltage

		pros::lcd::print(1, "%f, %f", left_motor.get_position(), right_motor.get_position());
	
		// button logic
		// use toggle (on rising edge)
		if (lady_brown_state != lady_brown_state_enum::MANUAL) {
			if (controller.get_digital_new_press(DIGITAL_L1)) {
				mogo.extend();
			} 
			else if (controller.get_digital_new_press(DIGITAL_L2)) {
				mogo.retract();
			}
		}
		
		if (controller.get_digital_new_press(DIGITAL_LEFT)) {
			doinker.toggle();
		}

		if (controller.get_digital_new_press(DIGITAL_RIGHT)) {
			intake_lift.toggle();
		}

		if (controller.get_digital(DIGITAL_R1)) {
				intake.move_velocity(intake_vel);
			} 
		else if (controller.get_digital(DIGITAL_R2)) {
			intake.move_velocity(-intake_vel);		
		}
		else {
			intake.move_velocity(0);
		}

		switch(lady_brown_state) {
			case NORMAL:
			{
				lb.off();
				printf("Normal\n");
				printf("Power %f\n", lady_brown.get_power());
				lady_brown.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
				if (controller.get_digital_new_press(DIGITAL_A)) {
					lady_brown_state = FIRST;
					lb.move(3500);
				}
				break;
			}
			case FIRST:
			{
				if (controller.get_digital_new_press(DIGITAL_A)) {
					printf("Done\n");
					lb.move(5000);
					lady_brown_state = SECOND;
				}
				break;
			}
			case SECOND:
			{
				if (controller.get_digital_new_press(DIGITAL_A)) {
					lb.off();
					lady_brown_state = MANUAL;
				}
				break;
			}
			case MANUAL:
			{
				lady_brown.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
				printf("Manual\n");
				if (controller.get_digital(DIGITAL_L1)) {
					lb_vol = 8000;
				}
				else if (controller.get_digital_new_press(DIGITAL_A)) {
					left_motors.move_voltage(10000);
					right_motors.move_voltage(10000);
					pros::delay(300);
					lb.move(1000);
					pros::delay(500);
					left_motors.move_voltage(0);
					right_motors.move_voltage(0);
					lady_brown_state = RESET;
				}
				else if (controller.get_digital(DIGITAL_L2)) {
					lb_vol = -8000;
				}
				else {
					lb_vol = 0;
				}
				if (rot.get_position() > 15000) {
					lady_brown.move_voltage(std::min(0, lb_vol));
				}
				else {
					lady_brown.move_voltage(lb_vol);
				}
				break;
			}
			case RESET:
			{
				reading = rot.get_position();
				if (controller.get_digital(DIGITAL_A)) {
					lady_brown_state = NORMAL;
				} 
				if (lb.done()) {
					printf("EXIT\n");
					lb.off();
					lady_brown.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
					printf("Coasting\n");
					lady_brown_state = NORMAL;
				}
				break;
			}
			
		}

		pros::delay(20);                               // Run for 20 ms then update
	}
}