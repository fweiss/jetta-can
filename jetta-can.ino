#include "Arduino.h"

#include <SPI.h>
#include "mcp_can.h"

MCP_CAN CAN(9);

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
    *zz = rpm * 24;

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
    writeTachometer(100);
    delay(100);
}
