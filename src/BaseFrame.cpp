#include <BaseFrame.h>

BaseFrame::BaseFrame(const unsigned long id, const byte ext) {
    this-> id = id;
    this->ext = ext;
}

BaseFrame::~BaseFrame() {
}

void BaseFrame::send(MCP_CAN can) {
    byte status = can.sendMsgBuf(id, ext, 8, getBytes());
    if (status == CAN_OK) {
        Serial.println("send OK");
    } else {
        Serial.print("send error: ");
        Serial.println(status);
    }
}

// deprecated
void BaseFrame::sendFrame(MCP_CAN can) {
    byte status = can.sendMsgBuf(id, ext, 8, getBytes());
    if (status == CAN_OK) {
        Serial.println("send OK");
    } else {
        Serial.print("send error: ");
        Serial.println(status);
    }
}


