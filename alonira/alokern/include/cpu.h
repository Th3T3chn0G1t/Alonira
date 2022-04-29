// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 TTG <prs.ttg+alonira@pm.me>

#ifndef ALO_KERNEL_CPU_H
#define ALO_KERNEL_CPU_H

#include <alocom.h>

typedef enum {
    ALO_CPU_PRIVILIGE_RING0 = 0,
    ALO_CPU_PRIVILIGE_RING1,
    ALO_CPU_PRIVILIGE_RING2,
    ALO_CPU_PRIVILIGE_RING3
} alo_cpu_privilige_t;

typedef enum {
    ALO_SEGMENT_TABLE_GDT = 0,
    ALO_SEGMENT_TABLE_LDT
} alo_segment_table_selector_t;

typedef struct __packed {
    alo_cpu_privilige_t privilige : 2;
    alo_segment_table_selector_t table : 1;
    uint16_t index : 13;
} alo_segment_selector_t;

#endif
