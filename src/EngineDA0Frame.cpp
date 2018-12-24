#include "EngineDA0Frame.h"

EngineDA0Frame::EngineDA0Frame() : BaseFrame(0xda0, 0) {
    // supposably engine on and ESP enabled
    unsigned char* raw = getBytes();
    raw[0] = 0x01;
    raw[1] = 0x80;
}

EngineDA0Frame::~EngineDA0Frame() {
}
