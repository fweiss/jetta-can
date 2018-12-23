#include <DefaultFrame.h>

DefaultFrame::DefaultFrame() : BaseFrame(0xfff, 0) {
    unsigned char* raw = getBytes();
}

DefaultFrame::~DefaultFrame() {
}

unsigned char* DefaultFrame::getBytes() {
    return (unsigned char*)&frame;
}

