#include <atomic>

#include "main.h"
#include "devices.h"
#include "ladybrown.h"
#include "pros/device.hpp"
#include "pros/rtos.hpp"

void skills() {
	/* 
	Initialization:
	- Line in the middle of double stacked delrin is on the right side (from driver perspective) of tile border
	- Front of robot touching alliance stake
	*/
	const int maxSpeed = 70;

	chassis.setPose({0, 0, 180});

	chassis.moveToPoint(0, 4, 1000, {.forwards=false});
	chassis.waitUntilDone();
	lb.move(18000);
	int stime = pros::millis();
	pros::delay(200);
	while (!lb.done()) {
		if (pros::millis() - stime > 3000) {
			break;
		}
		pros::delay(20);
	}
	lb.move(0, false);
	pros::delay(2000);
	lb.off();
	// chassis.turnToHeading(120, 4000, {.maxSpeed=maxSpeed});
	chassis.moveToPoint(-5, 22, 4000, {.forwards=false, .earlyExitRange=2});
	chassis.waitUntilDone();
	mogo.extend();
	pros::delay(500);
	// chassis.turnToHeading(0, 4000, {.maxSpeed=maxSpeed});
	// chassis.turnToPoint(-21, 59, 3000, {.maxSpeed=maxSpeed});
	// chassis.waitUntilDone();
	intake.move_velocity(600);
	chassis.moveToPoint(-19, 59, 3000);
	// chassis.turnToPoint(-41, 108.5, 1400);
	chassis.moveToPose(-42, 108.5, 0, 5000);
	// chassis.turnToPoint(-58, 68, 4000);
	chassis.moveToPose(-60, 68, 270, 4000);
	chassis.waitUntil(7);
	lb.move(4100);
	while (intake.get_actual_velocity() > 50) {
		pros::delay(50);
	}
	intake.move_velocity(0);
	chassis.moveToPoint((chassis.getPose().x-6.0), chassis.getPose().y, 4000);
	chassis.waitUntil(2);
	lb.move(18000, true);
	lb.move(0, true);
	lb.off();
}

void twelveInch() {
	chassis.setPose({0, 0, 0});
	chassis.moveToPoint(0, 12, 4000);
}

void test() {
	mogo.extend();
	intake.move_velocity(600);
	pros::delay(5000);
	color = BLUE;
}

void red_awp() {
	/*
	Init: aligned using tool, front of robot almost touching blue ring
	*/
	chassis.setPose(0, 0, 130);
	chassis.moveToPoint(4.725138, -3.774354, 1000);
	chassis.waitUntilDone();
	lb.move(18000);
	int stime = pros::millis();
	pros::delay(200);
	while (!lb.done()) {
		if (pros::millis() - stime > 1500) {
			break;
		}
		pros::delay(20);
	}
	lb.move(1000, false);
	pros::delay(500);
	chassis.moveToPoint(-18.529989, 27.775496, 3000, {.forwards=false, .maxSpeed=80});
	lb.off();
	chassis.waitUntil(33);
	mogo.extend();
	intake.move_velocity(600);
	// chassis.moveToPoint(13.152055, -43.607040, 4000);
	chassis.moveToPoint(-47.889133, 26.993231, 4000,{.maxSpeed=90});
	chassis.waitUntilDone();
	chassis.moveToPoint(19.986078, 8.585527, 4000, {.maxSpeed=105, .earlyExitRange=2});
	chassis.waitUntil(60);
	intake.move_velocity(600);
	chassis.moveToPoint(chassis.getPose().x+20, chassis.getPose().y-10, 4000, {.earlyExitRange=3});
	int st_time = pros::millis();
	while (true) {
		if (pros::millis() - st_time > 1500) {
			break;
		}
		// if (intake.get_actual_velocity() < 10) {
		// 	printf("Unjamming\n");
		// 	pros::delay(50);
		// 	intake.move_velocity(-600);
		// 	pros::delay(400);
		// 	intake.move_velocity(600);
		// }
		if (intakeD.get() < 30) {
			printf("SORT\n");
			pros::delay(100);
			intake.move_velocity(-600);
			pros::delay(200);
			intake.move(600);
			break;
		}
		pros::delay(10);
	}
	intake.move_velocity(600);
	chassis.waitUntilDone();
	mogo.retract();
	chassis.moveToPoint(chassis.getPose().x+12, chassis.getPose().y, 4000, {.earlyExitRange=3});
	// chassis.turnToPoint(30.2, 28.7, 2000, {.forwards=false});
	chassis.moveToPoint(34, 32, 3000, {.forwards=false, .maxSpeed=100, .earlyExitRange=4});
	chassis.waitUntil(37);
	mogo.extend();
	pros::delay(200);
	intake.move_velocity(600);
	chassis.moveToPoint(68, 42.537998,2000);
	chassis.moveToPoint(25.733557, 27.948318, 2000);
}


