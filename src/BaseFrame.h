#pragma once

class BaseFrame {
public:
    BaseFrame(const unsigned long id, const unsigned char ext);
    virtual ~BaseFrame();

    const unsigned long id;
    const unsigned char ext;

    virtual const unsigned char* getBytes() = 0;
};
