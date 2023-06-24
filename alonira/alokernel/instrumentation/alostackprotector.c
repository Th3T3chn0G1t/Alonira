// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include <gencommon.h>
#include <genlog.h>

GEN_USED gen_uintptr_t __stack_chk_guard = 0xAFAFAFAFAFAFAFAF;

GEN_NORETURN extern void __stack_chk_fail(void);
GEN_USED GEN_NORETURN void __stack_chk_fail(void) {
    gen_tooling_push(GEN_FUNCTION_NAME, GEN_FILE_NAME);
    GEN_TOOLING_AUTO gen_error_t* error;

    error = gen_error_attach_backtrace(GEN_ERROR_OUT_OF_BOUNDS, GEN_LINE_STRING, "Stack smashing detected");
    gen_log(GEN_LOG_LEVEL_FATAL, "alonira", "%e", error);
    gen_error_abort();
}
