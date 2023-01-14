// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2023 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include <gencommon.h>
#include <genlog.h>

#include <alophysicalmemory.h>
#include <alopaging.h>

#include "include/exposed/aloarchpagetables.h"

static gen_error_t* alo_arch_page_map_internal_address_to_level_index(const gen_uintptr_t address, const alo_page_table_level_t level, gen_size_t* const restrict out_index) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) alo_arch_page_map_internal_address_to_level_index, GEN_FILE_NAME);
    if(error) return error;

	if(!out_index) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`out_index` was GEN_NULL");

    *out_index = (address >> (12 + 9 * level)) & 0b111111111;

    return GEN_NULL;
}

gen_error_t* alo_arch_page_map(alo_physical_allocator_t* const restrict allocator, alo_page_table_entry_t* restrict * const restrict top_level, const gen_uintptr_t physical, const gen_uintptr_t virtual) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) alo_arch_page_map, GEN_FILE_NAME);
    if(error) return error;

	if(!allocator) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`allocator` was GEN_NULL");
	if(!top_level) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`top_level` was GEN_NULL");

    if(!*top_level) {
        alo_physical_allocated_t allocated = {0};
        error = alo_physical_allocator_request(allocator, &allocated);
        if(error) return error;

        *top_level = allocated.address;
    }

    gen_size_t index = 0;
    error = alo_arch_page_map_internal_address_to_level_index(virtual, ALO_PAGE_TABLE_LEVEL4, &index);
    if(error) return error;

    alo_page_table_entry_t* table = &(*top_level)[index];

    for(gen_size_t i = ALO_PAGE_TABLE_LEVEL4;; --i) {
        if(!table->common.present) {
            alo_physical_allocated_t allocated = {0};
            error = alo_physical_allocator_request(allocator, &allocated);
            if(error) return error;

            table->common.address = ((gen_uintptr_t) allocated.address) >> 12;
            table->common.present = gen_true;
            table->common.writeable = gen_true;
        }

        if(!(i - 1)) break;

        error = alo_arch_page_map_internal_address_to_level_index(virtual, (alo_page_table_level_t) i - 1, &index);
        if(error) return error;

        table = &((alo_page_table_entry_t*) (table->common.address << 12))[index];
    }

    table->level1.address = physical >> 12;
    table->level1.present = gen_true;
    table->level1.writeable = gen_true;

    return GEN_NULL;
}
