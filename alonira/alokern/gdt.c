// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 TTG <prs.ttg+alonira@pm.me>

#include "include/gdt.h"

#include "include/tss.h"

alo_gdt_entry_t alo_gdt[] = {
	[ALO_GDT_INDEX_NULL] = {0},
	[ALO_GDT_INDEX_CODE] = ALO_GDT_MAKE_ENTRY(0x0, 0xFFFFFF, ALO_GDT_CODE_UNREADABLE, ALO_GDT_CODE_CONFORMING_PRIVILIGE_RESTRICTED, true, ALO_GDT_TYPE_CODE_DATA, ALO_CPU_PRIVILIGE_RING0, ALO_GDT_GRANULARITY_4KIB),
	[ALO_GDT_INDEX_DATA] = ALO_GDT_MAKE_ENTRY(0x0, 0xFFFFFF, ALO_GDT_DATA_UNWRITEABLE, ALO_GDT_DATA_DIRECTION_DOWN, false, ALO_GDT_TYPE_CODE_DATA, ALO_CPU_PRIVILIGE_RING0, ALO_GDT_GRANULARITY_4KIB),
	[ALO_GDT_INDEX_TSS_BASE] = ALO_GDT_MAKE_ENTRY(0x0, sizeof(alo_tss), ALO_GDT_CODE_READABLE, ALO_GDT_DATA_DIRECTION_DOWN, false, ALO_GDT_TYPE_SYSTEM, ALO_CPU_PRIVILIGE_RING0, ALO_GDT_GRANULARITY_1B),
	[ALO_GDT_INDEX_TSS_HIGH] = {0}};

const alo_segment_selector_t alo_gdt_selectors[] = {
	[ALO_GDT_INDEX_NULL] = {ALO_CPU_PRIVILIGE_RING0, ALO_SEGMENT_TABLE_GDT, ALO_GDT_INDEX_NULL},
	[ALO_GDT_INDEX_CODE] = {ALO_CPU_PRIVILIGE_RING0, ALO_SEGMENT_TABLE_GDT, ALO_GDT_INDEX_CODE},
	[ALO_GDT_INDEX_DATA] = {ALO_CPU_PRIVILIGE_RING0, ALO_SEGMENT_TABLE_GDT, ALO_GDT_INDEX_DATA},
	[ALO_GDT_INDEX_TSS_BASE] = {ALO_CPU_PRIVILIGE_RING0, ALO_SEGMENT_TABLE_GDT, ALO_GDT_INDEX_TSS_BASE}};

const alo_gdt_pointer_t alo_gdtr = {sizeof(alo_gdt) - 1, alo_gdt};

alo_error_t alo_gdt_install(void) {
	ALO_FRAME_BEGIN(alo_gdt_install);

	alo_gdt[ALO_GDT_INDEX_TSS_BASE].base_low = (uintptr_t) &alo_gdt & 0xFFFFFF;
	alo_gdt[ALO_GDT_INDEX_TSS_BASE].base_high = ((uintptr_t) &alo_gdt >> 3) & 0xFF;
	((uint32_t*) &alo_gdt[ALO_GDT_INDEX_TSS_HIGH])[0] = (uint32_t) ((uintptr_t) &alo_gdt >> 4);

	// clang-format off
	iasm(
        as(movq %[gdtr], %%rax)
        as(lgdtq (%%rax))

        as(movq %[selectors], %%rbx)
        as(movw %c[data_segment]*%c[selector_stride](%%rbx), %%ax)
        as(movw %%ax, %%ds)
        as(movw %%ax, %%es)
        as(movw %%ax, %%fs)
        as(movw %%ax, %%gs)
        as(movw %%ax, %%ss)

        as(pushq %c[code_segment]*%c[selector_stride](%%rbx))
        as(lea .done_reload_cs(%%rip), %%rax)
        as(pushq %%rax)
        as(lretq)
        as(.done_reload_cs:),
    :: [gdtr]"p"(&alo_gdtr), [selectors]"p"(alo_gdt_selectors), [selector_stride]"n"(sizeof(alo_segment_selector_t)), [code_segment]"n"(ALO_GDT_INDEX_CODE), [data_segment]"n"(ALO_GDT_INDEX_DATA) : "rax", "rbx");
	// clang-format on

	ALO_ALL_OK;
}
