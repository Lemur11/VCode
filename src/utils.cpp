#include "main.h"

float wrap(float target, float reading) {
    float delta = fmod((reading - target + 540.0), 360.0) - 180.0;
    return -delta;
}

int sgn(float x) {
    return (x > 0) - (x < 0);
}  