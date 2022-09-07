// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include "include/boot.h"
#include "include/gdt.h"
#include "include/idt.h"
#include "include/kdiagnostic.h"
#include "include/serial.h"
#include "include/tss.h"

#include <gencommon.h>
#include <genlog.h>
#include <alocommon.h>

static gen_error_t* gen_main(ALO_BOOT_SIGNATURE) {
	gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_main, GEN_FILE_NAME);
    if(error) return error;

	error = alo_serial_set(ALO_SERIAL_COM1, 9600, ALO_SERIAL_DATA_WIDTH_8, ALO_SERIAL_STOP_BIT_1, ALO_SERIAL_PARITY_NONE, ALO_SERIAL_INTERRUPT_NONE);
    if(error) return error;

	error = alo_gdt_install();
    if(error) return error;

	error = alo_tss_install();
    if(error) return error;

	error = alo_idt_install();
    if(error) return error;

	error = gen_log(GEN_LOG_LEVEL_INFO, "alonira-entry", "Hello, Alonira!");
    if(error) return error;

	// alo_registers_t registers = {0};
	// ALO_STORE_REGISTERS(registers);

	// alo_panic_with_registers(GEN_ERROR_NOT_IMPLEMENTED, "OS not found :^)", registers);

    return NULL;
}

GEN_NORETURN GEN_UNUSED void _start(ALO_BOOT_SIGNATURE) {
    // TODO: Check boot magic

	ALO_ASM_BLOCK(ALO_ASM(cli));

	gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) _start, GEN_FILE_NAME);
	if(error) {
        gen_error_print("alonira-entry", error, GEN_ERROR_SEVERITY_FATAL);
        gen_error_abort();
    }

    error = gen_main(boot_data, magic);
	if(error) {
        gen_error_print("alonira-entry", error, GEN_ERROR_SEVERITY_FATAL);
        gen_error_abort();
    }

    alo_hang();
}
