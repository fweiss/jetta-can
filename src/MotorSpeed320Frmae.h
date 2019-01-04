#pragma once

#include "BaseFrame.h"

class MotorSpeed320Frame: public BaseFrame
{
public:
    MotorSpeed320Frame();

    void setSpeed(float speed) { frame.speed = speed * 100; }
private:
    struct {
        // byte 0
        unsigned char : 8;
        // byte 1 and 2
        unsigned short speed : 16;
        // byte 3
        unsigned char : 8;
        // byte 4
        unsigned char : 8;
        // byte 5
        unsigned char : 8;
        // byte 6
        unsigned char : 8;
        // byte 7
        unsigned char : 8;
    } frame;
};
