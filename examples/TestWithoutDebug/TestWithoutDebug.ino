#include <Arduino.h>

// Deactivate debug:
#undef WITH_DEBUG

#include <DebugUtil.h>

#ifndef MONITOR_BAUDRATE
#define MONITOR_BAUDRATE 9600
#endif

void setup() {
    DEBUG_SERIAL_BEGIN(MONITOR_BAUDRATE);
    DEBUG("setup");
}

void sleep() {
    delay(3000);
}

void loop() {
    DEBUG("simple test");

    DEBUG("param: %d", 123);

    DEBUG_EVERY(1000, "print every 1s param: %d", 123);

    DEBUG_EVERY(3000) {
        DEBUG("ramSize=%d, ramFree=%d", DebugUtil::ramSize(), DebugUtil::ramFree());
    }

    DEBUG_EVERY(1000) {
        int x = 123;
        Serial.println(x);
    }

    DEBUG_EVERY_WITH_DELAY(1000, 5000) {
        DEBUG("print every 1s with delay 5s");
    }

    DEBUG_EVERY_WITH_DELAY(2000, 2000, "run every 2s with delay 2s");

    DEBUG_MEMORY_EVERY(2000);

    DEBUG_EVERY(2000) {
        DEBUG_MEMORY();
    }

    runEvery(20000) {
        DEBUG("sleep");
        DEBUG_SERIAL_END();
        sleep();
        DEBUG_SERIAL_BEGIN(MONITOR_BAUDRATE);
        DEBUG("wakeup");
    }

    runEveryWithDelay(10000, 5000) {
        DEBUG("sleep");
        DEBUG_SERIAL_END();
        sleep();
        DEBUG_SERIAL_BEGIN(MONITOR_BAUDRATE);
        DEBUG("wakeup");
    }
}
