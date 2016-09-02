#include <Arduino.h>

// Activate debug:
#ifndef WITH_DEBUG
#define WITH_DEBUG
#endif
// Use StringUtil library
#define USE_STRING_UTIL

#include <DebugUtil.h>

void setup() {
    DEBUG_SERIAL_BEGIN(9600);
}

void loop() {
    // 1970-01-01 00:00:00: UseStringUtil.ino:18 loop - float=0.12
    DEBUG("float=%.2f", 0.123456);
    delay(1000);
}
