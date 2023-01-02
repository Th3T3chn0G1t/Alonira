// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include <gencommon.h>

#include "include/aloarchgeneric.h"
#include "include/aloboot.h"

#include "include/alogdt.h"
#include "include/aloidt.h"
#include "include/alotss.h"

#include "include/aloserial.h"

gen_error_t* alo_arch_generic_init(ALO_BOOT_SIGNATURE) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) alo_arch_generic_init, GEN_FILE_NAME);
    if(error) return error;

    error = alo_serial_set(ALO_SERIAL_COM1, 9600, ALO_SERIAL_DATA_WIDTH_8, ALO_SERIAL_STOP_BIT_1, ALO_SERIAL_PARITY_NONE, ALO_SERIAL_INTERRUPT_NONE);
    if(error) return error;

    error = alo_gdt_install();
    if(error) return error;

    error = alo_tss_install();
    if(error) return error;

    error = alo_idt_install();
    if(error) return error;

    // qemu/bochs shutdown
    // alo_port_out_word(0xB004, 0x2000);

    return GEN_NULL;
}
