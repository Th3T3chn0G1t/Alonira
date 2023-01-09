// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2023 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include <genlog.h>

#include "include/alophysicalmemory.h"

gen_error_t* alo_physical_allocator_init(const alo_physical_memory_range_t* const restrict physical_memory_ranges, const gen_size_t ranges_count, alo_physical_allocator_t* const restrict out_physical_allocator) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) alo_physical_allocator_init, GEN_FILE_NAME);
    if(error) return error;

    if(!physical_memory_ranges) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`physical_memory_ranges` was GEN_NULL");
    if(!ranges_count) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`ranges_count` was 0");
    if(!out_physical_allocator) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`out_physical_allocator` was GEN_NULL");

    gen_size_t free = 0;

    for(gen_size_t i = 0; i < ranges_count; ++i) {
        const alo_physical_memory_range_t* range = &physical_memory_ranges[i];

        const char* type_name = GEN_NULL;
        switch(range->type) {
            case ALO_PHYSICAL_MEMORY_TYPE_NOT_PRESENT: type_name = "NOT_PRESENT"; break;
            case ALO_PHYSICAL_MEMORY_TYPE_FREE: type_name = "FREE"; break;
            case ALO_PHYSICAL_MEMORY_TYPE_RECLAIMABLE: type_name = "RECLAIMABLE"; break;
            case ALO_PHYSICAL_MEMORY_TYPE_RESERVED: type_name = "RESERVED"; break;
            case ALO_PHYSICAL_MEMORY_TYPE_KERNEL: type_name = "KERNEL"; break;
            case ALO_PHYSICAL_MEMORY_TYPE_KERNEL_MODULE: type_name = "KERNEL_MODULE"; break;
        }

        if(range->type == ALO_PHYSICAL_MEMORY_TYPE_FREE) free += range->size;

        error = gen_log_formatted(GEN_LOG_LEVEL_DEBUG, "alonira-physicalmemory", "Range `%t` %p-%p (size: %uz)", type_name, range->address, range->address + range->size, range->size);
        if(error) return error;
    }

    error = gen_log_formatted(GEN_LOG_LEVEL_DEBUG, "alonira-physicalmemory", "Available: %uz KiB (%uz)", free / 1024, free);
    if(error) return error;

    return GEN_NULL;
}

gen_error_t* alo_physical_allocator_request(const alo_physical_allocator_t* const restrict physical_allocator, const gen_size_t count, gen_uintptr_t* const restrict out_physical) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) alo_physical_allocator_request, GEN_FILE_NAME);
    if(error) return error;

	if(!physical_allocator) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`physical_allocator` was GEN_NULL");
	if(!out_physical) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`out_physical` was GEN_NULL");
	if(!count) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`count` was 0");

    return GEN_NULL;
}
