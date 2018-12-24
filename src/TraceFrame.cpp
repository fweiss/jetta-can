#include "TraceFrame.h"

#include "Arduino.h"

TraceFrame::TraceFrame() : BaseFrame(0, 0) {
}

TraceFrame::~TraceFrame() {
}

const unsigned char* TraceFrame::getBytes() {
    return(unsigned char*)&frame;
}

void TraceFrame::print() {
}
