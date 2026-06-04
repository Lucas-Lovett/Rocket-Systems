#include "fins.h"

fins::fins(int pins[], int count) {
    for (int i = 0; i < count; i++) {
        this->pins[i] = pins[i];
        servos[i].attach(pins[i]);
    }
}

void fins::setFinPos(int fin, int angle) {
    if (fin >= 0 && fin < 3) {
        servos[fin].write(angle);
    } else {
        Serial.println("Trying to acsess non existant fin");
    }
}