#pragma once

#include "mcp_can.h"

class BasicFrame {
public:
    BasicFrame(const char* name, unsigned long id);
    virtual ~BasicFrame();

    unsigned long getId() { return this->id; }
    virtual byte send(MCP_CAN can);
protected:
    byte sendMessage(MCP_CAN can, byte message[8]);
private:
    const char* name;
    unsigned long id;
    byte message[8];
};
