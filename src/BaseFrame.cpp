#include "BaseFrame.h"

// mapping the subclass bit field structure to array of bytes.
// in the derived class, the pointer to frame structure is automatically cast to void*
// here the void* needs to be explicitly cast to the byte array data
// a more natural way is union, but not sure how that can be inherited
// using unsigned char* getBytes() may be more flexible as it can be computed,
// but the bitfield approach requires less boiler plate and no vtable
BaseFrame::BaseFrame(const unsigned long id, const unsigned char ext, void* data) : id(id), ext(ext) {
    this->data = (const unsigned char *)data;
}
