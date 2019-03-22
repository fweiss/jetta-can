#include "Lights470Frame.h"

Lights470Frame::Lights470Frame() : BaseFrame(0x470, 0, &frame) {
}

void Lights470Frame::setHighbeam(bool onOff) {
    frame.highbeam = onOff;
}

void Lights470Frame::setFoglamp(bool onOff) {
    frame.foglamp = onOff;
}

void Lights470Frame::setDoorAjar(unsigned char index, bool onOff) {
    unsigned char mask = 1 << index;
    unsigned char* raw = getBytes();
    if (onOff) {
        raw[1] |= mask;
    } else {
        raw[1] &= ~ mask;
    }
}
