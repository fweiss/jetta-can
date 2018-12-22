#include <ECU280Frame.h>

ECU280Frame::ECU280Frame() {
    //    byte message[8] = { 0x49, 0x0E, 0xCC, 0x0D, 0x0e, 0x00, 0x1B, 0x0E };
}

ECU280Frame::~ECU280Frame() {
}

void ECU280Frame::setRpm(unsigned short rpm) {
    frame.rpm = rpm * 4;
}

const unsigned char* ECU280Frame::getBytes() {
    return (unsigned char*)&frame;
}

void ECU280Frame::sendFrame(MCP_CAN can) {
    byte status = can.sendMsgBuf(id, ext, 8, (unsigned char*)&frame);
    if (status == CAN_OK) {
        Serial.println("send OK");
    } else {
        Serial.print("send error: ");
        Serial.println(status);
    }

}
