#ifndef QUATERNION_H
#define QUATERNION_H

#include <HardwareSerial.h>

class quaternion {
    public:

        quaternion(float w, float x, float y, float z);
        quaternion(const quaternion& q1);

        float getRoll();
        float getPitch();
        float getYaw();

        float w() const {
            return qw;
        }
        float x() const {
            return qx;
        }
        float y() const {
            return qy;
        }
        float z() const {
            return qz;
        }

        float norm() const;
        void print() {
            Serial.print("W: "); Serial.print(qw, 10); Serial.print('\t');
            Serial.print("X: "); Serial.print(qx, 10); Serial.print('\t');
            Serial.print("Y: "); Serial.print(qy, 10); Serial.print('\t');
            Serial.print("Z: "); Serial.println(qz, 10);
        }

    private:
        float qw = 0.0f;
        float qx = 0.0f;
        float qy = 0.0f;
        float qz = 0.0f;
};

quaternion conj(const quaternion& q);
quaternion normalize(const quaternion& q);
quaternion vector(const quaternion& q);

quaternion operator*(const quaternion& q1, const quaternion& q2);
quaternion operator*(float M, const quaternion& q);
quaternion operator/(const quaternion& q1, float M);
quaternion operator+(const quaternion& q1, const quaternion& q2);
quaternion operator-(const quaternion& q1, const quaternion& q2);


#endif