#include "intake.h"
#include "devices.h"

Intake::Intake(double length, double topPos, double sensorPos) : 
            fullLength(length), top(topPos), sensorPos(sensorPos) {
  hooks = {0, fullLength/3.0, fullLength*2.0/3.0};
  throwL = {};
  update_task = std::make_unique<pros::Task>([this] {
    while (1) {
      this->update();
      pros::delay(10);
    }
  });
}


void Intake::update() {
  for (int hookIdx : throwL) {
    double hook = hooks[hookIdx];
    hook += intake.get_position();
    hook = fmod(hook, fullLength);
    if (hook >= top) {
      kick();
      throwL.erase(throwL.begin() + hookIdx);
    }
  }
  if (intakeD.get() < 70) {
    if ((sortState == RED && intakeC.get_hue() > 120) or 
        (sortState == BLUE && intakeC.get_hue() < 40)) {
      double minDist = 100000;
      double minHook = 0;
      for (int hookIdx : std::vector<int>{0, 1, 2}) {
        double hook = hooks[hookIdx];
        hook += intake.get_position();
        hook = fmod(hook, fullLength);
        double dist = fabs(hook - sensorPos);
        if (dist < minDist) {
          minDist = dist;
          minHook = hookIdx;
        }
      }
      setToThrow(minHook);
    }
  }
}

void Intake::kick() {
  intake.move_velocity(-600);
  pros::delay(400);
  intake.move_velocity(600);
}

void Intake::setSort(color_enum color) {
  sortState = color;
}

void Intake::setToThrow(int hookNumber) {
    throwL.push_back(hookNumber);
  }
