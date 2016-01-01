#include <Arduino.h>

// Activate debug:
#define WITH_DEBUG
// Use StringUtil library
#define USE_STRING_UTIL

#include <DebugUtil.h>

void setup() {
    DEBUG_SERIAL_SETUP(9600);
}

void loop() {
    DEBUG("float=%.2f", 0.123456);
    delay(1000);
}
