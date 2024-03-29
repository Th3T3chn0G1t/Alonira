// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include <gencommon.h>

#include "include/alotss.h"
#include "include/alogdt.h"

alo_tss_t alo_tss = {0};

gen_error_t* alo_tss_install(void) {
    gen_tooling_push(GEN_FUNCTION_NAME, GEN_FILE_NAME);
    GEN_TOOLING_AUTO gen_error_t* error;

	// clang-format off
    GEN_ASM_BLOCK(
        GEN_ASM(ltr %[tss_selector]),
    :: [tss_selector] "m" (alo_gdt_selectors[ALO_GDT_INDEX_TSS_BASE]) :);
	// clang-format on

	return GEN_NULL;
}
