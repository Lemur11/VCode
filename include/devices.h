#include "main.h"
#include "pros/distance.hpp"
#include "pros/motor_group.hpp"
#include "pros/rotation.hpp"

extern pros::MotorGroup left_motors;
extern pros::MotorGroup right_motors;

extern pros::Motor left_motor;
extern pros::Motor right_motor;

extern pros::Motor lady_brown;

extern pros::MotorGroup intake;

extern pros::adi::Pneumatics mogo;
extern pros::adi::Pneumatics doinker;
extern pros::adi::Pneumatics intake_lift;

extern pros::Controller controller;

extern pros::Imu imu;

extern pros::Rotation rot;
extern pros::Distance mogod;
extern pros::Distance intakeD;

extern pros::Rotation backEncoder;