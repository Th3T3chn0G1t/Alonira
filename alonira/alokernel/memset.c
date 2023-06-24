// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include <gencommon.h>

GEN_USED void alo_memset(
        void* const restrict p, const gen_size_t size, const int c) {

    // TODO: Faster arch-specific impl/maybe move to Genstone
    for(gen_size_t i = 0; i < size; ++i) ((char*) p)[i] = (char) c;
}

GEN_USED void* memset(
        void* const p, const int c, const unsigned long size) {

    alo_memset(p, size, c);
    return p;
}
