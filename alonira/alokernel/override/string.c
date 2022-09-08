// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include <gencommon.h>

GEN_PRAGMA(GEN_PRAGMA_DIAGNOSTIC_REGION_BEGIN)
GEN_PRAGMA(GEN_PRAGMA_DIAGNOSTIC_REGION_IGNORE("-Wmissing-prototypes"))

// TODO: Codestyle kinda went out the window here as the signatures
//       were copied directly from manpages.

size_t strnlen(const char* const restrict string, size_t limit) {
    for(size_t i = 0; i < limit; ++i) {
        if(!string[i]) return i + 1;
    }

    return limit;
}

size_t strlen(const char *s) {
    return strnlen(s, SIZE_MAX);
}

char *strncpy(char * dst, const char * src, size_t len) {
    size_t i = 0;
    for(; i < len; ++i) {
        dst[i] = src[i];
        if(!src[i]) return dst;
    }
    dst[i - 1] = '\0';

    return dst;
}

char *strncat(char *restrict s1, const char *restrict s2, size_t n) {
    size_t start = __builtin_strlen(s1);

    return strncpy(s1 + start, s2, n);
}

GEN_PRAGMA(GEN_PRAGMA_DIAGNOSTIC_REGION_END)
