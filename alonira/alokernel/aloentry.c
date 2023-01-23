// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include <gencommon.h>
#include <genlog.h>
#include <genstring.h>

#include "include/aloarch.h"
#include "include/aloboot.h"
#include "include/alophysicalmemory.h"
#include "include/alopaging.h"

static gen_error_t* gen_main(ALO_BOOT_SIGNATURE) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_main, GEN_FILE_NAME);
    if(error) return error;

    alo_boot_info_t boot_info = {0};

    error = alo_arch_init(ALO_BOOT_PASSTHROUGH, &boot_info);
    if(error) return error;

    alo_physical_allocator_t allocator = {0};
    error = alo_physical_allocator_init(boot_info.physical_memory_ranges, boot_info.physical_memory_range_count, &allocator);
    if(error) return error;

    error = gen_log(GEN_LOG_LEVEL_INFO, "alonira-entry", "Hello, Alonira!");
    if(error) return error;

    error = gen_log_formatted(GEN_LOG_LEVEL_WARNING, "alonira-entry", "Kernel and dependencies currently contain `%uz` TODOs", ALO_TODO_COUNT);
    if(error) return error;

    alo_page_table_entry_t* top_level = GEN_NULL;
    for(gen_size_t i = 0; i < boot_info.physical_memory_range_count; ++i) {
        switch(boot_info.physical_memory_ranges[i].type) {
            case ALO_PHYSICAL_MEMORY_TYPE_NOT_PRESENT: GEN_FALLTHROUGH;
            case ALO_PHYSICAL_MEMORY_TYPE_KERNEL_MODULE: return gen_error_attach_backtrace(GEN_ERROR_UNKNOWN, GEN_LINE_NUMBER, "how");

            case ALO_PHYSICAL_MEMORY_TYPE_RESERVED: continue;

            case ALO_PHYSICAL_MEMORY_TYPE_FREE: GEN_FALLTHROUGH;
            case ALO_PHYSICAL_MEMORY_TYPE_RECLAIMABLE: {
                error = alo_arch_page_map_range(&allocator, &top_level, boot_info.physical_memory_ranges[i].address, boot_info.physical_memory_ranges[i].address, boot_info.physical_memory_ranges[i].size / ALO_PHYSICAL_PAGE_SIZE);
                if(error) return error;

                gen_uintptr_t physical = 0;
                error = alo_arch_translate_address(&top_level, boot_info.physical_memory_ranges[i].address, &physical);
                if(error) return error;

                gen_log_formatted(GEN_LOG_LEVEL_DEBUG, "", "Software traversed: %p -> %p", boot_info.physical_memory_ranges[i].address, physical);

                break;
            }

            case ALO_PHYSICAL_MEMORY_TYPE_KERNEL: {
                error = alo_arch_page_map_range(&allocator, &top_level, boot_info.kernel_physical_base, boot_info.kernel_virtual_base, boot_info.kernel_size);
                if(error) return error;

                gen_uintptr_t physical = 0;
                error = alo_arch_translate_address(&top_level, boot_info.kernel_virtual_base, &physical);
                if(error) return error;

                gen_log_formatted(GEN_LOG_LEVEL_DEBUG, "", "Software traversed: %p -> %p", boot_info.kernel_virtual_base, physical);

                break;
            }
            case ALO_PHYSICAL_MEMORY_TYPE_KERNEL_STACK: {
                error = alo_arch_page_map_range(&allocator, &top_level, boot_info.physical_memory_ranges[i].address, boot_info.kernel_virtual_base + boot_info.physical_memory_ranges[i].address, boot_info.physical_memory_ranges[i].size / ALO_PHYSICAL_PAGE_SIZE);
                if(error) return error;

                gen_uintptr_t physical = 0;
                error = alo_arch_translate_address(&top_level, boot_info.kernel_virtual_base + boot_info.physical_memory_ranges[i].address, &physical);
                if(error) return error;

                gen_log_formatted(GEN_LOG_LEVEL_DEBUG, "", "Software traversed: %p -> %p", boot_info.kernel_virtual_base + boot_info.physical_memory_ranges[i].address, physical);

                break;
            }
        }
    }

    error = alo_arch_page_flush(top_level);
    if(error) return error;

    return GEN_NULL;
}

extern GEN_NORETURN GEN_USED void _start(ALO_BOOT_SIGNATURE);
GEN_NORETURN GEN_USED void _start(ALO_BOOT_SIGNATURE) {
    ALO_BOOT_BLOCK;

	GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) _start, GEN_FILE_NAME);
	if(error) gen_error_abort_with_error(error,"alonira-entry");

    error = gen_main(ALO_BOOT_PASSTHROUGH);
    if(error) gen_error_abort_with_error(error, "alonira-entry");

    error = gen_error_attach_backtrace(GEN_ERROR_INVALID_CONTROL, GEN_LINE_NUMBER, "Reached end of `_start`");
    gen_error_abort_with_error(error, "alonira-entry");
}
