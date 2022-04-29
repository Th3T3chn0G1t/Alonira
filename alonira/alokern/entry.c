// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 TTG <prs.ttg+alonira@pm.me>

#include "include/boot.h"
#include "include/gdt.h"
#include "include/kdiagnostic.h"
#include "include/serial.h"

#include <alocom.h>
#include <alog.h>

ALO_DIAGNOSTIC_REGION_BEGIN
#pragma clang diagnostic ignored "-Wmissing-prototypes"
#pragma clang diagnostic ignored "-Wreserved-identifier"
noreturn __unused void _start(ALO_BOOT_SIGNATURE) {
	ALO_FRAME_BEGIN(_start);

	alo_error_t error = alo_serial_set(ALO_SERIAL_COM1, 9600, ALO_SERIAL_DATA_WIDTH_8, ALO_SERIAL_STOP_BIT_1, ALO_SERIAL_PARITY_NONE, ALO_SERIAL_INTERRUPT_NONE);
	ALO_REQUIRE_NO_ERROR_K(error);

	error = alo_gdt_install();
	ALO_REQUIRE_NO_ERROR_K(error);

	alog(INFO, "Hello, Alonira!");

	alog(FATAL, "OS not found :^)");
	panic(ALO_NOT_IMPLEMENTED, "OS not found :^)");
}
ALO_DIAGNOSTIC_REGION_END
