#pragma once

#include "BaseFrame.h"

class VehicleSpeed5A0Frame : public BaseFrame
{
public:
    VehicleSpeed5A0Frame();
    virtual ~VehicleSpeed5A0Frame();

//    virtual const unsigned char* getBytes() override { return (unsigned char*)&frame; }

    void setSpeedMph(float mph);
    void setDistanceTraveled(unsigned long distance);
    void setAbsWarning(bool onOff) { frame.abs = onOff; }
    void setOffroadWarning(bool onOff) { frame.offroad = onOff; }
private:
    struct {
        // byte 0
        unsigned char : 8;
        // byte 1 and 2
        unsigned short speed : 16;
        // byte 3
        unsigned char abs : 1;
        unsigned char offroad : 1;
        unsigned char handbrake : 1; // not implemented
        unsigned char tirePressureWarning : 1;
        unsigned char : 4;
        // byte 4
        unsigned char : 8;
        // byte 5 and 6
        unsigned short distanceCounter : 16;
        // byte 7
        unsigned char : 8;
    } frame;
};

