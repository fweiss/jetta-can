#pragma once

#include "BaseFrame.h"

class Lights470Frame : public BaseFrame {
public:
    Lights470Frame();

    const unsigned long id = 0x470;
    const unsigned char ext = 0;

    void setHighbeam(bool onOff);
    void setFoglamp(bool onOff);
    void setDoorAjar(unsigned char doorNumber, bool onOff);
    void setInstrumentBacklightBrightness(unsigned char brightness) { frame.instrumentBacklightBrightness = brightness; }
    void setLowBatteryWarning(bool onOff) { frame.lowBatteryWarning = onOff; }
private:
    struct {
        // byte 0
        unsigned char turnSignalLeft : 1;
        unsigned char turnSignalRight : 1;
        unsigned char : 5;
        unsigned char lowBatteryWarning : 1;
        // byte 1
        unsigned char doorAjar0 : 1; // implemented as or of the four door bits
        unsigned char doorAjar1 : 1;
        unsigned char doorAjar2 : 1;
        unsigned char doorAjar3 : 1;
        unsigned char trunklidAjar : 1; // trunk ajar light not implemented or is it 0x20?
        unsigned char : 3;
        // byte 2
        unsigned char instrumentBacklightBrightness : 7; // B00000001=fade off
        unsigned char : 1;
        // byte 3
        unsigned char : 8;
        // byte 4
        unsigned char checkClutch : 1; // lcd P/N indicator
        unsigned char : 3; // soem of these seem to reset check engine, tire pressure
        unsigned char lampOut : 1;
        unsigned char : 3;
        // byte 5
        unsigned char : 7;
        unsigned char keyBatteryLow : 1; // low key battery shown in LCD, over mileage
        // byte 6
        unsigned char : 8;
        // byte 7
        unsigned char : 5;
        unsigned char foglamp : 1;
        unsigned char highbeam : 1;
        unsigned char : 1;
    } frame;
};
