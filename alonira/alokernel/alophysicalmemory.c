// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2023 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include <genlog.h>
#include <genmemory.h>

#include "include/alophysicalmemory.h"

gen_error_t* alo_physical_allocator_init(const alo_physical_memory_range_t* const restrict physical_memory_ranges, const gen_size_t ranges_count, alo_physical_allocator_t* const restrict out_physical_allocator) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) alo_physical_allocator_init, GEN_FILE_NAME);
    if(error) return error;

    if(!physical_memory_ranges) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`physical_memory_ranges` was GEN_NULL");
    if(!ranges_count) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`ranges_count` was 0");
    if(!out_physical_allocator) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`out_physical_allocator` was GEN_NULL");

    for(gen_size_t i = 0; i < ranges_count; ++i) {
        const alo_physical_memory_range_t* range = &physical_memory_ranges[i];

        // TODO: Handle reclaimable pages in one allocator or create a separate allocator instance for them?
        if(range->type == ALO_PHYSICAL_MEMORY_TYPE_FREE) {
	    if(range->address <= 0x10000) continue; // Ignore pages under 1MiB

            out_physical_allocator->ranges[out_physical_allocator->ranges_count++] = *range;

            error = gen_memory_set((void*) range->address, range->size, range->size, 0);
            if(error) return error;

            alo_physical_allocator_header_t* header = (alo_physical_allocator_header_t*) range->address;
            gen_size_t range_page_count = range->size / ALO_PHYSICAL_PAGE_SIZE; // This discards any space <4KiB at the end of a region.
            header->header_page_count = ALO_PHYSICAL_ROUND_TO_NEAREST_PAGE(sizeof(alo_physical_allocator_header_t) + (range_page_count / 8)) / ALO_PHYSICAL_PAGE_SIZE;
            header->total = range_page_count - header->header_page_count;
            header->free = header->total;
        }
    }

    return GEN_NULL;
}

gen_error_t* alo_physical_allocator_request(const alo_physical_allocator_t* const restrict physical_allocator, const gen_size_t count, alo_physical_allocated_page_t* const restrict out_physical) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) alo_physical_allocator_request, GEN_FILE_NAME);
    if(error) return error;

	if(!physical_allocator) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`physical_allocator` was GEN_NULL");
	if(!out_physical) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`out_physical` was GEN_NULL");
	if(!count) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`count` was 0");

    for(gen_size_t i = 0; i < physical_allocator->ranges_count; ++i) {
        const alo_physical_memory_range_t* range = &physical_allocator->ranges[i];
        alo_physical_allocator_header_t* header = (alo_physical_allocator_header_t*) range->address;

        if(header->free >= count) {
            gen_size_t next = 0;
            for(; header->bitmap[next] == GEN_UINT8_MAX; ++next);

            gen_size_t page = next * 8;
            for(gen_size_t j = 0; (header->bitmap[next] << j) != 0; ++j) page++;

            out_physical->address = (void*) range->address + (page * ALO_PHYSICAL_PAGE_SIZE);

            gen_size_t allocated = 0;
            for(gen_size_t j = 0; j < (count / 8) + 1; ++j) {
                for(gen_size_t k = 0; k < 8 && allocated < count; ++k) {

                    allocated++;
                }
                next++;
            }
            header->free -= count;
        }
    }

    return GEN_NULL;
}

//gen_error_t* alo_physical_allocator_return(const alo_physical_allocator_t* const restrict physical_allocator, const alo_physical_allocated_page_t* const restrict physical) {
//    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) alo_physical_allocator_return, GEN_FILE_NAME);
//    if(error) return error;
//
//    if(!physical_allocator) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`physical_allocator` was GEN_NULL");
//    if(!physical) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`physical` was GEN_NULL");
//
//    return GEN_NULL;
//}
