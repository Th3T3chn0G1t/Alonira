// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 TTG <prs.ttg+alonira@pm.me>

#include "include/boot.h"
#include "include/kdiagnostic.h"
#include "include/vga.h"

#include <alocom.h>

ALO_DIAGNOSTIC_REGION_BEGIN
#pragma clang diagnostic ignored "-Wmissing-prototypes"
#pragma clang diagnostic ignored "-Wreserved-identifier"
noreturn __unused void _start(ALO_BOOT_SIGNATURE) {
	alo_error_t error = alo_vga_put_string_at_colored("FATAL: ", 7, ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_RED), ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_BLACK), 0, 0);
	ALO_REQUIRE_NO_ERROR_K(error);
	error = alo_vga_put_string_at_colored("OS not found", 12, ALO_VGA_COLOR_LIGHT(ALO_VGA_COLOR_WHITE), ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_BLACK), 7, 0);
	ALO_REQUIRE_NO_ERROR_K(error);

	hang();
}
ALO_DIAGNOSTIC_REGION_END
