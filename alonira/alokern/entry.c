// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 TTG <prs.ttg+alonira@pm.me>

#include "include/boot.h"
#include "include/kdiagnostic.h"
#include "include/vga.h"

#include <alocom.h>
#include <alog.h>
#include <alomemory.h>

ALO_DIAGNOSTIC_REGION_BEGIN
#pragma clang diagnostic ignored "-Wmissing-prototypes"
#pragma clang diagnostic ignored "-Wreserved-identifier"
noreturn __unused void _start(ALO_BOOT_SIGNATURE) {
	ALO_FRAME_BEGIN(_start);

	alo_error_t error = alo_memory_set(ALO_VGA_ADDRESS, ALO_VGA_WIDTH * ALO_VGA_HEIGHT * sizeof(ALO_VGA_ADDRESS[0]), 0);
	ALO_REQUIRE_NO_ERROR_K(error);

	alog(TRACE, "Test");
	alog(PERFORMANCE, "Test");
	alog(DEBUG, "Test");
	alog(NOTE, "Test");
	alog(INFO, "Test");
	alog(WARNING, "Test");
	alog(ERROR, "Test");
	alog(FATAL, "Test");

	static const char str[] = "Hello, world!";
	alogf(DEBUG, "%% %c %s %p %zu", str[0], str, (void*) str, sizeof(str) - 1);

	// panic(ALO_NOT_IMPLEMENTED, "OS not found :^)");
	hang();
}
ALO_DIAGNOSTIC_REGION_END
