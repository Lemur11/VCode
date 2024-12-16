#include "main.h"
#include "devices.h"
#include "pros/misc.h"
#include "robodash/views/console.hpp"
#include "utils.h"
#include "autons.h"
#include "ladybrown.h"

// init lady brown class and state var
lady_brown_state_enum lady_brown_state = lady_brown_state_enum::NORMAL;

rd::Selector selector({
    {"Skills", skills},
	{"Move 12", twelveInch}
});

rd::Console console;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	chassis.calibrate();

	rot.reset();
	rot.set_position(500);

	lb.initialize();
	lb.move(0);

	lady_brown.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

	pros::Task screenTask([&]() {
        while (true) {
			console.clear();
            // print robot location to the brain screen
            console.printf( "X: %f\n", chassis.getPose().x); // x
            console.printf( "Y: %f\n", chassis.getPose().y); // y
            console.printf( "Theta: %f\n", chassis.getPose().theta); // heading
            // log position telemetry
            lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
            // delay to save resources
            pros::delay(50);
        }
    });

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
void autonomous() {
	selector.run_auton();
}

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

	printf("OPCONTROL\n");
	while (true) {
		// Arcade control scheme with deadzones
		int dir = joystick(controller.get_analog(ANALOG_LEFT_Y));    // Gets amount forward/backward from left joystick
		int turn_p = joystick(controller.get_analog(ANALOG_RIGHT_X));  // Gets the turn left/right from right joystick
		chassis.arcade(dir, turn_p);

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
		
		if (controller.get_digital_new_press(DIGITAL_Y)) {
			doinker.toggle();
		}

		// if (controller.get_digital_new_press(DIGITAL_RIGHT)) {
			// intake_lift.toggle();
		// }

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
				if (controller.get_digital_new_press(DIGITAL_RIGHT)) {
					lady_brown_state = FIRST;
					lb.move(4100);
				}
				break;
			}
			case FIRST:
			{
				if (controller.get_digital_new_press(DIGITAL_RIGHT)) {
					printf("Done\n");
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
				else if (controller.get_digital_new_press(DIGITAL_RIGHT)) {
					lb.move(1000);
					lady_brown_state = RESET;
				}
				else if (controller.get_digital(DIGITAL_L2)) {
					lb_vol = -8000;
				}
				else {
					lb_vol = 0;
				}
				if (rot.get_position() > 19000) {
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
				if (controller.get_digital_new_press(DIGITAL_RIGHT)) {
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