// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#ifndef ALO_KERNEL_GDT_H
#define ALO_KERNEL_GDT_H

#include "cpu.h"

#include <gencommon.h>

typedef enum {
    ALO_GDT_TYPE_SYSTEM = 0,
    ALO_GDT_TYPE_CODE_DATA
} alo_gdt_type_t;

typedef enum {
    ALO_GDT_DATA_DIRECTION_DOWN = 0,
    ALO_GDT_DATA_DIRECTION_UP,

    ALO_GDT_CODE_CONFORMING_PRIVILIGE_RESTRICTED = 0,
    ALO_GDT_CODE_CONFORMING_PRIVILIGE_UNRESTRICTED
} alo_gdt_conforming_direction_mode_t;

typedef enum {
    ALO_GDT_CODE_READABLE = 0,
    ALO_GDT_CODE_UNREADABLE,

    ALO_GDT_DATA_WRITEABLE = 0,
    ALO_GDT_DATA_UNWRITEABLE
} alo_gdt_access_mode_t;

typedef enum {
    ALO_GDT_GRANULARITY_1B = 0,
    ALO_GDT_GRANULARITY_4KIB
} alo_gdt_granularity_t;

typedef enum {
    ALO_GDT_SEGMENT_WIDTH_16 = 0,
    ALO_GDT_SEGMENT_WIDTH_32,

    ALO_GDT_SEGMENT_WIDTH_64 = 0
} alo_gdt_segment_width_t;

#define ALO_GDT_MAKE_ENTRY(base, limit, readable_writeable, direction_conforming, executable, type, privilige, granularity) ((alo_gdt_entry_t) {(limit) & 0xFFFF, (base) & 0xFFFFFF, true, (readable_writeable), (direction_conforming), (executable), (type), (privilige), true, ((limit) >> 2) & 0xF, false, true, ALO_GDT_SEGMENT_WIDTH_64, (granularity), ((base) >> 3) & 0xFF})

typedef struct ALO_PACKED {
    uint16_t limit_low;
    uint32_t base_low : 24;

    bool accessed : 1;
    alo_gdt_access_mode_t readable_writeable : 1;
    alo_gdt_conforming_direction_mode_t direction_conforming : 1;
    bool executable : 1;
    alo_gdt_type_t type : 1;
    alo_cpu_privilige_t privilige : 2;
    bool present : 1;

    uint8_t limit_high : 4;

    bool reserved : 1;
    bool long_mode : 1;
    alo_gdt_segment_width_t width : 1;
    alo_gdt_granularity_t granularity : 1;

    uint8_t base_high;
} alo_gdt_entry_t;

typedef struct ALO_PACKED {
    uint16_t limit;
    const alo_gdt_entry_t* base;
} alo_gdt_pointer_t;

typedef enum {
    ALO_GDT_INDEX_NULL = 0,
    ALO_GDT_INDEX_CODE,
    ALO_GDT_INDEX_DATA,
    ALO_GDT_INDEX_TSS_BASE,
    ALO_GDT_INDEX_TSS_HIGH,

    ALO_GDT_INDEX_COUNT
} alo_gdt_index_t;

extern alo_gdt_entry_t alo_gdt[ALO_GDT_INDEX_COUNT];
extern const alo_segment_selector_t alo_gdt_selectors[ALO_GDT_INDEX_COUNT];
extern const alo_gdt_pointer_t alo_gdtr;

extern gen_error_t* alo_gdt_install(void);

#endif
