#include "main.h"
#include "pros/adi.hpp"

// motors
pros::MotorGroup left_motors = pros::MotorGroup({-9, 10, -20});
pros::MotorGroup right_motors = pros::MotorGroup({11, -12, 1});

pros::Motor left_motor = pros::Motor(-9);
pros::Motor right_motor = pros::Motor(11);

pros::Motor lady_brown = pros::Motor(19);

pros::Motor intake = pros::Motor(17);

// pneumatics
pros::adi::Pneumatics mogo = pros::adi::Pneumatics('a', false);
pros::adi::Pneumatics doinker = pros::adi::Pneumatics('b', false);
pros::adi::Pneumatics claw = pros::adi::Pneumatics('h', false);

// controller
pros::Controller controller = pros::Controller(pros::E_CONTROLLER_MASTER);

// sensors
pros::Imu imu = pros::Imu(17);

pros::Rotation rot = pros::Rotation(18);
