// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include <gencommon.h>
#include <genlog.h>

#include <aloarchgeneric.h>
#include "include/aloboot.h"

static gen_error_t* gen_main(ALO_BOOT_SIGNATURE) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_main, GEN_FILE_NAME);
    if(error) return error;

    alo_boot_info_t boot_info = {0};

    error = alo_arch_generic_init(ALO_BOOT_PASSTHROUGH, &boot_info);
    if(error) return error;

    error = gen_log(GEN_LOG_LEVEL_INFO, "alonira-entry", "Hello, Alonira!");
    if(error) return error;

    error = gen_log_formatted(GEN_LOG_LEVEL_WARNING, "alonira-entry", "Kernel and dependencies currently contain `%uz` TODOs", ALO_TODO_COUNT);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "OS not found :^)");
}

extern GEN_NORETURN GEN_USED void _start(ALO_BOOT_SIGNATURE);
GEN_NORETURN GEN_USED void _start(ALO_BOOT_SIGNATURE) {
    ALO_BOOT_BLOCK;

	GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) _start, GEN_FILE_NAME);
	if(error) gen_error_abort_with_error(error,"alonira-entry");

    error = gen_main(ALO_BOOT_PASSTHROUGH);
    if(error) gen_error_abort_with_error(error, "alonira-entry");

    error = gen_error_attach_backtrace(GEN_ERROR_INVALID_CONTROL, GEN_LINE_NUMBER, "Reached end of `_start`");
    gen_error_abort_with_error(error, "alonira-entry");
}