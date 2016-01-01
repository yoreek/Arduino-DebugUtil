#include <Arduino.h>

// Activate debug:
#define WITH_DEBUG

#include <DebugUtil.h>

void setup() {
    DEBUG_SERIAL_SETUP(9600);
}

void loop() {
    DEBUG("ramSize=%d, ramFree=%d", DebugUtil::ramSize(), DebugUtil::ramFree());
    delay(1000);
}
