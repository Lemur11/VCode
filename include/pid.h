#pragma once
class PID {
    private:
        float kp, ki, kd;
        float prev_error;
        float prev_vol=0.0;
        float vol;
        float error;
        float delta;
        float err_sum = 0.0;
    public:
        PID(float p, float i, float d);
        float cycle(float reference, float reading);
        void set_consts(float kp, float ki, float kd);
        void set_prev(float val);
        float get_prev();
        void reset_sum();
        void reset_vol();
        float get_deriv();
};