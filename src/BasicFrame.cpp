#include "BasicFrame.h"

BasicFrame::BasicFrame(const char* name, unsigned long id) {
    this->id = id;
    this->name = name;
}

BasicFrame::~BasicFrame() {
    // TODO Auto-generated destructor stub
}

byte BasicFrame::send(MCP_CAN can) {
    const byte highbeam = B01000000;
    const byte foglamp = B00100000;
    byte lightMode = 0;

    // hmm non-zero displays door, but 32 doesn't
    // maybe 5 LSB bits refer to 4 doors + trunk?
    const byte trunklidAjar = B00100000;
    const byte doorAjar = B00010000;
    byte ajar = 0; //trunklidAjar | doorAjar; // trunk ajar light implemented?

    byte backlight = 0; // B00000001=fade off

    byte turnsignal = 0; // left=B00000001, right=B00000010, with sound

    byte key_battery = B10000000; // low key battery shown in LCD, over mileage

    const byte checkLamp = B00010000; // light bulb signal
    const byte checkClutch = B00000001; // lcd P/N indicator
    byte check_clutch = 0;

    byte message[8] = { turnsignal, ajar, backlight, 0, check_clutch, key_battery, 0, lightMode };

    byte status;
    byte ext = 0;
    status = can.sendMsgBuf(id, ext, sizeof(message), message);
    if (status == CAN_OK) {
        Serial.print("send ");
        Serial.print(name);
        Serial.println(" OK");
    } else {
        Serial.print("send error: ");
        Serial.println(status);
    }
    return status;
}
