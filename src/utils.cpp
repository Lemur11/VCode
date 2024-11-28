#include "main.h"
#include "utils.h"

float wrap(float target, float reading) {
    float delta = fmod((reading - target + 540.0), 360.0) - 180.0;
    return -delta;
}

int sgn(float x) {
    return (x > 0) - (x < 0);
}  


int joystick(int inp) {
	if (abs(inp) < 15) {
		return 0;
	}
	else {
		return inp;
	}
}

float target_cal(float x) {
	if (x < 0) {
		return 360 - x;
	}
	else {
		return fmod(x, 360);
	}
}