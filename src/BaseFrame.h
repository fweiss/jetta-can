#pragma once

class BaseFrame {
public:
    BaseFrame(const unsigned long id, const unsigned char ext, void* data);

    const unsigned long id;
    const unsigned char ext;
    const unsigned char* data;

    const unsigned char* getBytes() { return data; }
};