void solo_awp() {
	std::atomic<int> ringCount{0};
	std::atomic<bool> seeing = false;
	std::atomic<bool> done = false;
	pros::Task counter = pros::Task([&]() {
		while (true) {
			if (done) {
				break;
			}
			if (!seeing && intakeD.get() < 70) {
				seeing = true;
				printf("Saw ring\n");
			}
			else if (seeing && intakeD.get() > 70) {
				seeing = false;
				++ringCount;
				printf("Ring count: %d\n", static_cast<int>(ringCount));
			}
			pros::delay(10);
		}
	});
  	chassis.setPose(0, 0, 120);
	chassis.moveToPoint(5.842803, -2.650379, 500);
	pros::delay(200);
	lb.move(20000);
	int stime = pros::millis();
	pros::delay(200);
	while (!lb.done()) {
		if (pros::millis() - stime > 700) {
			break;
		}
		pros::delay(20);
	}
	lb.move(1000, false);
	pros::delay(200);
	chassis.moveToPoint(-20.933121, 20.693683, 3000, {.forwards = false, .maxSpeed = 70, .earlyExitRange = 10}); // theta 132.165802
	while (chassis.getPose().distance(lemlib::Pose(-20.933121, 20.693683, 132.165802)) > 6) {
		pros::delay(50);
	}
	mogo.extend();
	chassis.cancelMotion();
	intake.move_velocity(600);
	chassis.moveToPoint(-49.950817, 12.715672, 3000); // 249.280914
	chassis.waitUntilDone();
	chassis.moveToPoint(25, 14.64, 2000, {.minSpeed = 70, .earlyExitRange = 10});
	chassis.moveToPoint(44.994579, 9.642445, 2000, {.maxSpeed = 80});
	while (true) {
		if (ringCount.load() == 1 && seeing) {
			pros::delay(100);
			intake.move_velocity(-600);
			pros::delay(200);
			intake.move_velocity(600);
			break;
		}
		pros::delay(10);
	}
	chassis.moveToPoint(chassis.getPose().x+5, chassis.getPose().y, 4000, {.earlyExitRange=3});
	stime = pros::millis();
	while (ringCount < 3) {
		if (pros::millis() - stime > 1500) { break; }
		pros::delay(50);
	}
	pros::delay(200);
	mogo.retract();
	chassis.moveToPoint(chassis.getPose().x+8, chassis.getPose().y, 4000, {.minSpeed = 70, .earlyExitRange=2});
	chassis.turnToPoint(30, 43.2, 2000, {.forwards = false, .minSpeed = 70, .earlyExitRange = 20});
	chassis.moveToPoint(32, 37, 2000, {.forwards = false, .earlyExitRange = 3}); // 30, 43.2
	while (chassis.getPose().distance(lemlib::Pose(35, 37, 180)) > 4) {
		pros::delay(50);
	}
	mogo.extend();
	chassis.moveToPoint(57.8, 47, 2000, {.minSpeed = 70, .earlyExitRange = 4});
	chassis.moveToPoint(-14.68, 32.19, 2000);

	done = true;
}

