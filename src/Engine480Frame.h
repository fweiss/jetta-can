#pragma once

#include "BaseFrame.h"

class Engine480Frame : public BaseFrame {
public:
    Engine480Frame();
    virtual ~Engine480Frame();

    virtual const unsigned char* getBytes() override;

    void setFuelCapNotTight(bool onOff) { frame.fuelCapNotTight = onOff; }
private:
    struct {
        // byte 0
        unsigned char : 8;
        // byte 1
        unsigned char : 2;
        unsigned char engineControlMalfunction : 1; // aka "EPC"
        unsigned char : 2;
        unsigned char waterTemp : 1; // not implemented
        unsigned char : 2;
        // byte 2
        unsigned char : 8;
        // byte 3
        unsigned char : 8;
        // byte 4
        unsigned char : 8;
        // byte 5 diesel preheat
        unsigned char : 4;
        unsigned char fuelCapNotTight : 1;
        unsigned char : 3;
        // byte 6
        unsigned char : 8;
        // byte 7
        unsigned char : 8;
    } frame;
};
