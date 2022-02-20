// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 TTG <prs.ttg+alonira@pm.me>

#include "include/kdiagnostic.h"
#include "include/vga.h"

#include <alocom.h>
#include <alostring.h>

static const char alo_internal_panic_message_head[] = "ALONIRA KERNEL PANIC";

void panic(const alo_error_t error) {
	// We can't check errors here - let's just hope we didn't mess up
	(void) alo_vga_put_string_at_colored(alo_internal_panic_message_head, sizeof(alo_internal_panic_message_head) - 1, ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_RED), ALO_VGA_COLOR_LIGHT(ALO_VGA_COLOR_WHITE), ALO_VGA_WIDTH / 2 - (sizeof(alo_internal_panic_message_head) - 1) / 2, 5);

	const char* error_name = alo_error_name(error);
	unsigned long error_name_length = 0;
	(void) alo_string_length(error_name, ALO_STRING_NO_BOUND, ALO_STRING_NO_BOUND, &error_name_length);
	(void) alo_vga_put_string_at_colored(error_name, error_name_length, ALO_VGA_COLOR_LIGHT(ALO_VGA_COLOR_WHITE), ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_BLACK), ALO_VGA_WIDTH / 2 - (alo_vga_dimension_t) error_name_length / 2, 7);

	const char* error_description = alo_error_description(error);
	unsigned long error_description_length = 0;
	(void) alo_string_length(error_description, ALO_STRING_NO_BOUND, ALO_STRING_NO_BOUND, &error_description_length);
	(void) alo_vga_put_string_at_colored(error_description, error_description_length, ALO_VGA_COLOR_LIGHT(ALO_VGA_COLOR_WHITE), ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_BLACK), ALO_VGA_WIDTH / 2 - (alo_vga_dimension_t) error_description_length / 2, 8);

	hang();
}