void red_rings() {
	color = BLUE;
	std::atomic<int> ringCount{0};
	std::atomic<bool> seeing = false;
	std::atomic<bool> done = false;
	pros::Task counter = pros::Task([&]() {
		while (true) {
			if (done) {
				break;
			}
			if (!seeing && intakeD.get() < 70) {
				seeing = true;
				printf("Saw ring\n");
			}
			else if (seeing && intakeD.get() > 70) {
				seeing = false;
				++ringCount;
				printf("Ring count: %d\n", static_cast<int>(ringCount));
			}
			pros::delay(10);
		}
	});
	chassis.setPose(0, 0, 120);
	chassis.moveToPoint(5.842803, -2.650379, 500);
	pros::delay(200);
	lb.move(20000);
	int stime = pros::millis();
	pros::delay(200);
	while (!lb.done()) {
		if (pros::millis() - stime > 700) {
			break;
		}
		pros::delay(20);
	}
	lb.move(1000, false);
	pros::delay(200);
	chassis.moveToPoint(-22.933121, 22.693683, 3000, {.forwards = false, .maxSpeed = 70, .earlyExitRange = 10}); // theta 132.165802
	while (chassis.getPose().distance(lemlib::Pose(-22.933121, 22.693683, 132.165802)) > 6) {
		pros::delay(50);
	}
	mogo.extend();
	chassis.cancelMotion();
	intake.move_velocity(600);
	antiJam = true;
	chassis.moveToPoint(-43.195377, 30.432755, 4000, {});
	// chassis.swingToHeading(270, DriveSide::RIGHT, 2000);
	chassis.moveToPoint(-57.887054, 20.030763, 4000, {.maxSpeed = 80});
	chassis.moveToPoint(-24, 3, 4000);
	chassis.turnToPoint(30, 10.5, 1000);
	chassis.moveToPoint(40, 10, 4000, {.maxSpeed = 80});

}


void elims() {
	color = BLUE;
	chassis.setPose(0, 0, 360-120);
	chassis.moveToPoint(-5.842803, -2.650379, 500);
	pros::delay(200);
	lb.move(20000);
	int stime = pros::millis();
	pros::delay(200);
	while (!lb.done()) {
		if (pros::millis() - stime > 700) {
			break;
		}
		pros::delay(20);
	}
	lb.move(1000, false);
	pros::delay(200);
	lb.move(7000);
	chassis.moveToPoint(11.98, 6.84, 2000, {.forwards = false});
	chassis.turnToHeading(270, 1000);
	intake_lift.set_value(true);
	intake.move_velocity(600);
	chassis.moveToPoint(-6.3, 14.95, 1000, {.maxSpeed = 70});
	chassis.waitUntilDone();
	intake_lift.set_value(false);
	stime = pros::millis();
	while (true) {
		if (pros::millis() - stime > 1200) {break;}
		if (intakeD.get() < 70) {
			break;
		}
		pros::delay(20);
	}
	// pros::delay(1000);

	// intake_lift.extend();
	antiJam = true;
	chassis.moveToPoint(10, 11.9, 1000, {.forwards = false});



	intake.move_velocity(0);
	chassis.turnToPoint(25.933121, 22.693683, 3000, {.forwards = false});
	chassis.moveToPoint(25.933121, 22.693683, 3000, {.forwards = false, .maxSpeed = 70, .earlyExitRange = 6}); // theta 132.165802
	while (chassis.getPose().distance(lemlib::Pose(25.933121, 22.693683, 132.165802)) > 3) {
		pros::delay(50);
	}
	mogo.extend();
	chassis.cancelMotion();
	pros::delay(500);
	antiJam = false;
	intake.move_velocity(600);

	chassis.turnToPoint(57.5, 16, 700);
	chassis.moveToPoint(57.5, 16, 1000);
	// antiJam = true;
	// chassis.moveToPoint(0, 40, 2000);
}


















