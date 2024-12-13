#include "main.h"
#include "pros/adi.hpp"
#include "pros/distance.hpp"
#include "pros/motor_group.hpp"

// motors
pros::MotorGroup left_motors = pros::MotorGroup({-9, 10, -20});
pros::MotorGroup right_motors = pros::MotorGroup({11, -12, 1});

pros::Motor left_motor = pros::Motor(-9);
pros::Motor right_motor = pros::Motor(11);

pros::Motor lady_brown = pros::Motor(16);

pros::MotorGroup intake = pros::MotorGroup({-4, 17});

// pneumatics
pros::adi::Pneumatics mogo = pros::adi::Pneumatics('a', false);
pros::adi::Pneumatics doinker = pros::adi::Pneumatics('b', false);
pros::adi::Pneumatics intake_lift = pros::adi::Pneumatics('c', false);

// controller
pros::Controller controller = pros::Controller(pros::E_CONTROLLER_MASTER);

// sensors
pros::Imu imu = pros::Imu(2);

pros::Rotation rot = pros::Rotation(18);
pros::Distance mogod = pros::Distance(3);
pros::Distance intakeD = pros::Distance(14);

// horizontal tracking wheel
pros::Rotation backEncoder = pros::Rotation(3);