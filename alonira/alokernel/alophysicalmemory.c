// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2023 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include <genlog.h>

#include "include/alophysicalmemory.h"
#include "include/alokernel.h"

gen_error_t* alo_physical_allocator_init(const alo_physical_memory_range_t* const restrict physical_memory_ranges, const gen_size_t ranges_count, alo_physical_allocator_t* const restrict out_physical_allocator) {
    gen_tooling_push(GEN_FUNCTION_NAME, GEN_FILE_NAME);
    GEN_TOOLING_AUTO gen_error_t* error;

    if(!physical_memory_ranges) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_STRING, "`physical_memory_ranges` was GEN_NULL");
    if(!ranges_count) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_STRING, "`ranges_count` was 0");
    if(!out_physical_allocator) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_STRING, "`out_physical_allocator` was GEN_NULL");

    for(gen_size_t i = 0; i < ranges_count; ++i) {
        const alo_physical_memory_range_t* range = &physical_memory_ranges[i];

        // TODO: Handle reclaimable pages in one allocator or create a separate allocator instance for them?
        if(range->type == ALO_PHYSICAL_MEMORY_TYPE_FREE) {
	        if(range->address <= 0x10000) continue; // Ignore pages under 1MiB

            if(out_physical_allocator->ranges_count >= ALO_PHYSICAL_BITMAP_MAX_FREE) return gen_error_attach_backtrace(GEN_ERROR_TOO_LONG, GEN_LINE_STRING, "Number of free ranges (`%uz`) exceeded bitmap limits (`%uz`)", out_physical_allocator->ranges_count, ALO_PHYSICAL_BITMAP_MAX_FREE);
            out_physical_allocator->ranges[out_physical_allocator->ranges_count++] = *range;

            alo_physical_allocator_header_t* header = (alo_physical_allocator_header_t*) range->address;
            gen_size_t range_page_count = range->size / ALO_PHYSICAL_PAGE_SIZE; // This discards any space <4KiB at the end of a region.
            gen_size_t header_page_count = GEN_NEXT_NEAREST(sizeof(alo_physical_allocator_header_t) + (range_page_count / 8), ALO_PHYSICAL_PAGE_SIZE) / ALO_PHYSICAL_PAGE_SIZE;
            // TODO: What to do for memset
            alo_memset((void*) range->address, header->header_page_count * ALO_PHYSICAL_PAGE_SIZE, 0);
            header->header_page_count = header_page_count;
            header->total = range_page_count - header->header_page_count;
            header->free = header->total;
        }
    }

    return GEN_NULL;
}

gen_error_t* alo_physical_allocator_request(const alo_physical_allocator_t* const restrict physical_allocator, alo_physical_allocated_t* const restrict out_physical) {
    gen_tooling_push(GEN_FUNCTION_NAME, GEN_FILE_NAME);
    GEN_TOOLING_AUTO gen_error_t* error;

	if(!physical_allocator) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_STRING, "`physical_allocator` was GEN_NULL");
	if(!out_physical) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_STRING, "`out_physical` was GEN_NULL");

    for(gen_size_t i = 0; i < physical_allocator->ranges_count; ++i) {
        const alo_physical_memory_range_t* range = &physical_allocator->ranges[i];
        alo_physical_allocator_header_t* header = (alo_physical_allocator_header_t*) range->address;

        if(header->free) {
            out_physical->from_range = i;

            gen_size_t next = 0;
            for(; header->bitmap[next] == GEN_UINT8_MAX; ++next);

            gen_size_t page = next * 8;
            gen_size_t bit = 0;
            for(; (gen_uint8_t) (header->bitmap[next] << bit) & 0b10000000; ++bit) page++;

            out_physical->address = (void*) range->address + ((page + header->header_page_count) * ALO_PHYSICAL_PAGE_SIZE);

            alo_memset((void*) out_physical->address, ALO_PHYSICAL_PAGE_SIZE, 0);

            header->bitmap[next] |= 0b10000000 >> bit;

            header->free--;

            return GEN_NULL;
        }
    }

    return gen_error_attach_backtrace(GEN_ERROR_OUT_OF_MEMORY, GEN_LINE_STRING, "No free pages remaining");
}

gen_error_t* alo_physical_allocator_return(const alo_physical_allocator_t* const restrict physical_allocator, const alo_physical_allocated_t* const restrict physical) {
    gen_tooling_push(GEN_FUNCTION_NAME, GEN_FILE_NAME);
    GEN_TOOLING_AUTO gen_error_t* error;

    if(!physical_allocator) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_STRING, "`physical_allocator` was GEN_NULL");
    if(!physical) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_STRING, "`physical` was GEN_NULL");

    if(physical->from_range >= physical_allocator->ranges_count) return gen_error_attach_backtrace(GEN_ERROR_OUT_OF_BOUNDS, GEN_LINE_STRING, "`physical.from_range` exceeded number of pages in allocator");

    const alo_physical_memory_range_t* range = &physical_allocator->ranges[physical->from_range];
    alo_physical_allocator_header_t* header = (alo_physical_allocator_header_t*) range->address;

    const gen_size_t page = (gen_uintptr_t) (physical->address - range->address) / ALO_PHYSICAL_PAGE_SIZE;
    header->bitmap[page / 8] &= ~(0b10000000 >> (page % 8));

    header->free++;

    return GEN_NULL;
}
