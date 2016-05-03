# Arduino debug utilities [![Build Status](https://travis-ci.org/yoreek/Arduino-DebugUtil.svg?branch=master)](https://travis-ci.org/yoreek/Arduino-DebugUtil)

* Version: 1.0.2
* Release Date: 2016-03-05

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
    DEBUG_SERIAL_SETUP(9600);
}

void loop() {
    DEBUG("ramSize=%d, ramFree=%d", DebugUtil::ramSize(), DebugUtil::ramFree());
    delay(1000);
}
```

Results:

```
0: QuickStart.ino:15 loop - ramSize=2191, ramFree=1603
1000: QuickStart.ino:15 loop - ramSize=2191, ramFree=1603
2001: QuickStart.ino:15 loop - ramSize=2191, ramFree=1603
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
    DEBUG_SERIAL_SETUP(9600);
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

 * 1.0.2 (2016-03-05): Improved macros.
                       Added feature to keep strings in PROGMEM (USE_PROGMEM).
 * 1.0.1 (2016-02-06): Fix warning about variadic macros.
 * 1.0.0 (2016-01-02): Initial version.


## Who do I talk to? ##

 * [Yoreek](https://github.com/yoreek)


[![Bitdeli Badge](https://d2weczhvl823v0.cloudfront.net/yoreek/arduino-debugutil/trend.png)](https://bitdeli.com/free "Bitdeli Badge")

