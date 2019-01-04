#pragma once

#include "BaseFrame.h"

class DefaultFrame: public BaseFrame {
public:
    DefaultFrame();
    virtual ~DefaultFrame();

//    virtual const unsigned char* getBytes() override;
private:
    struct {
        // byte 0
        unsigned char : 8;
        // byte 1
        unsigned char : 8;
        // byte 2
        unsigned char : 8;
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
