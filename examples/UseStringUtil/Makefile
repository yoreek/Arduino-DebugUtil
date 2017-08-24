# Arduino Make file. Refer to https://github.com/sudar/Arduino-Makefile

#ARDUINO_QUIET = 1
ROOT_DIR = $(HOME)/robot

#BOARD_TAG = uno
BOARD_TAG = mega
BOARD_SUB = atmega2560

ARDUINO_DIR = $(ROOT_DIR)/arduino
AVR_TOOLS_DIR = /usr
AVRDUDE_CONF = /etc/avrdude.conf
#ARDUINO_PORT = /dev/ttyACM0
ARDUINO_PORT = /dev/ttyUSB0

# No reset and no init modem
#MONITOR_CMD = picocom -l -i -r
MONITOR_BAUDRATE = 9600
MONITOR_CMD = picocom

ARDUINO_LIBS = DebugUtil StringUtil Time

# -fno-move-loop-invariants - fix bug with segfault during compilation
# -U__PROG_TYPES_COMPAT__   - fix warnings with PROGMEM
CXXFLAGS = -std=c++11 -std=c++1y                                        \
           -fno-move-loop-invariants -Wall -Wno-uninitialized -Werror   \
           -U__PROG_TYPES_COMPAT__  -fno-threadsafe-statics             \
           -DWITH_DEBUG -DUSE_PROGMEM -DMONITOR_BAUDRATE=${MONITOR_BAUDRATE}

# Enable float type on sprintf
#LDFLAGS=-lprintf_flt -lm
# Fix bug with segfault during compilation
#CXXFLAGS=-fno-move-loop-invariants

include $(ROOT_DIR)/Arduino-Makefile/Arduino.mk
