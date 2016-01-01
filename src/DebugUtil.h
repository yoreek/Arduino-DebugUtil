/*
 * DebugUtil.h - Arduino debug utilities
 * Copyright (C) 2016 Yuriy Ustushenko
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the version 3 GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef DEBUG_UTIL_H
#define DEBUG_UTIL_H

#define WITH_DEBUG
#ifdef WITH_DEBUG

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <stdarg.h>

#ifndef DEBUG_OUT
#define DEBUG_OUT Serial
#endif

#define DEBUG_SERIAL_SETUP(speed)                                       \
    do {                                                                \
        (DEBUG_OUT).begin(speed);                                       \
        while (!(DEBUG_OUT));                                           \
    } while (0)

#ifndef DEBUG_BUF_LEN
#define DEBUG_BUF_LEN 80
#endif

#ifdef USE_STRING_UTIL
#  include <StringUtil.h>
#  define DEBUG_PRINT(fmt, ...) StringUtil::fprintf(DEBUG_OUT, fmt, ##__VA_ARGS__)
#else
#  define DEBUG_PRINT(fmt, ...)                                         \
    do {                                                                \
        char buf[DEBUG_BUF_LEN];                                        \
        snprintf(buf, DEBUG_BUF_LEN, fmt, ##__VA_ARGS__);               \
        (DEBUG_OUT).print(buf);                                         \
    } while (0)
#endif

#define __SHORT_FILE__                                                  \
    (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#ifndef DEBUG_PREFIX
#  ifdef USE_STRING_UTIL
#    define DEBUG_PREFIX DEBUG_PRINT("%F %T: %s:%d %s - ", __SHORT_FILE__, __LINE__, __FUNCTION__)
#  else
#    define DEBUG_PREFIX DEBUG_PRINT("%lu: %s:%d %s - ", millis(), __SHORT_FILE__, __LINE__, __FUNCTION__)
#  endif
#endif

#define DEBUG(fmt, ...)                                                 \
    do {                                                                \
        DEBUG_PREFIX;                                                   \
        DEBUG_PRINT(fmt, ##__VA_ARGS__);                                \
        (DEBUG_OUT).println();                                          \
    } while (0)

#else

#define DEBUG(fmt, ...)
#define DEBUG_SERIAL_SETUP(speed)
#define DEBUG_PRINT(fmt, ...)

#endif // WITH_DEBUG

extern "C++" { namespace DebugUtil {

int ramFree();
int ramSize();

}} // namespace

#endif // DEBUG_UTIL_H
