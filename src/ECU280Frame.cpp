#include "ECU280Frame.h"

ECU280Frame::ECU280Frame() : BaseFrame(0x280, 0, &frame) {
}

ECU280Frame::~ECU280Frame() {
}

void ECU280Frame::setRpm(unsigned short rpm) {
    frame.rpm = rpm * 4;
}
