//
// Created by Simon Lisansky on 2/28/25.
//

#ifndef INTAKE_H
#define INTAKE_H

#include <vector>
#include "main.h"

enum color_enum {
  NONE,
  RED,
  BLUE,
};

class Intake {
  private:
    double top;
    double fullLength;
    double sensorPos;
    color_enum sortState{NONE};
    std::vector<double> hooks;
    std::vector<int> throwL;
    std::unique_ptr<pros::Task> update_task;
    void update();
    void kick();
    void setToThrow(int hookNumber);
  public:
    Intake(double length, double topPos, double sensorPos);
    void setSort(color_enum color);
};

#endif //INTAKE_H
