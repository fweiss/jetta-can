#include "CANApplication.h"

#include <Arduino.h>

CANApplication::CANApplication(MCP_CAN& can) :
 timer1Hz(1000),
 timer5Hz(200),
 timer10Hz(100),
 timer20Hz(50),
 timer50Hz(20),
 timer100Hz(10)
{
    this->can = can;
}

void CANApplication::setup() {

}
void CANApplication::loop() {
    loopReceive();
    loopSignals();
    loopTransmit();
}

void CANApplication::send(BaseFrame& frame) {
//    printSendTrace(frame.id);

    byte status = can.sendMsgBuf(frame.id, frame.ext, 8, frame.getBytes(), true);
    if (status == CAN_OK) {
//        Serial.println("send OK");
    } else {
        Serial.print("id: 0x");
        Serial.print(frame.id, HEX);
        Serial.print(" send error: ");
        Serial.println(status);
    }
}

void CANApplication::loopReceive() {
    byte result = can.checkReceive();
    if (result == CAN_MSGAVAIL) {
        receive(traceFrame);
    }
}

void CANApplication::loopSignals() {
    ecu280Frame.setRpm(800);

    float speed = 20.0;
    vehicleSpeed.setSpeedMph(speed);
    absFrame.setSpeed(speed * 0.62 * 1.4285 * 256);
    motorSpeed.setSpeed(speed * 0.62 * 1.4285 * 256);

    vehicleSpeed.setAbsWarning(false);
    vehicleSpeed.setOffroadWarning(false);

    lightframe.setInstrumentBacklightBrightness(127);
    lightframe.setFoglamp(false);
    lightframe.setHighbeam(false);
    lightframe.setLowBatteryWarning(false);
    lightframe.setDoorAjar(3);

    engine.setFuelCapNotTight(false);

    airbagFrame.setSeatbeltWarning(false);
}

void CANApplication::loopTransmit() {
// minimal vehicle speed PGNs: engine2, vehiclespeed, absframe

    if (timer100Hz.event()) { // 1A0, 4A0
    }
    if (timer50Hz.event()) { // 280
//        app.send(immobilizer);
        send(engine2);

//        send(motorSpeed);
        send(ecu280Frame);
        send(vehicleSpeed);
        send(absFrame);
//        send(airbagFrame);
    }
    if (timer10Hz.event()) { // 35B, 5A0, 621, 727
    }
    if (timer5Hz.event()) {
        send(lightframe);
//        send(engine);
    }
    if (timer1Hz.event()) {
    }

//    send(defaultFrame);
}

void CANApplication::receive(BaseFrame& frame) {
    bool showTrace = false;

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

void CANApplication::printSendTrace(unsigned long id) {
    Serial.print(millis());
    Serial.print(": ");
    Serial.println(id, HEX);
}

