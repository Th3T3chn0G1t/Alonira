// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 TTG <prs.ttg+alonira@pm.me>

#include <alocom.h>
ALO_DIAGNOSTIC_REGION_BEGIN
ALO_DIAGNOSTIC_IGNORE_ALL
#include <stivale2.h>
ALO_DIAGNOSTIC_REGION_END

static unsigned char stack[8192];

ALO_DIAGNOSTIC_REGION_BEGIN
#pragma clang diagnostic ignored "-Wgnu-binary-literal"
__attribute__((section(".stivale2hdr"), used)) static struct stivale2_header stivale_header = {
	.entry_point = 0,
	.stack = (unsigned long) stack + sizeof(stack),
	.flags = 0b00011110,
	.tags = 0};

#include "include/vga.h"

#pragma clang diagnostic ignored "-Wmissing-prototypes"
#pragma clang diagnostic ignored "-Wreserved-identifier"
noreturn __unused void _start(__unused const struct stivale2_struct* const restrict bootdata) {
	alo_error_t error = alo_vga_put_string_at_colored("FATAL: ", 7, ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_RED), ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_BLACK), 0, 0);
	if(error) hang();
	error = alo_vga_put_string_at_colored("OS not found", 12, ALO_VGA_COLOR_LIGHT(ALO_VGA_COLOR_WHITE), ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_BLACK), 7, 0);
	if(error) hang();

	hang();
}
ALO_DIAGNOSTIC_REGION_END
