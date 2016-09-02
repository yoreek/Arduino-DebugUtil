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
#pragma once
#ifndef _DEBUG_UTIL_ENABLE_H_
#define _DEBUG_UTIL_ENABLE_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <stdarg.h>
#include <inttypes.h>
#include "DebugUtilPP.h"

#ifndef DEBUG_OUT
#define DEBUG_OUT Serial
#endif


#define DEBUG_SERIAL_SETUP(speed) DEBUG_SERIAL_BEGIN(speed)
#define DEBUG_SERIAL_BEGIN(speed)                                       \
    do {                                                                \
        (DEBUG_OUT).begin(speed);                                       \
        while (!(DEBUG_OUT));                                           \
    } while (0)
#define DEBUG_SERIAL_END()        (DEBUG_OUT).end()


#if defined(F) && defined(USE_PROGMEM)
#   define __FLASH_STR(s) F(s)
#else
#   define __FLASH_STR(s) (s)
#endif


#define DEBUG_PRINT_0()
#define DEBUG_PRINT(...)    PP_CAT(DEBUG_PRINT_, PP_NARG1(__VA_ARGS__))(__VA_ARGS__)


#ifdef USE_STRING_UTIL
#    include <StringUtil.h>
#    define DEBUG_PRINT_1(fmt) StringUtil::fprintf(DEBUG_OUT, __FLASH_STR(fmt))
#    define DEBUG_PRINT_X(fmt, ...) StringUtil::fprintf(DEBUG_OUT, __FLASH_STR(fmt), __VA_ARGS__)
#else
#    ifndef DEBUG_BUF_LEN
#        define DEBUG_BUF_LEN 80
#    endif
#    define DEBUG_PRINT_1(fmt) (DEBUG_OUT).print(__FLASH_STR(fmt))
#    define DEBUG_PRINT_X(fmt, ...)                                     \
    do {                                                                \
        char buf[DEBUG_BUF_LEN];                                        \
        snprintf(buf, DEBUG_BUF_LEN, fmt, __VA_ARGS__);                 \
        (DEBUG_OUT).print(buf);                                         \
    } while (0)
#endif


#define __SHORT_FILE__                                                  \
    (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#ifndef DEBUG_PREFIX
#    ifdef DEBUG_COMPACT
#        define DEBUG_PREFIX DEBUG_PRINT("%ul: ", millis())
#    else
#        ifdef USE_STRING_UTIL
#            define DEBUG_PREFIX DEBUG_PRINT("%F %T: %s:%d %s - ", __SHORT_FILE__, __LINE__, __FUNCTION__)
#        else
#            define DEBUG_PREFIX DEBUG_PRINT("%lu: %s:%d %s - ", millis(), __SHORT_FILE__, __LINE__, __FUNCTION__)
#        endif
#    endif
#endif


#define DEBUG(...)                                                      \
    do {                                                                \
        DEBUG_PREFIX;                                                   \
        DEBUG_PRINT(__VA_ARGS__);                                       \
        (DEBUG_OUT).println();                                          \
    } while (0)


#define DEBUG_EVERY_0()
#define DEBUG_EVERY_1(t)                    runEvery(t)
#define DEBUG_EVERY_X(t, ...)               runEvery(t) DEBUG(__VA_ARGS__)
#define DEBUG_EVERY(...)                    PP_CAT(DEBUG_EVERY_, PP_NARG1(__VA_ARGS__))(__VA_ARGS__)
#define DEBUG_EVERY_WITH_DELAY_1(t, d)      runEveryWithDelay(t, d)
#define DEBUG_EVERY_WITH_DELAY_X(t, d, ...) runEveryWithDelay(t, d) DEBUG(__VA_ARGS__)
#define DEBUG_EVERY_WITH_DELAY(t, ...)      PP_CAT(DEBUG_EVERY_WITH_DELAY_, PP_NARG1(__VA_ARGS__))(t, __VA_ARGS__)


#define DEBUG_MEMORY()                                                  \
    DEBUG("ramSize:%d ramFree:%d", DebugUtil::ramSize(), DebugUtil::ramFree())
#define DEBUG_MEMORY_EVERY(interval) DEBUG_EVERY(interval) DEBUG_MEMORY()

#endif // _DEBUG_UTIL_ENABLE_H_
