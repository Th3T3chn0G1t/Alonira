// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#ifndef ALO_KERNEL_GDT_H
#define ALO_KERNEL_GDT_H

#include "cpu.h"

#include <gencommon.h>

typedef enum {
    ALO_GDT_TYPE_SYSTEM,
    ALO_GDT_TYPE_CODE_DATA
} alo_gdt_type_t;

typedef enum {
    ALO_GDT_DATA_DIRECTION_DOWN,
    ALO_GDT_DATA_DIRECTION_UP,

    ALO_GDT_CODE_CONFORMING_PRIVILIGE_RESTRICTED = 0,
    ALO_GDT_CODE_CONFORMING_PRIVILIGE_UNRESTRICTED
} alo_gdt_conforming_direction_mode_t;

typedef enum {
    ALO_GDT_CODE_READABLE,
    ALO_GDT_CODE_UNREADABLE,

    ALO_GDT_DATA_WRITEABLE = 0,
    ALO_GDT_DATA_UNWRITEABLE
} alo_gdt_access_mode_t;

typedef enum {
    ALO_GDT_GRANULARITY_1B,
    ALO_GDT_GRANULARITY_4KIB
} alo_gdt_granularity_t;

typedef enum {
    ALO_GDT_SEGMENT_WIDTH_16,
    ALO_GDT_SEGMENT_WIDTH_32,

    ALO_GDT_SEGMENT_WIDTH_64 = 0
} alo_gdt_segment_width_t;

typedef enum {
    ALO_GDT_SYSTEM_SEGMENT_TYPE_LDT = 2,
    
    ALO_GDT_SYSTEM_SEGMENT_TYPE_TSS_IDLE = 9,
    ALO_GDT_SYSTEM_SEGMENT_TYPE_TSS_BUSY = 11,
} alo_gdt_system_segment_type_t;

#define ALO_GDT_MAKE_ENTRY(base, limit, readable_writeable, direction_conforming, executable, privilige, granularity) ((alo_gdt_entry_t) { .entry = {(limit) & 0xFFFF, (base) & 0xFFFFFF, {.code_data_access = {gen_true, (readable_writeable), (direction_conforming), (executable), ALO_GDT_TYPE_CODE_DATA, (privilige), gen_true}}, ((limit) >> 2) & 0xF, gen_false, gen_true, ALO_GDT_SEGMENT_WIDTH_64, (granularity), ((base) >> 24) & 0xFF}})
#define ALO_GDT_MAKE_SYSTEM_ENTRY(base, limit, type, privilige, granularity) ((alo_gdt_entry_t) { .entry = {(limit) & 0xFFFF, (gen_uintptr_t) (base) & 0xFFFFFF, {.system_access = {(type), ALO_GDT_TYPE_SYSTEM, (privilige), gen_true}}, ((limit) >> 2) & 0xF, gen_false, gen_true, ALO_GDT_SEGMENT_WIDTH_64, (granularity), ((gen_uintptr_t) (base) >> 24) & 0xFF}})
#define ALO_GDT_MAKE_SYSTEM_ENTRY_HIGH(base) ((alo_gdt_entry_t) { .system_entry_high = {(gen_uint32_t) ((gen_uintptr_t) (base) >> 32), 0}})

typedef struct {
    union {
        struct GEN_PACKED {
            gen_uint16_t limit_low;
            gen_uint32_t base_low : 24;

            union {
                struct GEN_PACKED {
                    gen_bool_t accessed : 1;
                    alo_gdt_access_mode_t readable_writeable : 1;
                    alo_gdt_conforming_direction_mode_t direction_conforming : 1;
                    gen_bool_t executable : 1;
                    alo_gdt_type_t type : 1;
                    alo_cpu_privilige_t privilige : 2;
                    gen_bool_t present : 1;
                } code_data_access;

                struct GEN_PACKED {
                    alo_gdt_system_segment_type_t system_type : 4;
                    alo_gdt_type_t type : 1;
                    alo_cpu_privilige_t privilige : 2;
                    gen_bool_t present : 1;
                } system_access;
            };

            gen_uint8_t limit_high : 4;

            gen_bool_t reserved : 1;
            gen_bool_t long_mode : 1;
            alo_gdt_segment_width_t width : 1;
            alo_gdt_granularity_t granularity : 1;

            gen_uint8_t base_high;
        } entry;
        struct GEN_PACKED {
            gen_uint32_t base_high;
            gen_uint32_t reserved;
        } system_entry_high;
    };
} alo_gdt_entry_t;

typedef struct GEN_PACKED {
    gen_uint16_t limit;
    const alo_gdt_entry_t* base;
} alo_gdt_pointer_t;

typedef enum {
    ALO_GDT_INDEX_NULL,
    ALO_GDT_INDEX_CODE,
    ALO_GDT_INDEX_DATA,
    ALO_GDT_INDEX_TSS_BASE,
    ALO_GDT_INDEX_TSS_HIGH,

    ALO_GDT_INDEX_COUNT
} alo_gdt_index_t;

// TODO: Define LDT structs and API even though we aren't gonna use them.

extern alo_gdt_entry_t alo_gdt[ALO_GDT_INDEX_COUNT];
extern const alo_segment_selector_t alo_gdt_selectors[ALO_GDT_INDEX_COUNT];
extern const alo_gdt_pointer_t alo_gdtr;

extern gen_error_t* alo_gdt_install(void);

#endif