void blue_rings() {
	std::atomic<int> ringCount{0};
	std::atomic<bool> seeing = false;
	std::atomic<bool> done = false;
	pros::Task counter = pros::Task([&]() {
		while (true) {
			if (done) {
				break;
			}
			if (!seeing && intakeD.get() < 70) {
				seeing = true;
				printf("Saw ring\n");
			}
			else if (seeing && intakeD.get() > 70) {
				seeing = false;
				++ringCount;
				printf("Ring count: %d\n", static_cast<int>(ringCount));
			}
			pros::delay(10);
		}
	});
	chassis.setPose(0, 0, 360-120);
	chassis.moveToPoint(-5.842803, -2.650379, 500);
	pros::delay(200);
	lb.move(20000);
	int stime = pros::millis();
	pros::delay(200);
	while (!lb.done()) {
		if (pros::millis() - stime > 700) {
			break;
		}
		pros::delay(20);
	}
	lb.move(1000, false);
	pros::delay(200);
	chassis.moveToPoint(22.933121, 22.693683, 3000, {.forwards = false, .maxSpeed = 70, .earlyExitRange = 10}); // theta 132.165802
	while (chassis.getPose().distance(lemlib::Pose(22.933121, 22.693683, 132.165802)) > 6) {
		pros::delay(50);
	}
	mogo.extend();
	chassis.cancelMotion();
	intake.move_velocity(600);
	chassis.moveToPoint(44.195377, 43.432755, 2000, {});
	// chassis.swingToHeading(90, DriveSide::LEFT, 2000);
	chassis.moveToPoint(55.887054, 38.030763, 4000, {.maxSpeed = 80}); // 48, 50
	chassis.turnToPoint(34, 23, 1000, {.minSpeed = 60, .earlyExitRange = 10});
	chassis.moveToPoint(34, 23, 4000);
	chassis.turnToPoint(-14, 12, 1000);
	chassis.moveToPoint(-8, 27, 4000);
	doinker.extend();
	chassis.turnToHeading(180, 2000, {.maxSpeed = 90});
	chassis.waitUntilDone();
	doinker.retract();
	chassis.moveToPoint(-6, 1, 4000);
	done = true;
}

void redRight2() {
	color = BLUE;
	chassis.setPose(0, 0, 360-120);
	chassis.moveToPoint(-5.842803, -2.650379, 500);
	pros::delay(200);
	lb.move(20000);
	int stime = pros::millis();
	pros::delay(200);
	while (!lb.done()) {
		if (pros::millis() - stime > 700) {
			break;
		}
		pros::delay(20);
	}
	lb.move(1000, false);
	pros::delay(200);
		lb.move(7000);
	chassis.moveToPoint(11.98, 6.84, 2000, {.forwards = false});
	chassis.turnToHeading(270, 2000);
	intake_lift.toggle();
	intake.move_velocity(600);
	chassis.moveToPoint(-6.1, 14.95, 2000, {.maxSpeed = 70});
	intake_lift.toggle();
	chassis.moveToPoint(10.82, 11.9, 2000, {.forwards = false});
	while (true) {
		if (intakeD.get() < 70) {
			break;
		}
		pros::delay(20);
	}
	intake.move_velocity(0);
	chassis.moveToPoint(22.933121, 22.693683, 3000, {.forwards = false, .maxSpeed = 70, .earlyExitRange = 6}); // theta 132.165802
	while (chassis.getPose().distance(lemlib::Pose(22.933121, 22.693683, 132.165802)) > 3) {
		pros::delay(50);
	}
	mogo.extend();
	chassis.cancelMotion();
	pros::delay(1000);
	intake.move_velocity(450);
	antiJam = false;
	pros::delay(500);
	chassis.turnToHeading(90, 2000);
	chassis.moveToPoint(57.5, 16.5, 2000);
		antiJam = true;

	while (intakeD.get() > 70) {
		pros::delay(20);
	}
	chassis.waitUntilDone();
	antiJam = false;
	intake.move_velocity(0);
	chassis.turnToHeading(0,2000);
	chassis.waitUntilDone();
	intake.move_velocity(600);
	pros::delay(1500);
		mogo.retract();
	chassis.moveToPoint(34, 1, 2000, {.forwards=false});
	pros::delay(1000);
	chassis.moveToPoint(42, 28, 2000);
	chassis.turnToHeading(180, 2000);
	chassis.moveToPoint(36, 28, 2000, {.forwards=false});

}

void blueLeft2() {
	color = BLUE;
	chassis.setPose(0, 0, 120);
	// chassis.moveToPoint(5.842803, -2.650379, 500);
	// pros::delay(200);
	// lb.move(20000);
	// int stime = pros::millis();
	// pros::delay(200);
	// while (!lb.done()) {
	// 	if (pros::millis() - stime > 700) {
	// 		break;
	// 	}
	// 	pros::delay(20);
	// }
	// lb.move(1000, false);
	// pros::delay(200);
	chassis.moveToPoint(-21.933121, 22.693683, 3000, {.forwards = false, .maxSpeed = 70, .earlyExitRange = 10}); // theta 132.165802
	while (chassis.getPose().distance(lemlib::Pose(-21.933121, 22.693683, 132.165802)) > 4) {
		pros::delay(50);
	}
	lb.move(7000);
	mogo.extend();
	chassis.cancelMotion();
	intake.move_velocity(600);
	chassis.turnToHeading(260, 2000);
	chassis.moveToPoint(-49, 3, 2000, {.earlyExitRange = 3});
	while (intakeD.get() > 50) {
		pros::delay(20);
	}
	antiJam = false;
	intake.move_velocity(0);
	pros::delay(1000);
	chassis.turnToPoint(-45, -2, 2000, {.forwards=false});
	chassis.waitUntilDone();
	intake.move_velocity(600);
	chassis.moveToPoint(-45, -4, 2000, {.forwards=false});
	pros::delay(4000);
	mogo.retract();
	chassis.moveToPoint(-47, 18, 2000);
	chassis.turnToHeading(180, 2000);
}

