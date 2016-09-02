# Arduino debug utilities [![Build Status](https://travis-ci.org/yoreek/Arduino-DebugUtil.svg?branch=master)](https://travis-ci.org/yoreek/Arduino-DebugUtil)

* Version: 1.0.5
* Release Date: 2016-09-02

## What is this repository for? ##

Utilities for logging printf style formatted data to any Serial ports.


## How do I get set up? ##

 * [Download](https://github.com/yoreek/Arduino-DebugUtil/archive/master.zip) the Latest release from gitHub.
 * Unzip and modify the Folder name to "DebugUtil".
 * Paste the modified folder on your library folder (On your `Libraries` folder inside Sketchbooks or Arduino software).
 * Download and Install [StringUtil](https://github.com/yoreek/Arduino-StringUtil) as well, if you are going to use `StringUtil` library.
 * Restart the Arduino Software


## Usage ##

### Quick start ###
```
#include <Arduino.h>

// Activate debug:
#define WITH_DEBUG

#include <DebugUtil.h>

void setup() {
    DEBUG_SERIAL_BEGIN(9600);
}

void loop() {
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
}
```

Results:

```
0: QuickStart.ino:18 setup - setup
0: QuickStart.ino:29 loop - simple test
12: QuickStart.ino:32 loop - param: 123
55: QuickStart.ino:35 loop - print every 1s param: 123
113: QuickStart.ino:39 loop - ramSize=2187, ramFree=1487
123
179: QuickStart.ino:57 loop - ramSize:2187 ramFree:1487
237: QuickStart.ino:61 loop - ramSize:2187 ramFree:1487
296: QuickStart.ino:66 loop - sleep
3403: QuickStart.ino:71 loop - wakeup
3403: QuickStart.ino:29 loop - simple test
3422: QuickStart.ino:32 loop - param: 123
3467: QuickStart.ino:35 loop - print every 1s param: 123
3527: QuickStart.ino:39 loop - ramSize=2187, ramFree=1487
123
3594: QuickStart.ino:54 loop - run every 2s with delay 2s
3655: QuickStart.ino:57 loop - ramSize:2187 ramFree:1487
3716: QuickStart.ino:61 loop - ramSize:2187 ramFree:1487
3776: QuickStart.ino:29 loop - simple test
3821: QuickStart.ino:32 loop - param: 123
...
```
### Use StringUtil ###

Due to some performance reasons %f is not included in the Arduino's implementation of sprintf().
To solve this problem, you can use `StringUtil` library.

```
#include <Arduino.h>

// Activate debug:
#define WITH_DEBUG
// Use StringUtil library
#define USE_STRING_UTIL

#include <DebugUtil.h>

void setup() {
    DEBUG_SERIAL_BEGIN(9600);
}

void loop() {
    DEBUG("float=%.2f", 0.123456);
    delay(1000);
}
```

Output:
```
1970-01-01 00:00:01: UseStringUtil.ino:15 loop - float=0.12
1970-01-01 00:00:02: UseStringUtil.ino:15 loop - float=0.12
1970-01-01 00:00:03: UseStringUtil.ino:15 loop - float=0.12
1970-01-01 00:00:04: UseStringUtil.ino:15 loop - float=0.12
```

### Options

All must be defined before the include.

- `#define WITH_DEBUG` - Define it to activate debug; if not defined all debug code is removed
- `#define DEBUG_OUT <dev>` - Set output device (Serial, File, etc)
- `#define DEBUG_BUF_LEN <len>` - Set print buffer length (default: 80) when not used `StringUtil`
- `#define USE_STRING_UTIL` - Define it to to use `StringUtil` for string formatting
- `#define DEBUG_PREFIX <code>` - Define code for prefix printing
   (Default: ```DEBUG_PRINT("%lu: %s:%d %s - ", millis(), __SHORT_FILE__, __LINE__, __FUNCTION__)```)

## Example ##

Included on example folder, available on Arduino IDE.


## Version History ##

 * 1.0.5 (2016-09-02): Added DEBUG_EVERY, DEBUG_EVERY_WITH_DELAY macros.
 * 1.0.4 (2016-07-18): Added DEBUG_COMPACT key to save memory.
 * 1.0.3 (2016-05-13): Fix bug when call without parameters.
 * 1.0.2 (2016-03-05): Improved macros.
                       Added feature to keep strings in PROGMEM (USE_PROGMEM).
 * 1.0.1 (2016-02-06): Fix warning about variadic macros.
 * 1.0.0 (2016-01-02): Initial version.


## Who do I talk to? ##

 * [Yoreek](https://github.com/yoreek)


[![Bitdeli Badge](https://d2weczhvl823v0.cloudfront.net/yoreek/arduino-debugutil/trend.png)](https://bitdeli.com/free "Bitdeli Badge")

