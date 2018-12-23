#include <ABS1A0Frame.h>

ABS1A0Frame::ABS1A0Frame() : BaseFrame(0x1a0, 0) {
}

ABS1A0Frame::~ABS1A0Frame() {
}

unsigned char* ABS1A0Frame::getBytes() {
    return (unsigned char*)&frame;
}

