// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include "include/gdt.h"

#include "include/tss.h"

#include <alocommon.h>

alo_gdt_entry_t alo_gdt[] = {
	[ALO_GDT_INDEX_NULL] = {0},
	[ALO_GDT_INDEX_CODE] = ALO_GDT_MAKE_ENTRY(0x0, 0xFFFFFF, ALO_GDT_CODE_UNREADABLE, ALO_GDT_CODE_CONFORMING_PRIVILIGE_RESTRICTED, true, ALO_CPU_PRIVILIGE_RING0, ALO_GDT_GRANULARITY_4KIB),
	[ALO_GDT_INDEX_DATA] = ALO_GDT_MAKE_ENTRY(0x0, 0xFFFFFF, ALO_GDT_DATA_UNWRITEABLE, ALO_GDT_DATA_DIRECTION_DOWN, false, ALO_CPU_PRIVILIGE_RING0, ALO_GDT_GRANULARITY_4KIB),
	// These two need to be runtime initialized as they actually take addresses
    [ALO_GDT_INDEX_TSS_BASE] = {0},
	[ALO_GDT_INDEX_TSS_HIGH] = {0}};

const alo_segment_selector_t alo_gdt_selectors[] = {
	[ALO_GDT_INDEX_NULL] = {ALO_CPU_PRIVILIGE_RING0, ALO_SEGMENT_TABLE_GDT, ALO_GDT_INDEX_NULL},
	[ALO_GDT_INDEX_CODE] = {ALO_CPU_PRIVILIGE_RING0, ALO_SEGMENT_TABLE_GDT, ALO_GDT_INDEX_CODE},
	[ALO_GDT_INDEX_DATA] = {ALO_CPU_PRIVILIGE_RING0, ALO_SEGMENT_TABLE_GDT, ALO_GDT_INDEX_DATA},
	[ALO_GDT_INDEX_TSS_BASE] = {ALO_CPU_PRIVILIGE_RING0, ALO_SEGMENT_TABLE_GDT, ALO_GDT_INDEX_TSS_BASE}};

const alo_gdt_pointer_t alo_gdtr = {sizeof(alo_gdt) - 1, alo_gdt};

ALO_NO_INLINE gen_error_t* alo_gdt_install(void) {
	GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) alo_gdt_install, GEN_FILE_NAME);
	if(error) return error;

	alo_gdt[ALO_GDT_INDEX_TSS_BASE] = ALO_GDT_MAKE_SYSTEM_ENTRY(&alo_tss, sizeof(alo_tss), ALO_GDT_SYSTEM_SEGMENT_TYPE_TSS_IDLE, ALO_CPU_PRIVILIGE_RING0, ALO_GDT_GRANULARITY_1B);
	alo_gdt[ALO_GDT_INDEX_TSS_HIGH] = ALO_GDT_MAKE_SYSTEM_ENTRY_HIGH(&alo_tss);

	// clang-format off
	ALO_ASM_BLOCK(
        ALO_ASM(movq %[gdtr], %%rax)
        ALO_ASM(lgdtq (%%rax))

        ALO_ASM(movq %[selectors], %%rbx)
        ALO_ASM(movw %c[data_segment]*%c[selector_stride](%%rbx), %%ax)
        ALO_ASM(movw %%ax, %%ds)
        ALO_ASM(movw %%ax, %%es)
        ALO_ASM(movw %%ax, %%fs)
        ALO_ASM(movw %%ax, %%gs)
        ALO_ASM(movw %%ax, %%ss)

        ALO_ASM(pushq %c[code_segment]*%c[selector_stride](%%rbx))
        ALO_ASM(lea .done_reload_cs(%%rip), %%rax)
        ALO_ASM(pushq %%rax)
        ALO_ASM(lretq)
        ALO_ASM(.done_reload_cs:),
    :: [gdtr]"p"(&alo_gdtr), [selectors]"p"(alo_gdt_selectors), [selector_stride]"n"(sizeof(alo_segment_selector_t)), [code_segment]"n"(ALO_GDT_INDEX_CODE), [data_segment]"n"(ALO_GDT_INDEX_DATA) : "rax", "rbx");
	// clang-format on

	return NULL;
}
