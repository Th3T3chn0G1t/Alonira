// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 TTG <prs.ttg+alonira@pm.me>

#ifndef ALO_KERNEL_GDT_H
#define ALO_KERNEL_GDT_H

#include "cpu.h"

#include <alocom.h>

typedef enum {
    ALO_GDT_INVALID = 0,
    ALO_GDT_VALID
} alo_gdt_presence_t;

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

typedef struct __packed {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_mid;

    bool accessed : 1;
    alo_gdt_access_mode_t readable_writeable : 1;
    alo_gdt_conforming_direction_mode_t direction_conforming : 1;
    bool executable : 1;
    alo_gdt_type_t type : 1;
    alo_cpu_privilige_t privilige : 2;
    alo_gdt_presence_t present : 1;

    uint8_t limit_high : 4;

    bool reserved : 1;
    bool long_mode : 1;
    alo_gdt_segment_width_t width : 1;
    alo_gdt_granularity_t granularity : 1;

    uint8_t base_high;
} alo_gdt_entry_t;

typedef struct __packed {
    uint16_t limit;
    alo_gdt_entry_t* base;
} alo_gdt_pointer_t;

ALO_ERRORABLE alo_gdt_install(void);

#endif