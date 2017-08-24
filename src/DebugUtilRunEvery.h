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
#ifndef _DEBUG_UTIL_RUN_EVERY_H_
#define _DEBUG_UTIL_RUN_EVERY_H_

#define _runEveryWithDelay(t, d, f) for (                               \
    static uint32_t _nextTime = f() + (d), _cont = 0;                   \
    (!_cont && _nextTime <= f() && ((_nextTime = f() + (t)) || 1))      \
    || (_cont && --_cont); _cont++)
#define _runEvery(t, f) _runEveryWithDelay((t), 0, f)

#ifndef runEvery
#define runEvery(t)                 runEveryMS(t)
#endif
#ifndef runEveryMS
#define runEveryMS(t)               _runEvery(t, millis)
#endif
#ifndef runEveryUS
#define runEveryUS(t)               _runEvery(t, micros)
#endif

#ifndef runEveryWithDelay
#define runEveryWithDelay(t, d)     runEveryWithDelayMS(t, d)
#endif
#ifndef runEveryWithDelayMS
#define runEveryWithDelayMS(t, d)   _runEveryWithDelay(t, d, millis)
#endif
#ifndef runEveryWithDelayUS
#define runEveryWithDelayUS(t, d)   _runEveryWithDelay(t, d, micros)
#endif

#endif // _DEBUG_UTIL_RUN_EVERY_H_
