#include "Arduino.h"

#include <SPI.h>
#include "mcp_can.h"
#include "BasicFrame.h"
#include "AirbagFrame.h"

MCP_CAN CAN(9);

BasicFrame indicators("Indicators", 0x470);
AirbagFrame airbag;

const unsigned long speedCanId = 0x04;
const unsigned long rpmCanId = 0x05;

void traceReceive() {
    unsigned long id;
    byte ext;
    byte rtr;
    byte length;
    byte buffer[512];
    byte status;

    byte rxTxStatus = CAN.readRxTxStatus();
    status = CAN.readMsgBufID(rxTxStatus, &id, &ext, &rtr, &length, buffer);

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

void writeTachometer(unsigned long rpm) {
    byte message[8] = { 0x49, 0x0E, 0xCC, 0x0D, 0x0e, 0x00, 0x1B, 0x0E };
    unsigned short *zz = (unsigned short*)&message[2];

    byte status;
    unsigned long id = 0x280;
    byte ext = 0;
    *zz = rpm * 4;
//    message[7] = 255;

    status = CAN.sendMsgBuf(id, ext, sizeof(message), message);
    if (status == CAN_OK) {
        Serial.println("send OK");
    } else {
        Serial.print("send error: ");
        Serial.println(status);
    }
}

#define lo8(x) (x & 0xFF)
#define hi8(x) (x >> 8)

unsigned short distance_counter = 40;

void writeSpeed(byte kmph) {
//    byte message[8] = { 0,0,0,0,0,0,0,0 };
    byte speedL = 0;
    byte speedH = 50;

    const byte abs = B0000001;
    const byte offroad = B00000010;
    const byte tirePressure = B00001000;
    const byte handbrake = B00000100; // not implemented
    byte drive_mode = 0;

    distance_counter += 40;
    byte message[8] = { 0xFF, speedL, speedH, drive_mode, 0x00, lo8(distance_counter), hi8(distance_counter), 0xad };

    message[1] = 100;

    byte status;
//    unsigned long id = 0x320; // motor speed?
    unsigned long id = 0x5A0;
    byte ext = 0;

    status = CAN.sendMsgBuf(id, ext, sizeof(message), message);
    if (status == CAN_OK) {
        Serial.println("send speed OK");
    } else {
        Serial.print("send error: ");
        Serial.println(status);
    }

}

//void writeIndicators() {
//    const byte highbeam = B01000000;
//    const byte foglamp = B00100000;
//    byte lightMode = highbeam + foglamp;
//
//    // hmm non-zero displays door, but 32 doesn't
//    // maybe 5 LSB bits refer to 4 doors + trunk?
//    const byte trunklidAjar = B00100000;
//    const byte doorAjar = B00010000;
//    byte ajar = 1; //trunklidAjar | doorAjar; // trunk ajar light implemented?
//
//    byte backlight = 0; // B00000001=fade off
//
//    byte turnsignal = 0; // left=B00000001, right=B00000010, with sound
//
//    byte key_battery = B10000000; // low key battery shown in LCD, over mileage
//
//    const byte checkLamp = 0; //B00010000; // light bulb signal
//    const byte checkClutch = 0; //B00000001; // lcd P/N indicator
//    byte check_clutch = checkLamp | checkClutch;
//
//    byte message[8] = { turnsignal, ajar, backlight, 0, check_clutch, key_battery, 0, lightMode };
//
//    byte status;
//    unsigned long id = 0x470;
//    byte ext = 0;
//    status = CAN.sendMsgBuf(id, ext, sizeof(message), message);
//    if (status == CAN_OK) {
//        Serial.println("send OK");
//    } else {
//        Serial.print("send error: ");
//        Serial.println(status);
//    }
//}

void writeEngine() {
    const byte engineControlMalfunction = B00000100;
//    const byte waterTemp = B00010000;
    byte engine = 0;

    const byte fuelCapNotTight = B00010000;
    byte dieselPreheat = 0;

    byte message[8] = { 0, engine, 0, 0, 0, dieselPreheat, 0, 0 };

    byte status;
    unsigned long id = 0x480;
    byte ext = 0;
    status = CAN.sendMsgBuf(id, ext, sizeof(message), message);
    if (status == CAN_OK) {
        Serial.println("send OK");
    } else {
        Serial.print("send error: ");
        Serial.println(status);
    }
}

void writeAbs() {
    byte speedL = 50;
    byte speedH = 50;
    byte message[8] = { 0x18, speedL, speedH, 0x00, 0xfe, 0xfe, 0x00, 0xff };
    byte status;
    unsigned long id = 0x1A0;
    byte ext = 0;

    status = CAN.sendMsgBuf(id, ext, sizeof(message), message);
    if (status == CAN_OK) {
        Serial.println("send OK");
    } else {
        Serial.print("send error: ");
        Serial.println(status);
    }

}

void setup() {
    Serial.begin(115700);
    Serial.println("started setup");

    byte result = CAN.begin(CAN_500KBPS);
    if (result == CAN_OK) {
        Serial.println("CAN did start");
    } else {
        Serial.println("CAN did not start");
    }

    Serial.println("completed setup");
}

void loop()
{
    byte result = CAN.checkReceive();
    if (result == CAN_MSGAVAIL) {
        unsigned char len = 0;
        unsigned char buf[8];

//        CAN.readMsgBuf(&len, buf);
//        Serial.print("rxtxstatus: ");
//        Serial.println(rxTxStatus);

//        traceReceive();
    }
    writeTachometer(1800);
    writeSpeed(45);
    writeAbs();
//    writeIndicators();
    indicators.send(CAN);
    writeEngine();
    airbag.send(CAN);

    delay(10);
}
