#include "SnortXXXFrame.h"

SnortXXXFrame::SnortXXXFrame(int const pid) : BaseFrame(pid, 0, &frame) {

}

// fixme initialize to frame[0] = 0x01
void SnortXXXFrame::shift() {
    scan <<= 1;
    if ((scan & 0xff) == 0) {
        frame[index] = scan & 0xff;
        scan = 0x01;
        index = (index + 1) % 8;
    }
    frame[index] = scan & 0xff;
}
