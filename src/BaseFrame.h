#pragma once

class BaseFrame {
public:
    BaseFrame(const unsigned long id, const unsigned char ext, void* data);
    BaseFrame(const unsigned long id, const unsigned char ext);
    virtual ~BaseFrame();

    const unsigned long id;
    const unsigned char ext;
    const unsigned char* data;

    virtual const unsigned char* getBytes() { return data; }
};
