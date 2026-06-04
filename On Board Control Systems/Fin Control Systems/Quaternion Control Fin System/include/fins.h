#ifndef FINS_H
#define FINS_H

#include <ESP32Servo.h>

class fins {
    public:
        fins(int pins[], int count);

        void setFinPos(int fin, int angle);
    private:
        Servo servos[3];
        int pins[3];
};

#endif