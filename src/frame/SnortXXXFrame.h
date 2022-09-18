#pragma once

#include "BaseFrame.h"

class SnortXXXFrame : public BaseFrame {
public:
    SnortXXXFrame();
    virtual ~SnortXXXFrame() {}

public:
    unsigned char frame[8];
};