void redRightSide() {
	color = BLUE;
	chassis.setPose(0, 0, 360-120);
	chassis.moveToPoint(-5.842803, -2.650379, 500);
	pros::delay(200);
	lb.move(20000);
	int stime = pros::millis();
	pros::delay(200);
	while (!lb.done()) {
		if (pros::millis() - stime > 700) {
			break;
		}
		pros::delay(20);
	}
	lb.move(1000, false);
	pros::delay(200);
	lb.move(7000);
	chassis.moveToPoint(11.98, 6.84, 2000, {.forwards = false});
	chassis.turnToHeading(270, 1000);
	intake_lift.set_value(true);
	intake.move_velocity(600);
	chassis.moveToPoint(-6.3, 14.95, 1000, {.maxSpeed = 70});
	chassis.waitUntilDone();
	intake_lift.set_value(false);
	pros::delay(1000);
	// intake_lift.extend();
	antiJam = true;
	chassis.moveToPoint(10, 11.9, 1000, {.forwards = false});


	while (true) {
		if (intakeD.get() < 70) {
			break;
		}
		pros::delay(20);
	}
	intake.move_velocity(0);
	chassis.turnToPoint(22.933121, 22.693683, 3000, {.forwards = false});
	chassis.moveToPoint(22.933121, 22.693683, 3000, {.forwards = false, .maxSpeed = 70, .earlyExitRange = 6}); // theta 132.165802
	while (chassis.getPose().distance(lemlib::Pose(22.933121, 22.693683, 132.165802)) > 3) {
		pros::delay(50);
	}
	mogo.extend();
	chassis.cancelMotion();
	pros::delay(500);
	antiJam = false;
	chassis.turnToPoint(57.5, 16, 700);
	chassis.moveToPoint(57.5, 16, 1000);
	intake.move_velocity(600);
	antiJam = true;
	chassis.moveToPoint(0, 40, 2000);
}

void redLeftSide() {
	color = BLUE;
	chassis.setPose(0, 0, 120);
	chassis.moveToPoint(5.842803, -2.650379, 500);
	pros::delay(200);
	lb.move(20000);
	int stime = pros::millis();
	pros::delay(200);
	while (!lb.done()) {
		if (pros::millis() - stime > 700) {
			break;
		}
		pros::delay(20);
	}
	lb.move(1000, false);
	pros::delay(200);
	lb.move(7000);
	chassis.moveToPoint(-11.98, 6.84, 2000, {.forwards = false});
	chassis.turnToHeading(90, 1000);
	intake_lift.set_value(true);
	intake.move_velocity(600);
	chassis.moveToPoint(1.5, 14.95, 1000, {.maxSpeed = 70});
	chassis.waitUntilDone();
	intake_lift.set_value(false);
	// intake_lift.extend();
	antiJam = true;
	chassis.moveToPoint(-10, 11.9, 1000, {.forwards = false});


	while (true) {
		if (intakeD.get() < 70) {
			break;
		}
		pros::delay(20);
	}
	antiJam = false;
	intake.move_velocity(0);
	chassis.turnToPoint(-24.933121, 22.693683, 1200, {.forwards = false});
	chassis.moveToPoint(-24.933121, 22.693683, 3000, {.forwards = false, .maxSpeed = 70, .earlyExitRange = 6}); // theta 132.165802
	while (chassis.getPose().distance(lemlib::Pose(-24.933121, 22.693683, 132.165802)) > 3) {
		pros::delay(50);
	}
	mogo.extend();
	chassis.cancelMotion();
	pros::delay(500);
	intake.move_velocity(600);
	chassis.turnToPoint(-57.5, 15, 700);
	chassis.moveToPoint(-57.5, 15, 1000);
	antiJam = true;
	chassis.moveToPoint(0, 45, 5000, {.maxSpeed = 70});
	lb.move(16000);
}

