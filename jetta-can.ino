#include "Arduino.h"

#include <SPI.h>
#include "mcp_can.h"

#include "CANApplication.h"

#include "ECU280Frame.h"
#include "Lights470Frame.h"
#include "Airbag050Frame.h"
#include "VehicleSpeed5A0Frame.h"
#include "Engine480Frame.h"

MCP_CAN CAN(9);

CANApplication app(CAN);

ECU280Frame ecu280Frame;
Lights470Frame lightframe;
Airbag050Frame airbagFrame;
VehicleSpeed5A0Frame vehicleSpeed;
Engine480Frame engine;

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

    ecu280Frame.setRpm(3200);
    app.send(ecu280Frame);

    vehicleSpeed.setSpeedMph(120.0);
    app.send(vehicleSpeed);

    writeAbs();

    lightframe.setFoglamp(true);
    app.send(lightframe);

    engine.setFuelCapNotTight(false);
    app.send(engine);

    airbagFrame.setSeatbeltWarning(false);
    app.send(airbagFrame);

    delay(10);
}
