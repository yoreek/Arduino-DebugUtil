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
#ifndef _DEBUG_UTIL_H_
#define _DEBUG_UTIL_H_

#ifdef WITH_DEBUG
#include "DebugUtilEnable.h"
#else
#include "DebugUtilDisable.h"
#endif
#include "DebugUtilRunEvery.h"

extern "C++" { namespace DebugUtil {

int ramFree();
int ramSize();

}} // namespace

#endif // _DEBUG_UTIL_H_
