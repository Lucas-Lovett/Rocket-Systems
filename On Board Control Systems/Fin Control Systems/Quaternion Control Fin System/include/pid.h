#ifndef PID_H
#define PID_H

#include <HardwareSerial.h>

class pid {
    public:
        pid(float p, float i, float d);

        float p() const {
            return kp;
        }
        float i() const {
            return ki;
        }
        float d() const {
            return kd;
        }

        float pidControl(float error, float dt);

        void print() {
            Serial.print("P: "); Serial.print(kp); Serial.print('\t');
            Serial.print("I: "); Serial.print(ki); Serial.print('\t');
            Serial.print("D: "); Serial.print(kd); Serial.print('\t');
            Serial.print("Integral: "); Serial.print(integral); Serial.print('\t');
            Serial.print("Error: "); Serial.println(pError);
        }

    private:
        float kp = 0.0f;
        float ki = 0.0f;
        float kd = 0.0f;
        float integral = 0.0f;
        float pError = 0.0f;
};

#endif