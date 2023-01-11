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

#ifndef ALO_PHYSICAL_BITMAP_MAX_FREE
#define ALO_PHYSICAL_BITMAP_MAX_FREE 64
#endif

#define ALO_PHYSICAL_PAGE_SIZE 4096
#define ALO_PHYSICAL_ROUND_TO_NEAREST_PAGE(x) ((((x) + ALO_PHYSICAL_PAGE_SIZE - 1) / ALO_PHYSICAL_PAGE_SIZE) * ALO_PHYSICAL_PAGE_SIZE)

typedef struct {
    alo_physical_memory_range_t ranges[ALO_PHYSICAL_BITMAP_MAX_FREE];
    gen_size_t ranges_count;
} alo_physical_allocator_t;

typedef struct {
    void* address;
    gen_size_t from_range;
} alo_physical_allocated_t;

typedef struct GEN_PACKED {
    gen_size_t total;
    gen_size_t free;
    gen_size_t header_page_count;
    gen_uint8_t bitmap[];
} alo_physical_allocator_header_t;

extern gen_error_t* alo_physical_allocator_init(const alo_physical_memory_range_t* const restrict physical_memory_ranges, const gen_size_t ranges_count, alo_physical_allocator_t* const restrict out_physical_allocator);
extern gen_error_t* alo_physical_allocator_request(const alo_physical_allocator_t* const restrict physical_allocator, alo_physical_allocated_t* const restrict out_physical);
extern gen_error_t* alo_physical_allocator_return(const alo_physical_allocator_t* const restrict physical_allocator, const alo_physical_allocated_t* const restrict physical);

#endif
