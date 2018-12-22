#pragma once

// fixme decouple
#include "mcp_can.h"

//#include <functional>
//
//typedef std::function<void(unsigned long, unsigned char, unsigned char, unsigned char*)> SendMessage;


class ECU280Frame
{
public:
    ECU280Frame();
    virtual ~ECU280Frame();

    const unsigned long id = 0x280;
    const byte ext = 0;

    void setRpm(unsigned short rpm);
    const unsigned char* getBytes();
    void sendFrame(MCP_CAN can);
private:
    struct {
        // byte 0
        unsigned char : 4;
        unsigned char lowIdleSwitch : 1; // acc not pressed
        unsigned char : 2;
        unsigned char clutchSwitch : 1; // clutch not pressed
        unsigned char byte1 : 8;
        // byte 2, 3
        unsigned short rpm : 16;
        unsigned char byte4 : 8;
        unsigned char accelatorPosition : 8;
        unsigned char byte6 : 8;
        unsigned char byte7 : 8;
    } frame;
};
