// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 TTG <prs.ttg+alonira@pm.me>

#include "include/gdt.h"

static alo_gdt_entry_t gdt[3] = {
	{0},
	{0xFFFF, 0, 0, true, ALO_GDT_CODE_UNREADABLE, ALO_GDT_CODE_CONFORMING_PRIVILIGE_RESTRICTED, true, ALO_GDT_TYPE_CODE_DATA, ALO_CPU_PRIVILIGE_RING0, ALO_GDT_VALID, 0xF, false, true, ALO_GDT_SEGMENT_WIDTH_64, ALO_GDT_GRANULARITY_4KIB, 0},
	{0xFFFF, 0, 0, true, ALO_GDT_DATA_UNWRITEABLE, ALO_GDT_DATA_DIRECTION_DOWN, false, ALO_GDT_TYPE_CODE_DATA, ALO_CPU_PRIVILIGE_RING0, ALO_GDT_VALID, 0xF, false, true, ALO_GDT_SEGMENT_WIDTH_64, ALO_GDT_GRANULARITY_4KIB, 0}};

static alo_segment_selector_t gdt_selectors[3] = {
	{ALO_CPU_PRIVILIGE_RING0, ALO_SEGMENT_TABLE_GDT, 0},
	{ALO_CPU_PRIVILIGE_RING0, ALO_SEGMENT_TABLE_GDT, 1},
	{ALO_CPU_PRIVILIGE_RING0, ALO_SEGMENT_TABLE_GDT, 2}};

ALO_ERRORABLE alo_gdt_install(void) {
	ALO_FRAME_BEGIN(alo_gdt_install);

	alogf(DEBUG, "GDT Load: %zux entries @ %zu bytes - %zu bytes in total", sizeof(gdt) / sizeof(gdt[0]), sizeof(alo_gdt_entry_t), sizeof(gdt));
	alogf(DEBUG, "NULL %zx: %zx", (size_t) * (uint16_t*) &gdt_selectors[0], *(uint64_t*) &gdt[0]);
	alogf(DEBUG, "CODE %zx: %zx", (size_t) * (uint16_t*) &gdt_selectors[1], *(uint64_t*) &gdt[1]);
	alogf(DEBUG, "DATA %zx: %zx", (size_t) * (uint16_t*) &gdt_selectors[2], *(uint64_t*) &gdt[2]);

	// clang-format off
	iasm(
        as(jmp .reload_segments)
        as(.gdtr:)
            as(.short 0)
            as(.quad 0)
        as(.reload_segments:)
            as(cli)

            as(movq .gdtr, %%rax)
            as(movw %3, (%%rax))
            as(movq %0, 2(%%rax))
            as(lgdtq (%%rax))

            as(pushq 0x8)
            as(mov .done_reload_cs(%%rip), %%rax)
            as(pushq %%rax)
            as(lretq)
            as(.done_reload_cs:)

            as(hlt)

            // as(movq %1, %%rax)
            // as(pushw %c2(%%rax))
            // as(movq .done_reload_cs, %%rax)
            // as(pushq %%rax)
            // as(lretq)
            // as(.done_reload_cs:)

            // as(movq %1, %%rbx)
            // as(movw 2*%c2(%%rbx), %%ax)
            // as(movw %%ax, %%ds)
            // as(movw %%ax, %%es)
            // as(movw %%ax, %%fs)
            // as(movw %%ax, %%gs)
            // as(movw %%ax, %%ss)

            as(sti),
    :: "p"(&gdt), "p"(gdt_selectors), "n"(sizeof(alo_segment_selector_t)), "n"(sizeof(gdt) - 1) : "rax", "rbx");
	// clang-format on

	ALO_ALL_OK;
}
