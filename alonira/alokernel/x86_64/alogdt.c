// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include <gencommon.h>

#include "include/alogdt.h"
#include "include/alotss.h"

alo_gdt_entry_t alo_gdt[] = {
	[ALO_GDT_INDEX_NULL] = {0},
	[ALO_GDT_INDEX_CODE] = ALO_GDT_MAKE_ENTRY(0x0, 0xFFFFFF, ALO_GDT_CODE_UNREADABLE, ALO_GDT_CODE_CONFORMING_PRIVILEGE_RESTRICTED, gen_true, ALO_CPU_PRIVILEGE_RING0, ALO_GDT_GRANULARITY_4KIB),
	[ALO_GDT_INDEX_DATA] = ALO_GDT_MAKE_ENTRY(0x0, 0xFFFFFF, ALO_GDT_DATA_UNWRITEABLE, ALO_GDT_DATA_DIRECTION_DOWN, gen_false, ALO_CPU_PRIVILEGE_RING0, ALO_GDT_GRANULARITY_4KIB),
	// These two need to be runtime initialized as they actually take addresses
    // TODO: There's probably a way to make linker scripts insert pointers here
    [ALO_GDT_INDEX_TSS_BASE] = {0},
	[ALO_GDT_INDEX_TSS_HIGH] = {0}};

const alo_segment_selector_t alo_gdt_selectors[] = {
	[ALO_GDT_INDEX_NULL] = {{ALO_CPU_PRIVILEGE_RING0, ALO_SEGMENT_TABLE_GDT, ALO_GDT_INDEX_NULL}},
	[ALO_GDT_INDEX_CODE] = {{ALO_CPU_PRIVILEGE_RING0, ALO_SEGMENT_TABLE_GDT, ALO_GDT_INDEX_CODE}},
	[ALO_GDT_INDEX_DATA] = {{ALO_CPU_PRIVILEGE_RING0, ALO_SEGMENT_TABLE_GDT, ALO_GDT_INDEX_DATA}},
	[ALO_GDT_INDEX_TSS_BASE] = {{ALO_CPU_PRIVILEGE_RING0, ALO_SEGMENT_TABLE_GDT, ALO_GDT_INDEX_TSS_BASE}}};

const alo_gdt_pointer_t alo_gdtr = {sizeof(alo_gdt) - 1, alo_gdt};

GEN_NO_INLINE gen_error_t* alo_gdt_install(void) {
    gen_tooling_push(GEN_FUNCTION_NAME, GEN_FILE_NAME);
    GEN_TOOLING_AUTO gen_error_t* error;

	alo_gdt[ALO_GDT_INDEX_TSS_BASE] = ALO_GDT_MAKE_SYSTEM_ENTRY(&alo_tss, sizeof(alo_tss), ALO_GDT_SYSTEM_SEGMENT_TYPE_TSS_IDLE, ALO_CPU_PRIVILEGE_RING0, ALO_GDT_GRANULARITY_1B);
	alo_gdt[ALO_GDT_INDEX_TSS_HIGH] = ALO_GDT_MAKE_SYSTEM_ENTRY_HIGH(&alo_tss);

	// clang-format off
	GEN_ASM_BLOCK(
        GEN_ASM(lgdtq %[gdtr])

        GEN_ASM(movw %[data_segment], %%ax)
        GEN_ASM(movw %%ax, %%ds)
        GEN_ASM(movw %%ax, %%es)
        GEN_ASM(movw %%ax, %%fs)
        GEN_ASM(movw %%ax, %%gs)
        GEN_ASM(movw %%ax, %%ss)

        GEN_ASM(pushq %[code_segment])
        GEN_ASM(lea .done_reload_cs(%%rip), %%rax)
        GEN_ASM(pushq %%rax)
        GEN_ASM(lretq)
        GEN_ASM(.done_reload_cs:),
    ::
        [code_segment]    "n" (alo_gdt_selectors[ALO_GDT_INDEX_CODE]),
        [data_segment]    "n" (alo_gdt_selectors[ALO_GDT_INDEX_DATA]),
        [gdtr]            "m" (alo_gdtr)
    : "rax", "rbx");
	// clang-format on

	return GEN_NULL;
}
