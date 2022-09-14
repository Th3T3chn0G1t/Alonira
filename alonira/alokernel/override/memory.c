// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include <gencommon.h>

GEN_PRAGMA(GEN_PRAGMA_DIAGNOSTIC_REGION_BEGIN)
GEN_PRAGMA(GEN_PRAGMA_DIAGNOSTIC_REGION_IGNORE("-Wmissing-prototypes"))

void *memset(void *b, int c, size_t len) {
    for(size_t i = 0; i < len; ++i) {
        ((unsigned char*) b)[i] = (unsigned char) c;
    }

    return b;
}

GEN_PRAGMA(GEN_PRAGMA_DIAGNOSTIC_REGION_END)
