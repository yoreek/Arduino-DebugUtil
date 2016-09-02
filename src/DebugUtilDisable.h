/*
 * DebugUtilDisable.h - Arduino debug utilities
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
#ifndef _DEBUG_UTIL_DISABLE_H_
#define _DEBUG_UTIL_DISABLE_H_

#include "DebugUtilPP.h"

#define DEBUG_SERIAL_BEGIN(speed)
#define DEBUG_SERIAL_SETUP(speed)
#define DEBUG_SERIAL_END()
#define DEBUG_PRINT(...)
#define DEBUG(...)

#define DEBUG_EVERY_0()
#define DEBUG_EVERY_1(...)      if (0)
#define DEBUG_EVERY_X(...)
#define DEBUG_EVERY(...)               PP_CAT(DEBUG_EVERY_, PP_NARG1(__VA_ARGS__))(__VA_ARGS__)
#define DEBUG_EVERY_WITH_DELAY(t, ...) PP_CAT(DEBUG_EVERY_, PP_NARG1(__VA_ARGS__))(__VA_ARGS__)

#define DEBUG_MEMORY()
#define DEBUG_MEMORY_EVERY(interval)

#endif // _DEBUG_UTIL_DISABLE_H_
