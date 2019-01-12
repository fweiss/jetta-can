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
    loopTransmitSpeed();
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
    vehicleSpeed5A0.setSpeedMph(speed);
    abs_1A0.setSpeed(speed * 0.62 * 1.4285 * 256);
    motorSpeed320.setSpeed(speed * 0.62 * 1.4285 * 256);

    vehicleSpeed5A0.setAbsWarning(false);
    vehicleSpeed5A0.setOffroadWarning(false);

    lightframe.setInstrumentBacklightBrightness(127);
    lightframe.setFoglamp(false);
    lightframe.setHighbeam(false);
    lightframe.setLowBatteryWarning(false);
    lightframe.setDoorAjar(3);

    engine.setFuelCapNotTight(false);

    airbagFrame.setSeatbeltWarning(false);
}

void CANApplication::loopTransmit() {
    if (timer100Hz.event()) { // 1A0, 4A0
    }
    if (timer50Hz.event()) { // 280
        send(immobilizer);
        send(engineDA0);

        send(motorSpeed320);
        send(ecu280Frame);
        send(vehicleSpeed5A0);
        send(abs_1A0);
        send(airbagFrame);
    }
    if (timer10Hz.event()) { // 35B, 5A0, 621, 727
    }
    if (timer5Hz.event()) {
        send(lightframe);
        send(engine);
    }
    if (timer1Hz.event()) {
    }

//    send(defaultFrame);
}

void CANApplication::loopTransmitSpeed() {
// minimal vehicle speed PGNs: engine_DA0, vehicleSpeed_5A0, abs_1A0

    if (timer100Hz.event()) { // 1A0, 4A0
    }
    if (timer50Hz.event()) { // 280
        send(engineDA0);
        send(vehicleSpeed5A0);
        send(abs_1A0);
    }
    if (timer10Hz.event()) { // 35B, 5A0, 621, 727
    }
    if (timer5Hz.event()) {
    }
    if (timer1Hz.event()) {
    }
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

