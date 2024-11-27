#include "main.h"
#include "pid.h"
#include "devices.h"


class LadyBrown {
    private:
        int target = 0;
        int pos_deadzone = 100;
        int vel_deadzone = 10;
        bool on = true;
        bool at_target = true;
        void update();
        std::unique_ptr<pros::Task> update_task;
        PID lb_pid;
    public:
        LadyBrown();
        void off();
        bool done();
        void move(int cur_target, bool blocking=false);
};