#include <VehicleSpeed5A0Frame.h>

VehicleSpeed5A0Frame::VehicleSpeed5A0Frame() : BaseFrame(0x5a0, 0) {
    unsigned char* raw = getBytes();
}

VehicleSpeed5A0Frame::~VehicleSpeed5A0Frame() {
}

void VehicleSpeed5A0Frame::setSpeedMph(float mph) {
    // some empirical fiddling, but the guage may not be calibrated
    // kmh * 256 does seem to work
    frame.speed = mph * 0.62 * 1.4285 * 256;
    frame.distanceCounter += 40;
}

void VehicleSpeed5A0Frame::setDistanceTraveled(unsigned long distance) {
    frame.distanceCounter += distance;
}
