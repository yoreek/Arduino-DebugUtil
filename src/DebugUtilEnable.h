/*
 * DebugUtil.h - Arduino debug utilities
 * Copyright (C) 2016-2017 Yuriy Ustushenko
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
#   include "Arduino.h"
#else
#   include "WProgram.h"
#endif
#include <stdarg.h>
#include <inttypes.h>
#include "DebugUtilPP.h"

#define DEBUG_SERIAL_SETUP(speed) DEBUG_SERIAL_BEGIN(speed)
#define DEBUG_SERIAL_BEGIN(speed)                                       \
    do {                                                                \
        (DEBUG_OUT).begin(speed);                                       \
        while (!(DEBUG_OUT));                                           \
    } while (0)
#define DEBUG_SERIAL_END()        (DEBUG_OUT).end()


#define DEBUG_0()
#define DEBUG(...) PP_CAT(DEBUG_, PP_NARG1(__VA_ARGS__))(__VA_ARGS__)


#define DEBUG_UTIL_FILE (                                               \
    strrchr(__FILE__, '/')                                              \
        ? strrchr(__FILE__, '/') + 1                                    \
        : strrchr(__FILE__, '\\')                                       \
            ? strrchr(__FILE__, '\\') + 1                               \
            : __FILE__)


#if defined(DEBUG_COMPACT)
#   define DEBUG_1(fmt)      DebugUtil::debugCompact(DEBUG_UTIL_F(fmt))
#   define DEBUG_X(fmt, ...) DebugUtil::debugCompact(DEBUG_UTIL_F(fmt), __VA_ARGS__)
#elif defined(USE_STRING_UTIL)
#   define DEBUG_1(fmt)      DebugUtil::debugExtended(DEBUG_UTIL_FILE, __LINE__, __FUNCTION__, DEBUG_UTIL_F(fmt))
#   define DEBUG_X(fmt, ...) DebugUtil::debugExtended(DEBUG_UTIL_FILE, __LINE__, __FUNCTION__, DEBUG_UTIL_F(fmt), __VA_ARGS__)
#else
#   define DEBUG_1(fmt)      DebugUtil::debug(DEBUG_UTIL_FILE, __LINE__, __FUNCTION__, DEBUG_UTIL_F(fmt))
#   define DEBUG_X(fmt, ...) DebugUtil::debug(DEBUG_UTIL_FILE, __LINE__, __FUNCTION__, DEBUG_UTIL_F(fmt), __VA_ARGS__)
#endif


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
