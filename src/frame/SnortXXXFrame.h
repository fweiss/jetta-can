#pragma once

#include "BaseFrame.h"

class SnortXXXFrame : public BaseFrame {
public:
    SnortXXXFrame(int const pid);
    virtual ~SnortXXXFrame() {}

    void shift();

private:
    unsigned char frame[8];
    int index= 0;
    int scan = 0x80;
};
