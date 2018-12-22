#include <Lights470Frame.h>

Lights470Frame::Lights470Frame() {

}

Lights470Frame::~Lights470Frame() {
}

void Lights470Frame::setHighbeam(bool onOff) {
    frame.highbeam = onOff;
}

void Lights470Frame::setFoglamp(bool onOff) {
    frame.foglamp = onOff;
}

void Lights470Frame::sendFrame(MCP_CAN can) {
    unsigned char* raw = (unsigned char*)&frame;

//    frame.turnSignalLeft = 1;
//    frame.turnSignalRight = 0;
//    frame.highbeam = 1;
//    frame.trunklidAjar = 1;
//    frame.doorAjar3 = 1;
//    frame.checkClutch = 1;
//    frame.lampOut = 1;
//    frame.keyBatteryLow = 1;

//    raw[3] = 0xff;

    byte status = can.sendMsgBuf(id, ext, 8, raw);
    if (status == CAN_OK) {
        Serial.println("send OK");
    } else {
        Serial.print("send error: ");
        Serial.println(status);
    }

}
