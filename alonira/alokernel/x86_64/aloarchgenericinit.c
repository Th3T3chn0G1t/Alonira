// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include <gencommon.h>
#include <genlog.h>
#include <genmemory.h>

#include "include/aloarchgeneric.h"
#include "include/aloarchgenericboot.h"

#include "include/alogdt.h"
#include "include/aloidt.h"
#include "include/alotss.h"

#include "include/aloacpi.h"

#include "include/aloserial.h"

gen_error_t* alo_arch_generic_init(ALO_BOOT_SIGNATURE, alo_boot_info_t* const restrict out_boot_info) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) alo_arch_generic_init, GEN_FILE_NAME);
    if(error) return error;

    error = gen_log(GEN_LOG_LEVEL_INFO, "alonira-archgenericinit", "Alonira (x86_64) initializing - hold onto your hats...");
    if(error) return error;

    if(magic != ULTRA_MAGIC) return gen_error_attach_backtrace_formatted(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "Invalid boot magic `%ui`, expected `%ui`", magic, ULTRA_MAGIC);

    error = alo_serial_set(ALO_SERIAL_COM1, 9600, ALO_SERIAL_DATA_WIDTH_8, ALO_SERIAL_STOP_BIT_1, ALO_SERIAL_PARITY_NONE, ALO_SERIAL_INTERRUPT_NONE);
    if(error) return error;

    error = alo_gdt_install();
    if(error) return error;

    error = alo_tss_install();
    if(error) return error;

    error = alo_idt_install();
    if(error) return error;

    // GEN_ASM_BLOCK(GEN_ASM(sti));

    alo_rdsp_descriptor_t* rdsp = GEN_NULL;
    (void) rdsp;

    out_boot_info->protocol_version = (gen_version_t) {boot_data->protocol_major, boot_data->protocol_minor, 0};

    struct ultra_attribute_header* attribute = boot_data->attributes;
    for(gen_size_t i = 0; i < boot_data->attribute_count; ++i) {
        switch(attribute->type) {
            case ULTRA_ATTRIBUTE_INVALID: return gen_error_attach_backtrace_formatted(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "Invalid boot attribute at index `%uz`", i);
            case ULTRA_ATTRIBUTE_PLATFORM_INFO: {
                struct ultra_platform_info_attribute* platform_info = (struct ultra_platform_info_attribute*) attribute;

                switch(platform_info->platform_type) {
                    case ULTRA_PLATFORM_INVALID: return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "Invalid boot mode");
                    case ULTRA_PLATFORM_BIOS: out_boot_info->arch_info.mode = ALO_BOOT_MODE_BIOS; break;
                    case ULTRA_PLATFORM_UEFI: out_boot_info->arch_info.mode = ALO_BOOT_MODE_UEFI; break;
                    default: gen_log(GEN_LOG_LEVEL_WARNING, "alonira-archgenericinit", "Unknown boot type");
                }

                out_boot_info->loader_version = (gen_version_t) {platform_info->loader_major, platform_info->loader_minor, 0};

                rdsp = (alo_rdsp_descriptor_t*) platform_info->acpi_rsdp_address;

                error = gen_memory_copy(out_boot_info->loader_name, sizeof(out_boot_info->loader_name), platform_info->loader_name, sizeof(platform_info->loader_name), sizeof(platform_info->loader_name));
                if(error) return error;

                break;
            }
            case ULTRA_ATTRIBUTE_KERNEL_INFO: {
                
                break;
            }
            case ULTRA_ATTRIBUTE_MEMORY_MAP: {
                
                break;
            }
            case ULTRA_ATTRIBUTE_MODULE_INFO: {
                
                break;
            }
            case ULTRA_ATTRIBUTE_COMMAND_LINE: {
                
                break;
            }
            case ULTRA_ATTRIBUTE_FRAMEBUFFER_INFO: {
                
                break;
            }
        }

        attribute = ULTRA_NEXT_ATTRIBUTE(attribute);
    }

    // qemu/bochs shutdown
    // alo_port_out_word(0xB004, 0x2000);

    return GEN_NULL;
}
