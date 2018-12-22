#include <AirbagFrame.h>

AirbagFrame::AirbagFrame() : BasicFrame("Airbag", 0x050) {
}

AirbagFrame::~AirbagFrame() {
}

byte AirbagFrame::send(MCP_CAN can) {
    // this doesn't remove the airbag warning lamp
    byte temp_seat_belt = 0;

    byte message[8] = { 0x00, 0x80, temp_seat_belt, 0x00, 0x00, 0x00, 0x00, 0x00 };

    return sendMessage(can, message);
}

