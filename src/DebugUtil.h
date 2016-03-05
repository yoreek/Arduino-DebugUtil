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

#if defined(F) && defined(USE_PROGMEM)
# define __FLASH_STR(s) F(s)
#else
# define __FLASH_STR(s) (s)
#endif

#define PP_ARG_N(                                                       \
     _1,  _2,  _3,  _4,  _5,  _6,  _7,  _8,  _9, _10,                   \
    _11, _12, _13, _14, _15, _16, _17, _18, _19, _20,                   \
    _21, _22, _23, _24, _25, _26, _27, _28, _29, _30,   N, ...) N
#define PP_RSEQ_N()                                                     \
     30,  29,  28,  27,  26,  25,  24,  23,  22,  21,                   \
     20,  19,  18,  17,  16,  15,  14,  13,  12,  11,                   \
     10,   9,   8,   7,   6,   5,   4,   3,   2,   1,   0
#define PP_RSEQ_N1()                                                    \
      X,   X,   X,   X,   X,   X,   X,   X,   X,   X,                   \
      X,   X,   X,   X,   X,   X,   X,   X,   X,   X,                   \
      X,   X,   X,   X,   X,   X,   X,   X,   X,   1,   0
#define PP_NARG_(...)       PP_ARG_N(__VA_ARGS__)
#define PP_NARG(...)        PP_NARG_(__VA_ARGS__, PP_RSEQ_N())
#define PP_NARG1(...)       PP_NARG_(__VA_ARGS__, PP_RSEQ_N1())
#define PP_CAT_(x, y)       x ## y
#define PP_CAT(x, y)        PP_CAT_(x, y)

#define DEBUG_PRINT_0()
#define DEBUG_PRINT_1(fmt)  (DEBUG_OUT).print(__FLASH_STR(fmt))
#define DEBUG_PRINT(...)    PP_CAT(DEBUG_PRINT_, PP_NARG1(__VA_ARGS__))(__VA_ARGS__)

#ifdef USE_STRING_UTIL
#  include <StringUtil.h>
#  define DEBUG_PRINT_X(fmt, ...) StringUtil::fprintf(DEBUG_OUT, __FLASH_STR(fmt), __VA_ARGS__)
#else
#  define DEBUG_PRINT_X(fmt, ...)                                       \
    do {                                                                \
        char buf[DEBUG_BUF_LEN];                                        \
        snprintf(buf, DEBUG_BUF_LEN, fmt, __VA_ARGS__);                 \
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

#define DEBUG(...)                                                      \
    do {                                                                \
        DEBUG_PREFIX;                                                   \
        DEBUG_PRINT(__VA_ARGS__);                                       \
        (DEBUG_OUT).println();                                          \
    } while (0)

#else

#define DEBUG(...)
#define DEBUG_SERIAL_SETUP(speed)
#define DEBUG_PRINT(...)

#endif // WITH_DEBUG

extern "C++" { namespace DebugUtil {

int ramFree();
int ramSize();

}} // namespace

#endif // DEBUG_UTIL_H
