#pragma once

#include <frame/BaseFrame.h>

class Airbag050Frame : public BaseFrame {
public:
    Airbag050Frame();

    void setSeatbeltWarning(bool onOff) { frame.seatbeltWarning = onOff; }
private:
    struct {
        // byte 0
        unsigned char : 8;
        // byte 1
        unsigned char : 8;
        // byte 2
        unsigned char : 2;
        unsigned char seatbeltWarning : 1; // plus chime
        unsigned char : 5;
        // byte 3
        unsigned char : 8;
    } frame;
};
