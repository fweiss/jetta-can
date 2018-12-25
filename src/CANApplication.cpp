#include "CANApplication.h"

// fixme should be ref, not copy?
CANApplication::CANApplication(MCP_CAN can) : slowTimer(1000){
    this->can = can;
}

void CANApplication::setup() {

}
void CANApplication::loop() {
    if (slowTimer.event()) {
//        Serial.println("slow");
    }
}

void CANApplication::send(BaseFrame& frame) {
    byte status = can.sendMsgBuf(frame.id, frame.ext, 8, frame.getBytes());
    if (status == CAN_OK) {
//        Serial.println("send OK");
    } else {
        Serial.print("id: 0x");
        Serial.print(frame.id, HEX);
        Serial.print(" send error: ");
        Serial.println(status);
    }
}

void CANApplication::receive(BaseFrame& frame) {
    bool showTrace = true;

    unsigned long id;
    byte ext;
    byte rtr;
    byte length;
    byte buffer[512];
    byte status;

    byte rxTxStatus = can.readRxTxStatus();
    status = can.readMsgBufID(rxTxStatus, &id, &ext, &rtr, &length, buffer);

    if (showTrace && id == 0x320) {
        Serial.print("received id: ");
        Serial.print(id, HEX);
        Serial.print(" ext: ");
        Serial.print(ext, HEX);
        Serial.print(" rtr: ");
        Serial.print(rtr, HEX);
        Serial.print(" length: ");
        Serial.print(length);
        Serial.print(" data:");
        for (int i=0; i<length; i++) {
            Serial.print(" ");
            Serial.print(buffer[i], HEX);
        }
        Serial.println();
    }
}
