#pragma once

// fixme decouple
#include "mcp_can.h"

//#include <functional>
//
//typedef std::function<void(unsigned long, unsigned char, unsigned char, unsigned char*)> SendMessage;

class BaseFrame {
public:
    BaseFrame(const unsigned long id, const byte ext);
    virtual ~BaseFrame();

    const unsigned long id;
    const byte ext;

    void send(MCP_CAN can);
    virtual const unsigned char* getBytes() = 0;
protected:
    void sendFrame(MCP_CAN can);
};
