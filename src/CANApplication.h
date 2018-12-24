#pragma once

#include "mcp_can.h"

#include "BaseFrame.h"

class CANApplication {
public:
    CANApplication(MCP_CAN can);
    virtual ~CANApplication();

    void send(BaseFrame& frame);
    void receive(BaseFrame& frame);
private:
    MCP_CAN can;
};
