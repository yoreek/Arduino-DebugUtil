/*
 * DebugUtilPP.h - Arduino debug utilities
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

#ifndef DEBUG_UTIL_PP_H
#define DEBUG_UTIL_PP_H

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

#endif // DEBUG_UTIL_PP_H
