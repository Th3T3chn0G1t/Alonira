// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 TTG <prs.ttg+alonira@pm.me>

#include "include/tss.h"

#include "include/gdt.h"

alo_tss_t alo_tss = {0};

alo_error_t alo_tss_install(void) {
	ALO_FRAME_BEGIN(alo_tss_install);

	// clang-format off
    iasm(
        as(movq %[selectors], %%rbx)
        as(movw %c[tss_segment]*%c[selector_stride](%%rbx), %%ax)
        as(ltr %%ax),
    :: [tss_segment]"n"(ALO_GDT_INDEX_TSS_BASE), [selectors]"p"(alo_gdt_selectors), [selector_stride]"n"(sizeof(alo_segment_selector_t)) : "rax", "rbx");
	// clang-format on

	ALO_ALL_OK;
}
