#include "Immobilizer3D0Frame.h"

Immobilizer3D0Frame::Immobilizer3D0Frame() : BaseFrame(0x3d0, 0, &frame) {
    unsigned char* raw = getBytes();

    raw[1] = 0x80;
}
