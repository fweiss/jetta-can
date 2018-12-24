#include <Arduino.h>

#include <SPI.h>
#include <mcp_can.h>

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

    // cited in examples, but don't appear to do anything on the instrument cluster
    app.send(engine2);
    app.send(immobilizer);
}

void loop()
{
    byte result = CAN.checkReceive();
    if (result == CAN_MSGAVAIL) {
        app.receive(traceFrame);
    }

    ecu280Frame.setRpm(3200);

    vehicleSpeed.setSpeedMph(120.0);
    vehicleSpeed.setAbsWarning(false);
    vehicleSpeed.setOffroadWarning(false);

    lightframe.setInstrumentBacklightBrightness(127);
    lightframe.setFoglamp(false);
    lightframe.setHighbeam(false);
    lightframe.setLowBatteryWarning(false);
//    lightframe.setDoorAjar(1);

    engine.setFuelCapNotTight(false);

    airbagFrame.setSeatbeltWarning(false);

    app.send(airbagFrame);
    app.send(engine);
    app.send(lightframe);
    app.send(vehicleSpeed);
    app.send(ecu280Frame);
    app.send(absFrame);
//    app.send(defaultFrame);

    delay(100);
}
