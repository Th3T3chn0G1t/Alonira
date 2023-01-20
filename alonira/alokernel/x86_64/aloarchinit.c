// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include <gencommon.h>
#include <genlog.h>
#include <genmemory.h>
#include <genstring.h>

#include <aloarch.h>

#include "include/exposed/aloarchboot.h"

#include "include/aloarchcommon.h"

#include "include/alogdt.h"
#include "include/aloidt.h"
#include "include/alotss.h"

#include "include/aloacpi.h"

gen_error_t* alo_arch_init(ALO_BOOT_SIGNATURE, alo_boot_info_t* const restrict out_boot_info) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) alo_arch_init, GEN_FILE_NAME);
    if(error) return error;

    error = gen_log(GEN_LOG_LEVEL_INFO, "alonira-archgenericinit", "Alonira (x86_64) initializing - hold onto your hats...");
    if(error) return error;

    if(magic != ULTRA_MAGIC) return gen_error_attach_backtrace_formatted(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "Invalid boot magic `%ui`, expected `%ui`", magic, ULTRA_MAGIC);

    error = alo_gdt_install();
    if(error) return error;

    error = alo_tss_install();
    if(error) return error;

    error = alo_idt_install();
    if(error) return error;

    // TODO: PIC
    // GEN_ASM_BLOCK(GEN_ASM(sti));

    alo_rdsp_descriptor_t* rdsp = GEN_NULL;
    (void) rdsp;

    out_boot_info->protocol_version = (gen_version_t) {boot_data->protocol_major, boot_data->protocol_minor, 0};

    // TODO: Bump this out somewhere
    struct ultra_attribute_header* attribute = boot_data->attributes;
    for(gen_size_t i = 0; i < boot_data->attribute_count; ++i) {
        switch(attribute->type) {
            default: GEN_FALLTHROUGH;
            case ULTRA_ATTRIBUTE_INVALID: return gen_error_attach_backtrace_formatted(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "Invalid boot attribute at index `%uz`", i);
            case ULTRA_ATTRIBUTE_PLATFORM_INFO: {
                error = gen_log(GEN_LOG_LEVEL_DEBUG, "alonira-archgenericinit", "Parsing attribute `ULTRA_ATTRIBUTE_PLATFORM_INFO`");
                if(error) return error;

                struct ultra_platform_info_attribute* platform_info = (struct ultra_platform_info_attribute*) attribute;

                switch(platform_info->platform_type) {
                    default: GEN_FALLTHROUGH;
                    case ULTRA_PLATFORM_INVALID: return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "Invalid boot mode");
                    case ULTRA_PLATFORM_BIOS: out_boot_info->arch_info.mode = ALO_BOOT_MODE_BIOS; break;
                    case ULTRA_PLATFORM_UEFI: out_boot_info->arch_info.mode = ALO_BOOT_MODE_UEFI; break;
                }

                out_boot_info->loader_version = (gen_version_t) {platform_info->loader_major, platform_info->loader_minor, 0};

                rdsp = (alo_rdsp_descriptor_t*) platform_info->acpi_rsdp_address;

                error = gen_memory_copy(out_boot_info->loader_name, sizeof(out_boot_info->loader_name), platform_info->loader_name, sizeof(platform_info->loader_name), sizeof(platform_info->loader_name));
                if(error) return error;

                break;
            }
            case ULTRA_ATTRIBUTE_KERNEL_INFO: {
                error = gen_log(GEN_LOG_LEVEL_DEBUG, "alonira-archgenericinit", "Parsing attribute `ULTRA_ATTRIBUTE_KERNEL_INFO`");
                if(error) return error;

                struct ultra_kernel_info_attribute* kernel_info = (struct ultra_kernel_info_attribute*) attribute;

                out_boot_info->kernel_physical_base = kernel_info->physical_base;
                out_boot_info->kernel_virtual_base = kernel_info->virtual_base;
                out_boot_info->kernel_size = kernel_info->size;

                switch(kernel_info->partition_type) {
                    default: GEN_FALLTHROUGH;
                    case ULTRA_PARTITION_TYPE_INVALID: return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "Invalid boot disk partition schema");
                    case ULTRA_PARTITION_TYPE_RAW: {
                        // NOTE: We are just going to presume "raw" means ISO for now as it is the only
                        //       raw FS that Hyper supports.
                        out_boot_info->kernel_location.location.drive.type = ALO_DRIVE_TYPE_ISOFS;
                        out_boot_info->kernel_location.location.drive.iso.index = kernel_info->disk_index;
                        break;
                    }
                    case ULTRA_PARTITION_TYPE_MBR: {
                        out_boot_info->kernel_location.location.drive.type = ALO_DRIVE_TYPE_MBR;
                        out_boot_info->kernel_location.location.drive.mbr.index = kernel_info->disk_index;
                        out_boot_info->kernel_location.location.mbr.index = kernel_info->partition_index;
                        break;
                    }
                    case ULTRA_PARTITION_TYPE_GPT: {
                        out_boot_info->kernel_location.location.drive.type = ALO_DRIVE_TYPE_GPT;

                        error = gen_memory_copy(out_boot_info->kernel_location.location.drive.gpt.guid, sizeof(out_boot_info->kernel_location.location.drive.gpt.guid), &kernel_info->disk_guid, sizeof(kernel_info->disk_guid), sizeof(kernel_info->disk_guid));
                        if(error) return error;

                        error = gen_memory_copy(out_boot_info->kernel_location.location.gpt.guid, sizeof(out_boot_info->kernel_location.location.gpt.guid), &kernel_info->partition_guid, sizeof(kernel_info->partition_guid), sizeof(kernel_info->partition_guid));
                        if(error) return error;

                        out_boot_info->kernel_location.location.mbr.index = kernel_info->partition_index;
                        break;
                    }
                }

                error = gen_memory_copy(out_boot_info->kernel_location.path, sizeof(out_boot_info->kernel_location.path), kernel_info->fs_path, sizeof(kernel_info->fs_path), sizeof(kernel_info->fs_path));
                if(error) return error;

                break;
            }
            case ULTRA_ATTRIBUTE_MEMORY_MAP: {
                error = gen_log(GEN_LOG_LEVEL_DEBUG, "alonira-archgenericinit", "Parsing attribute `ULTRA_ATTRIBUTE_MEMORY_MAP`");
                if(error) return error;

                struct ultra_memory_map_attribute* memory_map = (struct ultra_memory_map_attribute*) attribute;

                gen_size_t entries = ULTRA_MEMORY_MAP_ENTRY_COUNT(memory_map->header);

                if(entries > ALO_BOOT_MEMORY_RANGE_MAX) return gen_error_attach_backtrace_formatted(GEN_ERROR_TOO_LONG, GEN_LINE_NUMBER, "Memory map contained too many entries (`%uz`), max is `%uz`", entries, ALO_BOOT_MEMORY_RANGE_MAX);

                out_boot_info->physical_memory_range_count = entries;

                for(gen_size_t j = 0; j < entries; ++j) {
                    struct ultra_memory_map_entry* entry = &memory_map->entries[j];

                    alo_physical_memory_type_t type = ALO_PHYSICAL_MEMORY_TYPE_NOT_PRESENT;
                    switch(entry->type) {
                        default: GEN_FALLTHROUGH;
                        case ULTRA_MEMORY_TYPE_INVALID: return gen_error_attach_backtrace_formatted(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "Invalid memory map entry at index `%uz`", j);
                        case ULTRA_MEMORY_TYPE_FREE: type = ALO_PHYSICAL_MEMORY_TYPE_FREE; break;
                        case ULTRA_MEMORY_TYPE_RESERVED: type = ALO_PHYSICAL_MEMORY_TYPE_RESERVED; break;
                        case ULTRA_MEMORY_TYPE_RECLAIMABLE: type = ALO_PHYSICAL_MEMORY_TYPE_RECLAIMABLE; break;
                        case ULTRA_MEMORY_TYPE_NVS: type = ALO_PHYSICAL_MEMORY_TYPE_RESERVED; break;
                        case ULTRA_MEMORY_TYPE_LOADER_RECLAIMABLE: type = ALO_PHYSICAL_MEMORY_TYPE_RECLAIMABLE; break;
                        case ULTRA_MEMORY_TYPE_MODULE: type = ALO_PHYSICAL_MEMORY_TYPE_KERNEL_MODULE; break;
                        case ULTRA_MEMORY_TYPE_KERNEL_STACK: type = ALO_PHYSICAL_MEMORY_TYPE_KERNEL_STACK; break;
                        case ULTRA_MEMORY_TYPE_KERNEL_BINARY: type = ALO_PHYSICAL_MEMORY_TYPE_KERNEL; break;
                    }

                    const char* name = GEN_NULL;
                    switch(type) {
                        case ALO_PHYSICAL_MEMORY_TYPE_NOT_PRESENT: name = "ALO_PHYSICAL_MEMORY_TYPE_NOT_PRESENT"; break;
                        case ALO_PHYSICAL_MEMORY_TYPE_FREE: name = "ALO_PHYSICAL_MEMORY_TYPE_FREE"; break;
                        case ALO_PHYSICAL_MEMORY_TYPE_RECLAIMABLE: name = "ALO_PHYSICAL_MEMORY_TYPE_RECLAIMABLE"; break;
                        case ALO_PHYSICAL_MEMORY_TYPE_RESERVED: name = "ALO_PHYSICAL_MEMORY_TYPE_RESERVED"; break;
                        case ALO_PHYSICAL_MEMORY_TYPE_KERNEL: name = "ALO_PHYSICAL_MEMORY_TYPE_KERNEL"; break;
                        case ALO_PHYSICAL_MEMORY_TYPE_KERNEL_STACK: name = "ALO_PHYSICAL_MEMORY_TYPE_KERNEL_STACK"; break;
                        case ALO_PHYSICAL_MEMORY_TYPE_KERNEL_MODULE: name = "ALO_PHYSICAL_MEMORY_TYPE_KERNEL_MODULE"; break;
                    }

                    error = gen_log_formatted(GEN_LOG_LEVEL_DEBUG, "alonira-archgenericinit", "Memory map entry `%t`: %p -> %p (%uz pages)", name, entry->physical_address, entry->physical_address + entry->size, entry->size / ALO_PHYSICAL_PAGE_SIZE);
                    if(error) return error;

                    out_boot_info->physical_memory_ranges[j] = (alo_physical_memory_range_t) {type, entry->physical_address, entry->size};
                }

                break;
            }
            case ULTRA_ATTRIBUTE_MODULE_INFO: {
                error = gen_log(GEN_LOG_LEVEL_DEBUG, "alonira-archgenericinit", "Parsing attribute `ULTRA_ATTRIBUTE_MODULE_INFO`");
                if(error) return error;

                // TODO: Handle this
                return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Kernel modules are not yet implemented");
            }
            case ULTRA_ATTRIBUTE_COMMAND_LINE: {
                error = gen_log(GEN_LOG_LEVEL_DEBUG, "alonira-archgenericinit", "Parsing attribute `ULTRA_ATTRIBUTE_COMMAND_LINE`");
                if(error) return error;

                struct ultra_command_line_attribute* command_line = (struct ultra_command_line_attribute*) attribute;

                gen_size_t length = 0;
                error = gen_string_length(command_line->text, GEN_STRING_NO_BOUNDS, GEN_STRING_NO_BOUNDS, &length);
                if(error) return error;

                if(length > ALO_BOOT_COMMAND_LINE_MAX) return gen_error_attach_backtrace_formatted(GEN_ERROR_TOO_LONG, GEN_LINE_NUMBER, "Command line contained too many characters (`%uz`), max is `%uz`", length, ALO_BOOT_COMMAND_LINE_MAX);

                error = gen_string_copy(out_boot_info->command_line, sizeof(out_boot_info->command_line), command_line->text, GEN_STRING_NO_BOUNDS, length, length);
                if(error) return error;

                break;
            }
            case ULTRA_ATTRIBUTE_FRAMEBUFFER_INFO: {
                error = gen_log(GEN_LOG_LEVEL_DEBUG, "alonira-archgenericinit", "Parsing attribute `ULTRA_ATTRIBUTE_FRAMEBUFFER_INFO`");
                if(error) return error;

                // TODO: Handle this
                return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Framebuffers are not yet implemented");
            }
        }

        attribute = ULTRA_NEXT_ATTRIBUTE(attribute);
    }

    return GEN_NULL;
}
