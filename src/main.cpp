#include "main.h"

#include <atomic>

#include "devices.h"
#include "utils.h"
#include "autons.h"
#include "ladybrown.h"

std::vector<pros::controller_digital_e_t> buttons{DIGITAL_A, DIGITAL_B, DIGITAL_X, DIGITAL_Y, DIGITAL_LEFT,
												DIGITAL_RIGHT, DIGITAL_R1, DIGITAL_R2, DIGITAL_L1, DIGITAL_L2};

#define press(button) 	while (!controller.get_digital(button)) {pros::delay(20);}
#define pressOnly(button) while (!controller.get_digital(button)) { \
	for (auto but : buttons) { \
		if (but == button) {continue;} \
		else if (controller.get_digital(but)) {while (1){pros::delay(20);}} \
	} \
	pros::delay(20);}


// init lady brown class and state var
lady_brown_state_enum lady_brown_state = lady_brown_state_enum::NORMAL;
color_enum color = color_enum::NONE;

rd::Selector selector({
    // {"Test", test},
	{"elims", elims},
	{"Move 12", twelveInch},
	{"Blue Left", blueLeftSide},
{"Red Left", redLeftSide},

	{"Red Right", redRightSide},
	{"Blue Right", blueRightSide},
});

rd::Console console;

std::atomic<bool> sorting{false};
std::atomic<bool> antiJam{false};

void vibrator() {
	while (0) {
		if (!mogo.is_extended()) {
			controller.rumble(".");
		}
		pros::delay(200);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	chassis.calibrate();
	chassis.setPose(0, 0, 360-120);

	lady_brown.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
	lady_brown.set_gearing(pros::E_MOTOR_GEAR_RED);
	lady_brown.set_zero_position(0);

	lb.initialize();
	lb.off();

	lady_brown.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	pros::Task([&]() {
		int counter = 0;
		while (true) {
			if (antiJam && !sorting && intake.get_actual_velocity() < 10) {
				if (counter > 100) {
					intake.move_velocity(-600);
					pros::delay(400);
					intake.move_velocity(600);
					pros::delay(100);
					counter = 0;
				}
				else {counter++;}

			}
			pros::delay(20);
		}
	});

	pros::Task([&]() {
		intakeC.set_led_pwm(100);
		while (true) {
			if (intakeD.get() < 70) {
				sorting = true;
				if (color == RED && intakeC.get_hue() < 40) {
					pros::delay(200);
					intake.move_velocity(-600);
					pros::delay(400);
					intake.move_velocity(600);
				}
				else if (color == BLUE && intakeC.get_hue() > 120) {
					pros::delay(200);
					intake.move_velocity(-600);
					pros::delay(400);
					intake.move_velocity(600);
				}
			}
			else {sorting = false;}
			pros::delay(10);
		}
	});

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
	console.focus();
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

	pros::Task vib(vibrator);

	console.focus();

	color = NONE;

	lady_brown_state = NORMAL;



	// pros::delay(200);
	// while (controller.get_analog(ANALOG_LEFT_Y) > -5) {pros::delay(20);}


	// press(DIGITAL_X)
	// press(DIGITAL_Y)


	printf("OPCONTROL\n");
	while (true) {
		// Arcade control scheme with deadzones
		int dir = joystick(controller.get_analog(ANALOG_LEFT_Y));    // Gets amount forward/backward from left joystick
		int turn_p = joystick(controller.get_analog(ANALOG_RIGHT_X));  // Gets the turn left/right from right joystick
		chassis.arcade(dir, turn_p);

		if (controller.get_digital_new_press(DIGITAL_X)) {
			printf("%f, %f, %f\n", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
		}

		if (controller.get_digital_new_press(DIGITAL_RIGHT)) {
			mogo.extend();
		}
		else if (controller.get_digital_new_press(DIGITAL_Y)) {
			mogo.retract();
		}

		// button logic
		// use toggle (on rising edge)
		// if (controller.get_digital_new_press(DIGITAL_DOWN)) {
		// 	lb.move(7000);
		// }
		
		if (controller.get_digital_new_press(DIGITAL_A)) {
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

		if (controller.get_digital_new_press(DIGITAL_UP)) {
			intake_lift.toggle();
		}

		if (controller.get_digital(DIGITAL_L2)) {
			lb.off();
			lady_brown.move_voltage(-12000);
		}
		else if (!lb.isOn()) {
			lady_brown.move_voltage(0);
		}
		if (1) {
			switch(lady_brown_state) {
				case NORMAL:
				{
					lb.off();
					printf("Normal\n");
					// printf("Power %f\n", lady_brown.get_power());
					lady_brown.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
					if (controller.get_digital_new_press(DIGITAL_L1)) {
						lady_brown_state = FIRST;
						lb.move(-29);
					}
					break;
				}
				case FIRST:
				{
					lady_brown.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
					if (controller.get_digital_new_press(DIGITAL_L1)) {
						lady_brown_state = RESET;
						lb.move(-27);
					}
					break;
				}
				case RESET:
				{
					if (controller.get_digital_new_press(DIGITAL_L1)) {
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
		}

		pros::delay(20);                               // Run for 20 ms then update
	}
}