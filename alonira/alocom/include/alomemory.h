// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 TTG <prs.ttg+alonira@pm.me>

#ifndef ALO_MEMORY_H
#define ALO_MEMORY_H

#include "alocom.h"

extern void* memset(void* dest, int ch, size_t count);

ALO_ERRORABLE alo_memory_set(void* const restrict address, const size_t length, const unsigned char value);

#endif
