#include <Arduino.h>

#include <SPI.h>
#include <mcp_can.h>

#include "LoopTimer.h"

#include "CANApplication.h"

#include "ECU280Frame.h"
#include "Lights470Frame.h"
#include "Airbag050Frame.h"
#include "VehicleSpeed5A0Frame.h"
#include "Engine480Frame.h"
#include "ABS1A0Frame.h"
#include "DefaultFrame.h"
#include "TraceFrame.h"
#include "EngineDA0Frame.h"
#include "Immobilizer3D0Frame.h"
#include "MotorSpeed320Frmae.h"

MCP_CAN CAN(9);

CANApplication app(CAN);

ECU280Frame ecu280Frame;
Lights470Frame lightframe;
Airbag050Frame airbagFrame;
VehicleSpeed5A0Frame vehicleSpeed;
Engine480Frame engine;
ABS1A0Frame absFrame;
DefaultFrame defaultFrame;
TraceFrame traceFrame;
EngineDA0Frame engine2;
Immobilizer3D0Frame immobilizer;
MotorSpeed320Frame motorSpeed;

LoopTimer timer1Hz(1000);
LoopTimer timer5Hz(200);
LoopTimer timer10Hz(100);
LoopTimer timer20Hz(50);
LoopTimer timer50Hz(20);
LoopTimer timer100Hz(10);

void setup() {
    Serial.begin(9600);
    Serial.println("started setup");

    byte result = CAN.begin(CAN_500KBPS);
    if (result == CAN_OK) {
        Serial.println("CAN did start");
    } else {
        Serial.println("CAN did not start");
    }

    app.setup();

    Serial.println("completed setup");
}

void loop()
{
    byte result = CAN.checkReceive();
    if (result == CAN_MSGAVAIL) {
        app.receive(traceFrame);
    }

    ecu280Frame.setRpm(800);

    float speed = 20.0;
    vehicleSpeed.setSpeedMph(speed);
    absFrame.setSpeed(speed * 0.62 * 1.4285 * 256);
    motorSpeed.setSpeed(speed * 0.62 * 1.4285 * 256);

    vehicleSpeed.setAbsWarning(false);
    vehicleSpeed.setOffroadWarning(false);

//    lightframe.setInstrumentBacklightBrightness(127);
    lightframe.setFoglamp(false);
    lightframe.setHighbeam(false);
    lightframe.setLowBatteryWarning(false);
//    lightframe.setDoorAjar(1);

    engine.setFuelCapNotTight(false);

    airbagFrame.setSeatbeltWarning(false);

    // cited in examples, but don't appear to do anything on the instrument cluster

// minimal vehicle speed PGNs: engine2, vehiclespeed, absframe

    if (timer100Hz.event()) { // 1A0, 4A0
    }
    if (timer50Hz.event()) { // 280
//        app.send(immobilizer);
        app.send(engine2);

//        app.send(motorSpeed);
//        app.send(ecu280Frame);
        app.send(vehicleSpeed);
        app.send(absFrame);
//        app.send(airbagFrame);
    }
    if (timer10Hz.event()) { // 35B, 5A0, 621, 727
    }
    if (timer5Hz.event()) {
//        app.send(lightframe);
//        app.send(engine);
    }
    if (timer1Hz.event()) {
    }

//    app.send(defaultFrame);

    app.loop();

    delay(1);
}
