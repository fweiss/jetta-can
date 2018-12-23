#include <Airbag050Frame.h>

Airbag050Frame::Airbag050Frame() : BaseFrame(0x050, 0) {
    // message length = 4
    frame.seatbeltWarning = 0;
}

Airbag050Frame::~Airbag050Frame() {
}

unsigned char* Airbag050Frame::getBytes() {
    return (unsigned char*)&frame;
}
