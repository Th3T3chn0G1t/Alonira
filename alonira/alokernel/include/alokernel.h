// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#ifndef ALO_KERNEL_H
#define ALO_KERNEL_H

#include <gencommon.h>

GEN_NORETURN void alo_hang(void);

void alo_memset(void* const restrict p, const gen_size_t size, const int c);
void alo_memcpy(
        void* const restrict a, void* const restrict b,
        const gen_size_t size);

#endif
