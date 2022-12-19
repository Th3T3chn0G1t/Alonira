// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include "include/kdiagnostic.h"

#include <gencommon.h>


extern gen_uintptr_t __stack_chk_guard;
GEN_USED gen_uintptr_t __stack_chk_guard = 0xAFAFAFAFAFAFAFAF;

GEN_PRAGMA(GEN_PRAGMA_DIAGNOSTIC_REGION_BEGIN)
GEN_PRAGMA(GEN_PRAGMA_DIAGNOSTIC_REGION_IGNORE("-Wmissing-prototypes"))
GEN_USED GEN_NORETURN void __stack_chk_fail(void) {
GEN_PRAGMA(GEN_PRAGMA_DIAGNOSTIC_REGION_END)
    gen_error_t* error = gen_error_attach_backtrace(GEN_ERROR_OUT_OF_BOUNDS, GEN_LINE_NUMBER, "Stack smashing detected");
    gen_error_print("alonira", error, GEN_ERROR_SEVERITY_FATAL);
    gen_error_abort();
}
