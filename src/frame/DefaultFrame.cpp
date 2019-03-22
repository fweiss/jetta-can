#include <frame/DefaultFrame.h>

DefaultFrame::DefaultFrame() : BaseFrame(0x00, 0, &frame) {
    unsigned char* raw = getBytes();

//    raw[0] = 0xff;
//    raw[1] = 0xff;
//    raw[3] = 0xff;
//    raw[4] = 0xff;
//    raw[5] = 0xff;
//    raw[6] = 0xff;
//    raw[7] = 0xff;
}
