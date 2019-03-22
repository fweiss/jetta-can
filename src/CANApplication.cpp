#include "CANApplication.h"

#include <Arduino.h>

CANApplication::CANApplication(MCP_CAN& can) :
 timer1Hz(1000),
 timer5Hz(200),
 timer10Hz(100),
 timer20Hz(50),
 timer50Hz(20),
 timer100Hz(10),
 signal1Hz(1000)
{
    this->can = can;
}

void CANApplication::setup() {

}
void CANApplication::loop() {
    loopReceive();
    loopSignals();
//    loopTransmitDistance();
//    loopTransmitSpeed();
    loopTransmit();
//    loopTransmitQuery();
}

void CANApplication::loopTransmitDistance() {
    int speed = 102.0 / 0.0075;
    int distance_multiplier = 1;

    int distance_adder = 1000; //speed * distance_multiplier;
//    distance_counter += distance_adder;
//    if (distance_counter > distance_adder) {
//        distance_counter = 0;
//    }
    motorSpeed320.setSpeed(speed * 100);
    vehicleSpeed5A0.setSpeedRaw(speed);
    vehicleSpeed5A0.setDistanceTraveled(distance_counter);
    abs_1A0.setSpeed(speed);


    if (timer100Hz.event()) { // 1A0, 4A0
    }
    if (timer50Hz.event()) { // 280
//        send(motorSpeed320);
        send(vehicleSpeed5A0);
        send(abs_1A0);

//        send(engineDA0);
    }
    if (timer1Hz.event()) {
        distance_counter = 1;
    }
}

void CANApplication::loopTransmitQuery() {
    if (timer1Hz.event()) {
//        byte data[] = { 0x02, 0x01, 0x0c, 0, 0, 0, 0, 0 };
        byte data[] = { 0x0200, 0x1f, 0xc0, 0, 0, 0, 0, 0 };
        BaseFrame frame(0x7DF, 0, data);
        send(frame);
    }
}

void CANApplication::send(BaseFrame& frame) {
//    printSendTrace(frame);

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
    ecu280Frame.setRpm(2200);

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
    lightframe.setDoorAjar(0, false);

    engine.setFuelCapNotTight(false);

    airbagFrame.setSeatbeltWarning(false);

    if (signal1Hz.event()) {
        vehicleSpeed5A0.setDistanceTraveled(distance_counter);
    }
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
    int speed = 120.0 / 0.0075;
    int distance_multiplier = 2;

    int distance_adder = speed * distance_multiplier;
    distance_counter += distance_adder;
    if (distance_counter > distance_adder) {
        distance_counter = 0;
    }
    motorSpeed320.setSpeed(speed * 100);
    vehicleSpeed5A0.setSpeedRaw(speed);
    vehicleSpeed5A0.setDistanceTraveled(distance_counter);
    abs_1A0.setSpeed(speed);


    if (timer100Hz.event()) { // 1A0, 4A0
    }
    if (timer50Hz.event()) { // 280
        send(motorSpeed320);
        send(vehicleSpeed5A0);
        send(abs_1A0);

//        send(engineDA0);
    }
    if (timer10Hz.event()) { // 35B, 5A0, 621, 727
    }
    if (timer5Hz.event()) {
    }
    if (timer1Hz.event()) {
    }
}

void CANApplication::receive(BaseFrame& frame) {
    bool showTrace = true;
    unsigned short traceId = 0x60e;
    // following are emitted by cluster
    unsigned short exclude[] = { 0x320, 0x420, 0x621, 0x62d, 0x727,
    0x520, 0x51a, 0x62b, 0x629, 0x52a, 0x5d2, 0x62e, 0x5f3, 0x60e };

    unsigned long id;
    byte ext;
    byte rtr;
    byte length;
    byte buffer[512];
    byte status;

    byte rxTxStatus = can.readRxTxStatus();
    status = can.readMsgBufID(rxTxStatus, &id, &ext, &rtr, &length, buffer);

    boolean block = false;
    for (unsigned short xid : exclude) {
        if (xid == id) {
            block = true;
        }
    }

    if (! block) {
//    if (showTrace && (traceId == 0 || id == traceId)) {
        printReceiveTrace(id, ext, rtr, length, buffer);
    }
}

void CANApplication::printReceiveTrace(unsigned short id, byte ext, byte rtr, byte length, byte* buffer) {
    Serial.print(millis());
    Serial.print(": received id: ");
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

void CANApplication::printSendTrace(BaseFrame& frame) {
    Serial.print(millis());
    Serial.print(": transmit id: ");
    Serial.print(frame.id, HEX);
    Serial.print(" ext: ");
    Serial.print(frame.ext, HEX);
    Serial.print(" rtr: ");
    Serial.print(frame.rtr, HEX);
    Serial.print(" length: ");
    Serial.print(frame.length);
    Serial.print(" data:");
    for (int i=0; i<frame.length; i++) {
        Serial.print(" ");
        Serial.print(frame.data[i], HEX);
    }
    Serial.println();
}

