// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include "include/boot.h"
#include "include/gdt.h"
#include "include/idt.h"
#include "include/kdiagnostic.h"
#include "include/serial.h"
#include "include/tss.h"
#include "include/vga.h"

#include <gencommon.h>
#include <genlog.h>
#include <genstring.h>


static gen_error_t* gen_main(ALO_BOOT_SIGNATURE) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_main, GEN_FILE_NAME);
    if(error) return error;

	error = alo_serial_set(ALO_SERIAL_COM1, 9600, ALO_SERIAL_DATA_WIDTH_8, ALO_SERIAL_STOP_BIT_1, ALO_SERIAL_PARITY_NONE, ALO_SERIAL_INTERRUPT_NONE);
    if(error) return error;

	error = alo_gdt_install();
    if(error) return error;

	error = alo_tss_install();
    if(error) return error;

//	error = alo_idt_install();
//    if(error) return error;

    error = alo_serial_send_string(ALO_SERIAL_COM1, "TEST");
    if(error) return error;

    error = gen_log(GEN_LOG_LEVEL_INFO, "alonira-entry", "Hello, Alonira!");
    if(error) return error;

    GEN_ASM_BLOCK(GEN_ASM(int $3));

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "OS not found :^)");
}

GEN_PRAGMA(GEN_PRAGMA_DIAGNOSTIC_REGION_BEGIN)
GEN_PRAGMA(GEN_PRAGMA_DIAGNOSTIC_REGION_IGNORE("-Wmissing-prototypes"))
GEN_NORETURN GEN_USED void _start(ALO_BOOT_SIGNATURE) {
GEN_PRAGMA(GEN_PRAGMA_DIAGNOSTIC_REGION_END)
// TODO: Check boot magic

	GEN_ASM_BLOCK(GEN_ASM(cli));

	GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) _start, GEN_FILE_NAME);
	if(error) {
        // TODO: Abort with print
        gen_error_print("alonira-entry", error, GEN_ERROR_SEVERITY_FATAL);
        gen_error_abort();
    }

    error = gen_main(ALO_BOOT_PASSTHROUGH);
	if(error) {
        alo_vga_put_char_at_colored('E', ALO_VGA_COLOR_RED, ALO_VGA_COLOR_WHITE, 0, 0);
        gen_error_print("alonira-entry", error, GEN_ERROR_SEVERITY_FATAL);
        gen_error_abort();
    }

    alo_hang();
}
