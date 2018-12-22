#pragma once

#include "BasicFrame.h"

class AirbagFrame : public BasicFrame {
public:
    AirbagFrame();
    virtual ~AirbagFrame();

    virtual byte send(MCP_CAN can) override;
};
