#include "Airbag050Frame.h"

Airbag050Frame::Airbag050Frame() : BaseFrame(0x050, 0, &frame) {
    // message length = 4
}

Airbag050Frame::~Airbag050Frame() {
}

//const unsigned char* Airbag050Frame::getBytes() {
//    return (unsigned char*)&frame;
//}
