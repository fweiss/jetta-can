#include <Arduino.h>

#include <SPI.h>
#include <mcp_can.h>

#include "CANApplication.h"

MCP_CAN CAN(9);
CANApplication app(CAN);

void setup() {
    Serial.begin(115200);
    Serial.println("started setup");

    byte result = CAN.begin(CAN_500KBPS);
    if (result == CAN_OK) {
        Serial.println("CAN did start");
    } else {
        Serial.println("CAN did not start");
    }

    app.setup();

    Serial.println("completed setup");
}

void loop()
{
    app.loop();
    delay(1);
}
