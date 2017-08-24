#if defined(ARDUINO) && ARDUINO >= 100
#   include "Arduino.h"
#else
#   include "WProgram.h"
#endif

// Activate debug:
#ifndef WITH_DEBUG
#   define WITH_DEBUG
#endif
//#undef WITH_DEBUG

#include <DebugUtil.h>

#ifndef MONITOR_BAUDRATE
#   define MONITOR_BAUDRATE 9600
#endif

void setup() {
    DEBUG_SERIAL_BEGIN(MONITOR_BAUDRATE);
    // 0: QuickStart.ino:17 setup - setup
    DEBUG("setup");
}

void sleep() {
    delay(3000);
}

void loop() {
    // loop

    // 12: QuickStart.ino:29 loop - param: 123
    DEBUG("simple test");

    // 55: QuickStart.ino:32 loop - print every 1s param: 123
    DEBUG("param: %d", 123);

    // 113: QuickStart.ino:35 loop - ramSize=2187, ramFree=1487
    DEBUG_EVERY(1000, "print every 1s param: %d", 123);

    DEBUG_EVERY(3000) {
        // 113: QuickStart.ino:39 loop - ramSize=2187, ramFree=1487
        DEBUG("ramSize=%d, ramFree=%d", DebugUtil::ramSize(), DebugUtil::ramFree());
    }

    DEBUG_EVERY(1000) {
        int x = 123;
        // 123
        Serial.println(x);
    }

    DEBUG_EVERY_WITH_DELAY(1000, 5000) {
        // 5198: QuickStart.ino:50 loop - print every 1s with delay 5s
        DEBUG("print every 1s with delay 5s");
    }

    // 3594: QuickStart.ino:54 loop - run every 2s with delay 2s
    DEBUG_EVERY_WITH_DELAY(2000, 2000, "run every 2s with delay 2s");

    // 179: QuickStart.ino:57 loop - ramSize:2187 ramFree:1487
    DEBUG_MEMORY_EVERY(2000);

    DEBUG_EVERY(2000) {
        // 5811: QuickStart.ino:61 loop - ramSize:2187 ramFree:1487
        DEBUG_MEMORY();
    }

    runEvery(20000) {
        // 296: QuickStart.ino:53 loop - sleep
        DEBUG("sleep");
        DEBUG_SERIAL_END();
        sleep();
        DEBUG_SERIAL_BEGIN(MONITOR_BAUDRATE);
        // 3403: QuickStart.ino:71 loop - wakeup
        DEBUG("wakeup");
    }

    delay(500);
}
