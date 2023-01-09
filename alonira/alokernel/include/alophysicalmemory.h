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

typedef struct {
    gen_uint8_t* bitmap;
} alo_physical_allocator_t;

extern gen_error_t* alo_physical_allocator_init(const alo_physical_memory_range_t* const restrict physical_memory_ranges, const gen_size_t ranges_count, alo_physical_allocator_t* const restrict out_physical_allocator);
extern gen_error_t* alo_physical_allocator_request(const alo_physical_allocator_t* const restrict physical_allocator, const gen_size_t count, gen_uintptr_t* const restrict out_physical);

#endif
