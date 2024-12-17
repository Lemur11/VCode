#include "main.h"
#include "pros/adi.hpp"
#include "pros/distance.hpp"
#include "pros/motor_group.hpp"

// left motor group
pros::MotorGroup left_motors({-9, 10, -20}, pros::MotorGears::blue);
// right motor group
pros::MotorGroup right_motors({11, -12, 1}, pros::MotorGears::blue);

// drivetrain settings
lemlib::Drivetrain drivetrain(&left_motors, // left motor group
                              &right_motors, // right motor group
                              12, // 12 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 3.25" omnis
                              450, // drivetrain rpm is 450
                              2 // horizontal drift is 2 (for now)
);

//imu
pros::Imu imu = pros::Imu(2);
// horizontal tracking wheel encoder
pros::Rotation horizontal_encoder(3);
// horizontal tracking wheel
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder, lemlib::Omniwheel::NEW_325, -1.911); //6.7676
// vertical tracking wheel encoder
// TODO: NOT HERE YET
// vertical tracking wheel
// lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, lemlib::Omniwheel::NEW_275, -2.5);

// odometry settings
lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            &horizontal_tracking_wheel, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// lateral PID controller
lemlib::ControllerSettings lateral_PID(10, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              3, // derivative gain (kD)
                                              3, // anti windup
                                              0.25, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              1000, // large error range timeout, in milliseconds
                                              0.5 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_PID(6, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              22, // derivative gain (kD)
                                              3, // anti windup
                                              0.5, // small error range, in degrees
                                              200, // small error range timeout, in milliseconds
                                              2, // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// input curve for throttle input during driver control
lemlib::ExpoDriveCurve throttleCurve(3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1.019 // expo curve gain
);

// input curve for steer input during driver control
lemlib::ExpoDriveCurve steerCurve(3, // joystick deadband out of 127
                                  10, // minimum output where drivetrain will move out of 127
                                  1.019 // expo curve gain
);

// create the chassis
lemlib::Chassis chassis(drivetrain, lateral_PID, angular_PID, 
                        sensors, &throttleCurve, &steerCurve);

// lb
pros::Motor lady_brown = pros::Motor(16);

// intake
pros::MotorGroup intake = pros::MotorGroup({-4, 17});

// pneumatics
pros::adi::Pneumatics mogo = pros::adi::Pneumatics('a', false);
pros::adi::Pneumatics doinker = pros::adi::Pneumatics('b', false);
pros::adi::Pneumatics intake_lift = pros::adi::Pneumatics('c', false);

// controller
pros::Controller controller = pros::Controller(pros::E_CONTROLLER_MASTER);

// sensors
pros::Rotation rot = pros::Rotation(18);
pros::Distance mogod = pros::Distance(3);
pros::Distance intakeD = pros::Distance(14);


