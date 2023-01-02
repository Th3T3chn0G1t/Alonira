// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include <gencommon.h>

extern gen_uintptr_t __stack_chk_guard;
GEN_USED gen_uintptr_t __stack_chk_guard = 0xAFAFAFAFAFAFAFAF;

GEN_NORETURN extern void __stack_chk_fail(void);
GEN_USED GEN_NORETURN void __stack_chk_fail(void) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) __stack_chk_fail, GEN_FILE_NAME);
    if(error) gen_error_abort_with_error(error, "alonira");

    error = gen_error_attach_backtrace(GEN_ERROR_OUT_OF_BOUNDS, GEN_LINE_NUMBER, "Stack smashing detected");
    gen_error_abort_with_error(error, "alonira");
}
