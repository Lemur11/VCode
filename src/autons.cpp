#include "main.h"
#include "devices.h"
#include "ladybrown.h"

void skills() {
	chassis.setPose({0, 0, 0});
	chassis.moveToPoint(0, 24, 4000);
	chassis.turnToHeading(90, 4000, {.maxSpeed=70});
	chassis.turnToHeading(135, 4000, {.maxSpeed=70});
	chassis.turnToHeading(180, 4000, {.maxSpeed=70});
	chassis.turnToHeading(225, 4000, {.maxSpeed=70});
	chassis.turnToHeading(270, 4000, {.maxSpeed=70});
	chassis.turnToHeading(315, 4000, {.maxSpeed=70});
	chassis.turnToHeading(0, 4000, {.maxSpeed=70});
}

void twelveInch() {
	chassis.setPose({0, 0, 0});
	chassis.moveToPoint(0, 12, 4000);
}