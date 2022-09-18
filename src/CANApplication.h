#pragma once

#include <frame/ABS1A0Frame.h>
#include <frame/Airbag050Frame.h>
#include <frame/BaseFrame.h>
#include <frame/DefaultFrame.h>
#include <frame/ECU280Frame.h>
#include <frame/Engine480Frame.h>
#include <frame/EngineDA0Frame.h>
#include <frame/Immobilizer3D0Frame.h>
#include <frame/MotorSpeed320Frmae.h>
#include <frame/TraceFrame.h>
#include <frame/VehicleSpeed5A0Frame.h>
#include <frame/SnortXXXFrame.h>
#include "mcp_can.h"

#include "LoopTimer.h"
#include "frame/Lights470Frame.h"

class CANApplication {
public:
    CANApplication(MCP_CAN& can);
    virtual ~CANApplication() { }

    void setup();
    void loop();

    void send(BaseFrame& frame);
    void receive(BaseFrame& frame);
private:
    MCP_CAN can;

    void loopReceive();
    void loopSignals();
    void loopTransmit();
    void loopTransmitSpeed();
    void loopTransmitQuery();
    void loopTransmitDistance();

    void printSendTrace(BaseFrame& frame);
    void printReceiveTrace(unsigned short id, byte ext, byte rtr, byte length, byte* buffer);

    ECU280Frame ecu280Frame;
    Lights470Frame lightframe;
    Airbag050Frame airbagFrame;
    VehicleSpeed5A0Frame vehicleSpeed5A0;
    Engine480Frame engine;
    ABS1A0Frame abs_1A0;
    DefaultFrame defaultFrame;
    TraceFrame traceFrame;
    EngineDA0Frame engineDA0;
    Immobilizer3D0Frame immobilizer;
    MotorSpeed320Frame motorSpeed320;
    SnortXXXFrame snortXXXFrame;

    LoopTimer timer1Hz;
    LoopTimer timer5Hz;
    LoopTimer timer10Hz;
    LoopTimer timer20Hz;
    LoopTimer timer50Hz;
    LoopTimer timer100Hz;
    LoopTimer signal1Hz;

    unsigned short distance_counter;
};
