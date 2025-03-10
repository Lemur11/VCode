#pragma once

#include "main.h"
#include "pid.h"
#include "devices.h"

#define lb LadyBrown::getInstance()

class LadyBrown {
    private:
        int target = 0;
        int pos_deadzone = 100;
        int vel_deadzone = 10;
        int ff_K = 0; //500
        bool on = true;
        bool at_target = true;
        void update();
        std::unique_ptr<pros::Task> update_task;
        PID lb_pid = PID(600.0, 0.0, 300.0, 45000.0);
        LadyBrown() = default;
	    LadyBrown(const LadyBrown&) = delete;
	    LadyBrown& operator=(const LadyBrown&) = delete;
    public:
        inline static LadyBrown& getInstance() {
    		static LadyBrown INSTANCE;
	    	return INSTANCE;
	    }   
        void initialize();
        void off();
		bool isOn();
        bool done();
        void move(int cur_target, bool blocking=false);
};
