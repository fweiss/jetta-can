#pragma once

#include "mcp_can.h"

class BasicFrame {
public:
    BasicFrame(const char* name, unsigned long id);
    virtual ~BasicFrame();

    unsigned long getId() { return this->id; }
    byte send(MCP_CAN can);

private:
    const char* name;
    unsigned long id;
    byte message[8];
};
