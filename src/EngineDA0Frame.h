#pragma once

#include "BaseFrame.h"

class EngineDA0Frame: public BaseFrame {
public:
    EngineDA0Frame();
    virtual ~EngineDA0Frame();

//    virtual unsigned char* getBytes() { return (unsigned char*)&frame; }
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
