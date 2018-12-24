#include <Arduino.h>

class LoopTimer {
public:
    LoopTimer(unsigned long periodMillis) {
        this->periodMillis = periodMillis;
        this->nextMillis = millis() + periodMillis;
    }
    bool event() {
        unsigned long currentMillis = millis();
        if (currentMillis < nextMillis) {
            return false;
        } else {
            nextMillis = currentMillis + periodMillis;
            return true;
        }
    }
private:
    unsigned long periodMillis;
    unsigned long nextMillis;
};
