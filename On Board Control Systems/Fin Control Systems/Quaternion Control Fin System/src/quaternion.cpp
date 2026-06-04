#include "quaternion.h"

quaternion::quaternion(float w, float x, float y, float z) {
    qw = w;
    qx = x;
    qy = y;
    qz = z;
}

quaternion::quaternion(const quaternion& q1) {
    qw = q1.w();
    qx = q1.x();
    qy = q1.y();
    qz = q1.z();
}

float quaternion::getRoll() {
    return atan2(2.0 * (qz * qy + qw * qx), 1.0 - 2.0 * (qx * qx + qy * qy));
}

float quaternion::getPitch() {
    return asin(2.0 * (qy * qw - qz * qx));
}

float quaternion::getYaw() {
    return atan2(2.0 * (qz * qw + qx * qy), - 1.0 + 2.0 * (qw * qw + qx * qx));
}

float quaternion::norm() const {
    return(float) sqrt(qw* qw + qx * qx + qy * qy + qz * qz);
}

quaternion conj(const quaternion& q) {
    return quaternion(q.w(), -q.x(), -q.y(), -q.z());
}

quaternion normalize(const quaternion& q) {
    float n = q.norm();
    return quaternion((q.w() / n), (q.x() / n), (q.y() / n), (q.z() / n));
}

quaternion vector(const quaternion& q){
    return quaternion(0, q.x(), q.y(), q.z());
}

quaternion operator*(const quaternion& q1, const quaternion& q2) {
  float newW = q1.w() * q2.w() - q1.x() * q2.x() - q1.y() * q2.y() - q1.z() * q2.z();
  float newX = q1.w() * q2.x() + q1.x() * q2.w() + q1.z() * q2.y() - q1.y() * q2.z();
  float newY = q1.w() * q2.y() + q1.y() * q2.w() + q1.x() * q2.z() - q1.z() * q2.y();
  float newZ = q1.w() * q2.z() + q1.z() * q2.w() + q1.y() * q2.x() - q1.x() * q2.y();
  
  return quaternion(newW, newX, newY, newZ);;
}

quaternion operator*(float M, const quaternion &q) {
  return quaternion((q.w() * M), (q.x() * M), (q.y() * M), (q.z() * M));
}

quaternion operator/(const quaternion &q, float M) {
  return quaternion((q.w() / M), (q.x() / M), (q.y() / M), (q.z() / M));
}

quaternion operator+(const quaternion& q1, const quaternion& q2) {
  return quaternion((q1.w() + q2.w()), (q1.x() + q2.x()), (q1.y() + q2.y()), (q1.z() + q2.z()));
}

quaternion operator-(const quaternion& q1, const quaternion& q2) {
  return quaternion((q1.w() - q2.w()), (q1.x() - q2.x()), (q1.y() - q2.y()), (q1.z() - q2.z()));
}