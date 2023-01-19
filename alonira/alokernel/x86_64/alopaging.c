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

    *out_index = (address >> (12 + 9 * level)) & 0b111111111;

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

    for(gen_size_t i = ALO_PAGE_TABLE_LEVEL4;; --i) {
        if(virtual >= 0xFFFFFFFF80000000) {
            gen_log_formatted(GEN_LOG_LEVEL_DEBUG, "a", "index: %uz; table: %uz @ %p", index, i, table);
        }
        if(!table->common.present) {
            alo_physical_allocated_t allocated = {0};
            error = alo_physical_allocator_request(allocator, &allocated);
            if(error) return error;
            if(virtual >= 0xFFFFFFFF80000000) {
                gen_log_formatted(GEN_LOG_LEVEL_DEBUG, "a", "allocated new table @ %p (>> 12 -> %p)", allocated.address, (gen_uintptr_t) allocated.address >> 12);
            }

            table->common.address = (gen_uintptr_t) allocated.address;
            table->common.address >>= 12;
            if(virtual >= 0xFFFFFFFF80000000) {
                gen_log_formatted(GEN_LOG_LEVEL_DEBUG, "a", "addr %p : addr %p : addr %p", (gen_uintptr_t) allocated.address, (gen_uintptr_t) allocated.address >> 12);
            }

            table->common.present = gen_true;
            table->common.writeable = gen_true;
        }

        if(!(i - 1)) break;

        error = alo_arch_page_map_internal_address_to_level_index(virtual, (alo_page_table_level_t) i - 1, &index);
        if(error) return error;

        gen_uintptr_t addr = table->common.address << 12;
        if(virtual >= 0xFFFFFFFF80000000) {
            gen_log_formatted(GEN_LOG_LEVEL_DEBUG, "a", "next @ %p (%p << 12)", addr, (gen_uintptr_t) table->common.address);
        }
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

    gen_log_formatted(GEN_LOG_LEVEL_DEBUG, "adad", "Mapping range %p->%p (%uz pages)", virtual, physical, count);

    for(gen_size_t i = 0; i < count; ++i) {
        error = alo_arch_page_map(allocator, top_level, physical + count * ALO_PHYSICAL_PAGE_SIZE, virtual + i * ALO_PHYSICAL_PAGE_SIZE);
        if(error) return error;
    }

    return GEN_NULL;
}

gen_error_t* alo_arch_page_flush(const alo_page_table_entry_t* const restrict top_level) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) alo_arch_page_map_range, GEN_FILE_NAME);
    if(error) return error;

    if(!top_level) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`top_level` was GEN_NULL");

    alo_register_cr3_t cr3 = { .table_writethrough = gen_true, .table_cacheable = gen_false, .table_address = ((gen_uintptr_t) top_level) >> 12 };
    GEN_ASM_BLOCK(
        GEN_ASM(movq %%rax, %%cr3),
        :: [value] "a" (cr3.cr3) :
    );

    return GEN_NULL;
}
