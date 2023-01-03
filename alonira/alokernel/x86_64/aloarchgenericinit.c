// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include <gencommon.h>
#include <genlog.h>

#include "include/aloarchgeneric.h"
#include "include/aloboot.h"

#include "include/alogdt.h"
#include "include/aloidt.h"
#include "include/alotss.h"

#include "include/aloserial.h"

gen_error_t* alo_arch_generic_init(ALO_BOOT_SIGNATURE) {
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

    error = gen_log_formatted(GEN_LOG_LEVEL_DEBUG, "alonira-archgenericinit", "Booting under Ultra protocol revision %uc.%uc", boot_data->protocol_major, boot_data->protocol_minor);
    if(error) return error;

    // qemu/bochs shutdown
    // alo_port_out_word(0xB004, 0x2000);

    return GEN_NULL;
}
