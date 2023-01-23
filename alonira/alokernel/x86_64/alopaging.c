// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2023 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include <gencommon.h>
#include <genlog.h>

#include <alophysicalmemory.h>
#include <alopaging.h>

#include "include/exposed/aloarchpagetables.h"
#include "include/alocpu.h"

static gen_error_t* alo_arch_page_map_internal_address_to_level_index(const gen_uintptr_t address, const alo_page_table_level_t level, gen_size_t* const restrict out_index) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) alo_arch_page_map_internal_address_to_level_index, GEN_FILE_NAME);
    if(error) return error;

	if(!out_index) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`out_index` was GEN_NULL");

    *out_index = (address >> (12 + 9 * (level - 1))) & 0b111111111;

    return GEN_NULL;
}

gen_error_t* alo_arch_page_map(alo_physical_allocator_t* const restrict allocator, alo_page_table_entry_t* restrict * const restrict top_level, const gen_uintptr_t physical, const gen_uintptr_t virtual) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) alo_arch_page_map, GEN_FILE_NAME);
    if(error) return error;

	if(!allocator) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`allocator` was GEN_NULL");
	if(!top_level) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`top_level` was GEN_NULL");
    if(physical & 0b111111111111) return gen_error_attach_backtrace_formatted(GEN_ERROR_BAD_ALIGNMENT, GEN_LINE_NUMBER, "`physical` (%p) was not on a page boundary", physical);
    if(virtual & 0b111111111111) return gen_error_attach_backtrace_formatted(GEN_ERROR_BAD_ALIGNMENT, GEN_LINE_NUMBER, "`virtual` (%p) was not on a page boundary", virtual);

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

    for(gen_size_t i = ALO_PAGE_TABLE_LEVEL4; i - 1; --i) {
       if(!table->common.present) {
           alo_physical_allocated_t allocated = {0};
           error = alo_physical_allocator_request(allocator, &allocated);
           if(error) return error;

           gen_uintptr_t address = (gen_uintptr_t) allocated.address >> 12;
           table->common.address = address;

           table->common.present = gen_true;
           table->common.writeable = gen_true;
       }

       error = alo_arch_page_map_internal_address_to_level_index(virtual, (alo_page_table_level_t) i - 1, &index);
       if(error) return error;

       gen_uintptr_t addr = table->common.address << 12;
       table = &((alo_page_table_entry_t*) addr)[index];
    }

    table->level1.address = physical >> 12;
    table->level1.present = gen_true;
    table->level1.writeable = gen_true;

    return GEN_NULL;
}

gen_error_t* alo_arch_page_map_range(alo_physical_allocator_t* const restrict allocator, alo_page_table_entry_t* restrict * const restrict top_level, const gen_uintptr_t physical, const gen_uintptr_t virtual, const gen_size_t count) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) alo_arch_page_map_range, GEN_FILE_NAME);
    if(error) return error;

    if(!allocator) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`allocator` was GEN_NULL");
    if(!top_level) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`top_level` was GEN_NULL");
    if(physical & 0b111111111111) return gen_error_attach_backtrace_formatted(GEN_ERROR_BAD_ALIGNMENT, GEN_LINE_NUMBER, "`physical` (%p) was not on a page boundary", physical);
    if(virtual & 0b111111111111) return gen_error_attach_backtrace_formatted(GEN_ERROR_BAD_ALIGNMENT, GEN_LINE_NUMBER, "`virtual` (%p) was not on a page boundary", virtual);

    error = gen_log_formatted(GEN_LOG_LEVEL_DEBUG, "alonira-paging", "Mapping range of %uz pages %p -> %p", count, virtual, physical);
    if(error) return error;

    for(gen_size_t i = 0; i < count; ++i) {
        error = alo_arch_page_map(allocator, top_level, physical + i * ALO_PHYSICAL_PAGE_SIZE, virtual + i * ALO_PHYSICAL_PAGE_SIZE);
        if(error) return error;
    }

    return GEN_NULL;
}

gen_error_t* alo_arch_translate_address(alo_page_table_entry_t* restrict * const restrict top_level, const gen_uintptr_t virtual, gen_uintptr_t* const restrict out_physical) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) alo_arch_translate_address, GEN_FILE_NAME);
    if(error) return error;

    gen_size_t index = 0;
    error = alo_arch_page_map_internal_address_to_level_index(virtual, ALO_PAGE_TABLE_LEVEL4, &index);
    if(error) return error;

    alo_page_table_entry_t* table = &(*top_level)[index];

    for(gen_size_t i = ALO_PAGE_TABLE_LEVEL4; i - 1; --i) {
        error = alo_arch_page_map_internal_address_to_level_index(virtual, (alo_page_table_level_t) i - 1, &index);
        if(error) return error;

        gen_uintptr_t addr = table->common.address << 12;
        table = &((alo_page_table_entry_t*) addr)[index];
    }

    *out_physical = table->level1.address << 12;

    return GEN_NULL;
}

gen_error_t* alo_arch_page_flush(const alo_page_table_entry_t* const restrict top_level) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) alo_arch_page_map_range, GEN_FILE_NAME);
    if(error) return error;

    if(!top_level) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`top_level` was GEN_NULL");

    alo_register_cr3_t cr3 = {0};
    cr3.table_address = (gen_uintptr_t) top_level >> 12;

    error = gen_log_formatted(GEN_LOG_LEVEL_DEBUG, "alonira-paging", "Reloading CR3 w/ %p (L4 @ %p), kiss your caches goodbye...", cr3.cr3, top_level);
    if(error) return error;

    GEN_ASM_BLOCK(
        GEN_ASM(movq %%rax, %%cr3),
        :: [value] "a" (cr3.cr3) :
    );

    return GEN_NULL;
}
