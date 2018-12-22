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

    virtual void send(MCP_CAN can) = 0;
    virtual const unsigned char* getBytes() = 0;
protected:
    void sendFrame(MCP_CAN can);
private:
    unsigned long id;
    byte ext;
};
