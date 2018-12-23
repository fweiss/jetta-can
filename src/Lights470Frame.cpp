#include <Lights470Frame.h>

Lights470Frame::Lights470Frame() : BaseFrame(0x470, 0) {
}

Lights470Frame::~Lights470Frame() {
}

unsigned char* Lights470Frame::getBytes() {
    return (unsigned char*)&frame;
}

void Lights470Frame::setHighbeam(bool onOff) {
    frame.highbeam = onOff;
}

void Lights470Frame::setFoglamp(bool onOff) {
    frame.foglamp = onOff;
}

void Lights470Frame::setDoorAjar(unsigned char index) {
    unsigned char* raw = getBytes();
    raw[1] |= 1 << index;
}
