#include "fins.h"
#include "pid.h"
#include "quaternion.h"
#include "logger.h"
#include "accessPoint.h"
#include <Adafruit_BNO08x.h>

Adafruit_BNO08x imu;

quaternion q1(1, 0, 0, 0);

int finPins[] = {5, 6, 7};
fins fin(finPins, 3);

pid pitchPID(0, 0, 0);
pid rollPID(0, 0, 0);

accessPoint preFlightAP("Ursus", "Spelaeus");

logger flightLogger(10, preFlightAP);

unsigned long lastTime = 0;

void setup() {
    Serial.begin(115200);
    delay(1000);
    preFlightAP.activateAP();

    preFlightAP.send("Starting IMU");
    while (!imu.begin_I2C()) {
        preFlightAP.send("IMU failed to boot, retrying...");
        delay(1000);
    }
    preFlightAP.send("IMU started");
    
    flightLogger.begin();

    preFlightAP.deactiveAP();
    
    imu.enableReport(SH2_ROTATION_VECTOR);
}

void loop() {
    sh2_SensorValue_t sensorValue;
    if (imu.getSensorEvent(&sensorValue)) {
        float w = sensorValue.un.rotationVector.real;
        float x = sensorValue.un.rotationVector.i;
        float y = sensorValue.un.rotationVector.j;
        float z = sensorValue.un.rotationVector.k;

        quaternion q2(w, x, y, z);

        float pitch = q2.getPitch();
        float roll = q2.getRoll();

        Serial.print("Pitch: "); Serial.print(pitch); Serial.print('\t');
        Serial.print("Roll: "); Serial.println(roll);

        quaternion error = q1 * conj(q2);

        float dt = (millis() - lastTime) / 1000.0f;
        lastTime = millis();

        float pitchOutput = pitchPID.pidControl(error.x(), dt);
        float rollOutput = rollPID.pidControl(error.y(), dt);

        Serial.print("Pitch Output: "); Serial.print(pitchOutput); Serial.print('\t');
        Serial.print("Roll Output: "); Serial.println(rollOutput);
        
        int angleOne = 90 + pitchOutput * cos(0) + rollOutput * sin(0);
        int angleTwo = 90 + pitchOutput * cos(2 * PI / 3) + rollOutput * sin(2 * PI / 3);
        int angleThree = 90 + pitchOutput * cos(4 * PI / 3) + rollOutput * sin(4 * PI / 3);
        
        if (angleOne < 0) angleOne = 0;
        if (angleOne > 180) angleOne = 180;
        fin.setFinPos(0, angleOne);

        if (angleTwo < 0) angleTwo = 0;
        if (angleTwo > 180) angleTwo = 180;
        fin.setFinPos(1, angleTwo);

        if (angleThree < 0) angleThree = 0;
        if (angleThree > 180) angleThree = 180;
        fin.setFinPos(2, angleThree);

        flightLogger.finLogger(millis(), 0, angleOne);
        flightLogger.finLogger(millis(), 1, angleTwo);
        flightLogger.finLogger(millis(), 2, angleThree);

        flightLogger.quatLogger(millis(), q2.w(), q2.x(), q2.y(), q2.z(), error.w(), error.x(), error.y(), error.z(), pitch, roll, pitchOutput, rollOutput);
    }
}