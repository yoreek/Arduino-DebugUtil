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
#ifndef _DEBUG_UTIL_H_
#define _DEBUG_UTIL_H_

#if defined(ARDUINO) && ARDUINO >= 100
#   include "Arduino.h"
#else
#   include "WProgram.h"
#endif

#ifdef WITH_DEBUG

#ifdef USE_STRING_UTIL
#   include <StringUtil.h>
#else
#   ifndef DEBUG_BUF_LEN
#        define DEBUG_BUF_LEN 80
#   endif
#endif

#ifndef DEBUG_OUT
#   define DEBUG_OUT Serial
#endif

#if defined(F) && defined(USE_PROGMEM) && defined(USE_STRING_UTIL)
#   define DEBUG_UTIL_PROGMEM PROGMEM
#   define DEBUG_UTIL_F(s) F(s)
#   define DEBUG_UTIL_PGM_P const __FlashStringHelper *
#else
#   define DEBUG_UTIL_PROGMEM
#   define DEBUG_UTIL_F(s) (s)
#   define DEBUG_UTIL_PGM_P const char *
#endif

#endif /* WITH_DEBUG */

extern int __heap_start, *__brkval;

class DebugUtil {
    public:
#ifdef WITH_DEBUG
        static void printf(DEBUG_UTIL_PGM_P fmt, ...)
        {
            va_list args;

            va_start(args, fmt);
            vprintf(fmt, args);
            va_end(args);
        };

        static void vprintf(DEBUG_UTIL_PGM_P fmt, va_list &args)
        {
#ifdef USE_STRING_UTIL
            StringUtil::vfprintf(DEBUG_OUT, fmt, args);
#else
            char buf[DEBUG_BUF_LEN];

            vsnprintf(buf, DEBUG_BUF_LEN, fmt, args);
            (DEBUG_OUT).print(buf);
#endif
        };

        static void debugCompact(DEBUG_UTIL_PGM_P fmt, ...)
        {
            va_list args;

            DebugUtil::printf(DEBUG_UTIL_F("%l: "), millis());

            va_start(args, fmt);
            vprintf(fmt, args);
            va_end(args);

            (DEBUG_OUT).println();
        };


        static void debugExtended(const char *file, int line, const char *func, DEBUG_UTIL_PGM_P fmt, ...)
        {
            va_list args;

            DebugUtil::printf(DEBUG_UTIL_F("%F %T: %s:%d %s - "), file, line, func);

            va_start(args, fmt);
            vprintf(fmt, args);
            va_end(args);

            (DEBUG_OUT).println();
        };

        static void debug(const char *file, int line, const char *func, DEBUG_UTIL_PGM_P fmt, ...)
        {
            va_list args;

            DebugUtil::printf(DEBUG_UTIL_F("%lu: %s:%d %s - "), millis(), file, line, func);

            va_start(args, fmt);
            vprintf(fmt, args);
            va_end(args);

            (DEBUG_OUT).println();
        };
#endif /* WITH_DEBUG */

        static int ramFree()
        {
            int v;
            int a = (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
            return a;
        };

        static int ramSize()
        {
            int v;
            int a = (int) &v;
            return a;
        };
};

#ifdef WITH_DEBUG
#   include "DebugUtilEnable.h"
#else
#   include "DebugUtilDisable.h"
#endif

#include "DebugUtilRunEvery.h"

#endif // _DEBUG_UTIL_H_
