// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include "include/tss.h"

#include "include/gdt.h"

alo_tss_t alo_tss = {0};

gen_error_t* alo_tss_install(void) {
	gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) alo_tss_install, GEN_FILE_NAME);
	if(error) return error;

	// clang-format off
    ALO_ASM_BLOCK(
        ALO_ASM(movq %[selectors], %%rbx)
        ALO_ASM(movw %c[tss_segment]*%c[selector_stride](%%rbx), %%ax)
        ALO_ASM(ltr %%ax),
    :: [tss_segment]"n"(ALO_GDT_INDEX_TSS_BASE), [selectors]"p"(alo_gdt_selectors), [selector_stride]"n"(sizeof(alo_segment_selector_t)) : "rax", "rbx");
	// clang-format on

	return NULL;
}