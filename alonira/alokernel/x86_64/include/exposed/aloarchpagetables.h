// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#ifndef ALO_KERNEL_X86_64_PAGE_TABLES_H
#define ALO_KERNEL_X86_64_PAGE_TABLES_H

#include <alophysicalmemory.h>

typedef struct {
    gen_bool_t present : 1;
    gen_bool_t writeable : 1;
    gen_bool_t restrict_privileged_access : 1;
    gen_bool_t writethrough : 1;
    gen_bool_t cacheable : 1;
    gen_bool_t accessed : 1;
    gen_bool_t reserved0 : 1;
    gen_bool_t reserved1 : 1;
    gen_bool_t reserved2 : 1;

    gen_uint8_t free0 : 3;

    gen_uintptr_t address : 40;

    gen_uint16_t free1 : 11;

    gen_bool_t no_execute : 1; // TODO: EFER MSR?
} alo_page_table_internal_common_entry_t;

typedef union GEN_PACKED {
    gen_uint64_t raw;
    alo_page_table_internal_common_entry_t common;
    alo_page_table_internal_common_entry_t level4;
    alo_page_table_internal_common_entry_t level3;
    alo_page_table_internal_common_entry_t level2;
    struct GEN_PACKED {
        gen_bool_t present : 1;
        gen_bool_t writeable : 1;
        gen_bool_t restrict_privileged_access : 1;
        gen_bool_t writethrough : 1;
        gen_bool_t cacheable : 1;
        gen_bool_t accessed : 1;

        gen_bool_t dirty : 1;
        gen_bool_t page_attribute_table_high : 1;
        gen_bool_t global : 1;

        gen_uint8_t free0 : 3;

        gen_uintptr_t address : 40;

        gen_uint16_t free1 : 11;

        gen_bool_t no_execute : 1;
    } level1;
} alo_page_table_entry_t;

typedef enum {
    ALO_PAGE_TABLE_LEVEL1 = 1,
    ALO_PAGE_TABLE_LEVEL2,
    ALO_PAGE_TABLE_LEVEL3,
    ALO_PAGE_TABLE_LEVEL4
} alo_page_table_level_t;

#define ALO_PAGE_TABLE_ENTRY_COUNT (ALO_PHYSICAL_PAGE_SIZE / sizeof(alo_page_table_entry_t))
#define ALO_HIGHER_HALF 0xFFFF800000000000

#endif
