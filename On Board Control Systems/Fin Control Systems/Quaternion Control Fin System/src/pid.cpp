#include "pid.h"

pid::pid(float p, float i, float d) {
    kp = p;
    ki = i;
    kd = d;
}

float pid::pidControl(float error, float dt) {
    float derivative;
    if (dt <= 0.001f) {
        integral += error * dt;
        derivative = 0;
        pError = error;
    } else {
        integral += error * dt;
        derivative = (error - pError) / dt;
        pError = error;
    }
    return (kp * error) + (ki * integral) + (kd * derivative);
}