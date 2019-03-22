#include <frame/Airbag050Frame.h>

Airbag050Frame::Airbag050Frame() : BaseFrame(0x050, 0, &frame) {
    // message length = 4
}
