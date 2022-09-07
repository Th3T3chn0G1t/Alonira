// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#ifndef ALO_KERNEL_DIAGNOSTIC_H
#define ALO_KERNEL_DIAGNOSTIC_H

#include <gencommon.h>
#include <alocommon.h>

#include "cpu.h"

static GEN_NORETURN ALO_FORCE_INLINE void alo_hang(void) {
    ALO_ASM_BLOCK(ALO_ASM(cli));
    while(true) ALO_ASM_BLOCK(ALO_ASM(hlt));
}
extern GEN_NORETURN void alo_panic(const gen_error_t* error, const char* const restrict context);
extern GEN_NORETURN void alo_panic_with_registers(const gen_error_t* error, const char* const restrict context, alo_registers_t registers);

#define ALO_REQUIRE_NO_ERROR_K(error) \
    do { \
        if(error != ALO_OK) { \
            alogf(FATAL, "Require failed - got error %s (%s)", alo_error_name(error), alo_error_description(error)); \
            alo_panic(error, "Require failed - got error"); \
        } \
    } while(0)

#define ALO_REQUIRE_NO_REACH_K \
    do { \
        alogf(FATAL, "Require failed - invalid control path reached"); \
        alo_panic(ALO_INVALID_CONTROL, "Require failed - invalid control path reached"); \
    } while(0)

#endif
