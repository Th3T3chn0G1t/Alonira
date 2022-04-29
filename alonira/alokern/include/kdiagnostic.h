// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 TTG <prs.ttg+alonira@pm.me>

#ifndef ALO_KERNEL_DIAGNOSTIC_H
#define ALO_KERNEL_DIAGNOSTIC_H

#include <alocom.h>

static noreturn __forceinline void hang(void) {
    ALO_FRAME_BEGIN(hang);
    while(true) iasm(as(hlt));
}
extern noreturn void panic(const alo_error_t error, const char* const restrict context);

#define ALO_REQUIRE_NO_ERROR_K(error) \
    do { \
        if(error != ALO_OK) { \
            alogf(FATAL, "Require failed - got error %s (%s)", alo_error_name(error), alo_error_description(error)); \
            panic(error, "Require failed - got error"); \
        } \
    } while(0)

#define ALO_REQUIRE_NO_REACH_K \
    do { \
        alogf(FATAL, "Require failed - invalid control path reached"); \
        panic(ALO_INVALID_CONTROL, "Require failed - invalid control path reached"); \
    } while(0)

#endif
