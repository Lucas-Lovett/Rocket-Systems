#ifndef LOGGER_H
#define LOGGER_H

#include <SD.h>

class logger {
    public:
        logger(int csPin);

        void finLogger(unsigned long timeStamp, int finIndex, float angle);
        void quatLogger(unsigned long timeStamp, float qw, float qx, float qy, float qz, float errorW, float errorX, float errorY, float errorZ, float pitch, float roll, float pitchOutput, float rollOutput);
        void begin();
    private:
        File finLogs;
        File quatLogs;
        int csPin;
};

#endif