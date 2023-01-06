// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2023 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#ifndef ALO_KERNEL_PHYSICAL_MEMORY_H
#define ALO_KERNEL_PHYSICAL_MEMORY_H

#include <gencommon.h>

typedef enum {
    ALO_PHYSICAL_MEMORY_TYPE_NOT_PRESENT,
    ALO_PHYSICAL_MEMORY_TYPE_FREE,
    ALO_PHYSICAL_MEMORY_TYPE_RECLAIMABLE,
    ALO_PHYSICAL_MEMORY_TYPE_RESERVED,
    ALO_PHYSICAL_MEMORY_TYPE_KERNEL,
    ALO_PHYSICAL_MEMORY_TYPE_KERNEL_MODULE
} alo_physical_memory_type_t;

typedef struct {
    alo_physical_memory_type_t type;
    gen_uintptr_t address;
    gen_size_t size;
} alo_physical_memory_range_t;

#endif
