#pragma once

#include <BaseFrame.h>

class ABS1A0Frame: public BaseFrame {
public:
    ABS1A0Frame();
    virtual ~ABS1A0Frame();

    virtual const unsigned char* getBytes() override;
private:
    struct {
        //byte 0
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