void blueLeftSide() {
	color = RED;
	chassis.setPose(0, 0, 120);
	chassis.moveToPoint(5.842803, -2.650379, 500);
	pros::delay(200);
	lb.move(20000);
	int stime = pros::millis();
	pros::delay(200);
	while (!lb.done()) {
		if (pros::millis() - stime > 700) {
			break;
		}
		pros::delay(20);
	}
	lb.move(1000, false);
	pros::delay(200);
	lb.move(7000);
	chassis.moveToPoint(-11.98, 6.84, 2000, {.forwards = false});
	chassis.turnToHeading(90, 1000);
	intake_lift.set_value(true);
	intake.move_velocity(600);
	chassis.moveToPoint(1.5, 14.95, 1000, {.maxSpeed = 70});
	chassis.waitUntilDone();
	intake_lift.set_value(false);
	// intake_lift.extend();
	antiJam = true;
	chassis.moveToPoint(-10, 11.9, 1000, {.forwards = false});


	while (true) {
		if (intakeD.get() < 70) {
			break;
		}
		pros::delay(20);
	}
	antiJam = false;
	intake.move_velocity(0);
	chassis.turnToPoint(-24.933121, 22.693683, 1200, {.forwards = false});
	chassis.moveToPoint(-24.933121, 22.693683, 3000, {.forwards = false, .maxSpeed = 70, .earlyExitRange = 6}); // theta 132.165802
	while (chassis.getPose().distance(lemlib::Pose(-24.933121, 22.693683, 132.165802)) > 3) {
		pros::delay(50);
	}
	mogo.extend();
	chassis.cancelMotion();
	pros::delay(500);
	intake.move_velocity(600);
	chassis.turnToPoint(-57.5, 15, 700);
	chassis.moveToPoint(-57.5, 15, 1000);
	antiJam = true;
	chassis.moveToPoint(0, 45, 5000, {.maxSpeed = 70});
	lb.move(16000);
}


void blueRightSide() {
	color = RED;
	chassis.setPose(0, 0, 360-120);
	chassis.moveToPoint(-5.842803, -2.650379, 500);
	pros::delay(200);
	lb.move(20000);
	int stime = pros::millis();
	pros::delay(200);
	while (!lb.done()) {
		if (pros::millis() - stime > 700) {
			break;
		}
		pros::delay(20);
	}
	lb.move(1000, false);
	pros::delay(200);
	lb.move(7000);
	chassis.moveToPoint(11.98, 6.84, 2000, {.forwards = false});
	chassis.turnToHeading(270, 1000);
	intake_lift.set_value(true);
	intake.move_velocity(600);
	chassis.moveToPoint(-6.3, 14.95, 1000, {.maxSpeed = 70});
	chassis.waitUntilDone();
	intake_lift.set_value(false);
	pros::delay(1000);
	// intake_lift.extend();
	antiJam = true;
	chassis.moveToPoint(10, 11.9, 1000, {.forwards = false});

	stime = pros::millis();

	while (true) {
		if (pros::millis() - stime > 1200) {break;}
		if (intakeD.get() < 70) {
			break;
		}
		pros::delay(20);
	}
	intake.move_velocity(0);
	chassis.turnToPoint(27.933121, 22.693683, 3000, {.forwards = false});
	chassis.moveToPoint(27.933121, 22.693683, 3000, {.forwards = false, .maxSpeed = 70, .earlyExitRange = 6}); // theta 132.165802
	while (chassis.getPose().distance(lemlib::Pose(25.933121, 22.693683, 132.165802)) > 3) {
		pros::delay(50);
	}
	mogo.extend();
	chassis.cancelMotion();
	pros::delay(500);
	antiJam = false;
	chassis.turnToPoint(57.5, 19, 700);
	chassis.moveToPoint(57.5, 19, 1000);
	intake.move_velocity(600);
	antiJam = true;
	chassis.moveToPoint(0, 40, 2000);
}
