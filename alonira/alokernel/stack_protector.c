// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include "include/kdiagnostic.h"

#include <gencommon.h>
#include <alocommon.h>

extern uintptr_t __stack_chk_guard;
ALO_USED uintptr_t __stack_chk_guard = 0xAFAFAFAFAFAFAFAF;

ALO_USED GEN_NORETURN void __stack_chk_fail(void) {
    gen_error_t* error = gen_error_attach_backtrace(GEN_ERROR_OUT_OF_BOUNDS, GEN_LINE_NUMBER, "Stack smashing detected");
    gen_error_print("alonira", error, GEN_ERROR_SEVERITY_FATAL);
    gen_error_abort();
}
