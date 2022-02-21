// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 TTG <prs.ttg+alonira@pm.me>

#include "include/kdiagnostic.h"
#include "include/vga.h"

#include <alocom.h>
#include <alog.h>
#include <alostring.h>

static alo_vga_dimension_t alo_internal_cursor_x = 0;
static alo_vga_dimension_t alo_internal_cursor_y = 0;

static const alo_vga_color_t color_table[] = {
	ALO_VGA_COLOR_BLACK,
	ALO_VGA_COLOR_WHITE,
	ALO_VGA_COLOR_CYAN,
	ALO_VGA_COLOR_BLUE,
	ALO_VGA_COLOR_YELLOW,
	ALO_VGA_COLOR_RED,
	ALO_VGA_COLOR_MAGENTA};
static const char* const level_name_table[] = {
	"TRACE: ",
	"PERFORMANCE: ",
	"NOTE: ",
	"INFO: ",
	"WARNING: ",
	"ERROR: ",
	"FATAL: "};

void alog(const alo_log_level_t level, const char* const restrict string) {
	alo_internal_cursor_x = 0;

	unsigned long string_length = 0;
	alo_error_t error = alo_string_length(string, ALO_STRING_NO_BOUND, ALO_STRING_NO_BOUND, &string_length);
	ALO_REQUIRE_NO_ERROR_K(error);

	unsigned long level_name_length = 0;
	error = alo_string_length(level_name_table[level], ALO_STRING_NO_BOUND, ALO_STRING_NO_BOUND, &level_name_length);
	ALO_REQUIRE_NO_ERROR_K(error);

	error = alo_vga_put_string_at_colored(level_name_table[level], level_name_length, color_table[level], ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_BLACK), alo_internal_cursor_x, alo_internal_cursor_y);
	ALO_REQUIRE_NO_ERROR_K(error);

	alo_internal_cursor_x += level_name_length;

	error = alo_vga_put_string_at_colored(string, string_length, color_table[level], ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_BLACK), alo_internal_cursor_x, alo_internal_cursor_y);
	ALO_REQUIRE_NO_ERROR_K(error);

	++alo_internal_cursor_y;
}
