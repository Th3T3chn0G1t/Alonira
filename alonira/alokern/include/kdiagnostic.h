// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 TTG <prs.ttg+alonira@pm.me>

#ifndef ALO_KERNEL_DIAGNOSTIC_H
#define ALO_KERNEL_DIAGNOSTIC_H

#include <alocom.h>

ALO_DIAGNOSTIC_REGION_BEGIN
#pragma clang diagnostic ignored "-Wlanguage-extension-token"
static noreturn __forceinline void hang(void) { while(true) asm("hlt"); }
ALO_DIAGNOSTIC_REGION_END
extern noreturn void panic(const alo_error_t error, const char* const restrict context);

#define ALO_REQUIRE_NO_ERROR_K(error) \
    do { \
        if(error != ALO_OK) { \
            panic(error, "Require failed - got error"); \
        } \
    } while(0)

#define ALO_REQUIRE_NO_REACH_K panic(ALO_INVALID_CONTROL, "Require failed - invalid control path reached")

#endif
