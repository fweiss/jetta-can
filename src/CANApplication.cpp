
#include <CANApplication.h>

CANApplication::CANApplication(MCP_CAN can) {
    this->can = can;
}

CANApplication::~CANApplication() {
}

void CANApplication::send(BaseFrame& frame) {
    byte status = can.sendMsgBuf(frame.id, frame.ext, 8, frame.getBytes());
    if (status == CAN_OK) {
        Serial.println("send OK");
    } else {
        Serial.print("send error: ");
        Serial.println(status);
    }
}
