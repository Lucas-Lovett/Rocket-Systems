#include "logger.h"

logger::logger(int pin) {
    this->csPin = pin;
}

void logger::begin() {
    Serial.println("Starting SD Card");
    while (!SD.begin(csPin)) {
        Serial.println("SD Card failed to start, retying...");
        delay(1000);
    }
    Serial.println("SD Card Started");
    Serial.println("Creating Fin Logs");
    finLogs = SD.open("finLogs.csv", FILE_WRITE);
    finLogs.println("timestamp, finIndex, angle");
    Serial.println("Fin Logs Created");
    Serial.println("Creating Quaternion Logs");
    quatLogs = SD.open("quatLogs.csv", FILE_WRITE);
    quatLogs.println("timestamp, qw, qx, qy, qz, errorW, errorX, errorY, errorZ, pitch, roll, pitchOutput, rollOutput");
    Serial.println("Quaternion Logs Created");
}

void logger::finLogger(unsigned long timeStamp, int finIndex, float angle) {
    finLogs.print(timeStamp); finLogs.print(",");
    finLogs.print(finIndex); finLogs.print(",");
    finLogs.println(angle);
}

void logger::quatLogger(unsigned long timeStamp, float qw, float qx, float qy, float qz, float errorW, float errorX, float errorY, float errorZ, float pitch, float roll, float pitchOutput, float rollOutput) {
    quatLogs.print(timeStamp); quatLogs.print(",");
    quatLogs.print(qw); quatLogs.print(",");
    quatLogs.print(qx); quatLogs.print(",");
    quatLogs.print(qy); quatLogs.print(",");
    quatLogs.print(qz); quatLogs.print(",");
    quatLogs.print(errorW); quatLogs.print(",");
    quatLogs.print(errorX); quatLogs.print(",");
    quatLogs.print(errorY); quatLogs.print(",");
    quatLogs.print(errorZ); quatLogs.print(",");
    quatLogs.print(pitch); quatLogs.print(",");
    quatLogs.print(roll); quatLogs.print(",");
    quatLogs.print(pitchOutput); quatLogs.print(",");
    quatLogs.println(rollOutput);
}