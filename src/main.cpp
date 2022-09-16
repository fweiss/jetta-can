#include <Arduino.h>

#include <SPI.h>
#include <mcp_can.h>

#include "CANApplication.h"

// depending on the solder bridge configuration
// the Seeed Studio CAN Bus Shield v2 can use GPIO 9 or 10
// default bridge setting is 9
const byte mcpCanChipSelect = 9;

MCP_CAN CAN(mcpCanChipSelect);
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
