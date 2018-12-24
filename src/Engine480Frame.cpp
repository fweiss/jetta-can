#include "Engine480Frame.h"

Engine480Frame::Engine480Frame() : BaseFrame(0x480, 0) {
}

Engine480Frame::~Engine480Frame() {
}

const unsigned char* Engine480Frame::getBytes() {
    return (unsigned char*)&frame;
}
