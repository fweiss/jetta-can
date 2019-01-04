#include "EngineDA0Frame.h"

EngineDA0Frame::EngineDA0Frame() : BaseFrame(0xda0, 0, &frame) {
    // supposably engine on and ESP enabled
    unsigned char* raw = getBytes();
    raw[0] = 0x01;
    raw[1] = 0x80;
//    raw[2] = 254;
//    raw[3] = 254;
//    raw[4] = 254;
//    raw[5] = 254;
}

EngineDA0Frame::~EngineDA0Frame() {
}
