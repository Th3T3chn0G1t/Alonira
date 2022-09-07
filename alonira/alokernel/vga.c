// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include "include/vga.h"

gen_error_t* alo_vga_put_char_at_colored(const char c, const alo_vga_color_t foreground, const alo_vga_color_t background, const alo_vga_dimension_t x, const alo_vga_dimension_t y) {
	gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) alo_vga_put_char_at_colored, GEN_FILE_NAME);
	if(error) return error;

	if(foreground > ALO_VGA_COLOR_LAST) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`foreground` was not a valid color");
	if(background > ALO_VGA_COLOR_LAST) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`background` was not a valid color");
	const alo_vga_offset_t offset = x + y * ALO_VGA_WIDTH;
	if(offset > ALO_VGA_LENGTH) return gen_error_attach_backtrace_formatted(GEN_ERROR_OUT_OF_BOUNDS, GEN_LINE_NUMBER, "Calculated character offset `%uz` is outside of VGA buffer bounds", offset);

	ALO_VGA_ADDRESS[offset] = (alo_vga_character_t) c | (alo_vga_character_t) ((alo_vga_character_t) ((alo_vga_color_t) foreground | (alo_vga_color_t) background << 4) << 8);

	return NULL;
}

gen_error_t* alo_vga_put_string_at_colored(const char* const restrict string, const size_t length, const alo_vga_color_t foreground, const alo_vga_color_t background, const alo_vga_dimension_t x, const alo_vga_dimension_t y) {
	gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) alo_vga_put_string_at_colored, GEN_FILE_NAME);
	if(error) return error;

	if(foreground > ALO_VGA_COLOR_LAST) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`foreground` was not a valid color");
	if(background > ALO_VGA_COLOR_LAST) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`background` was not a valid color");
	if(!string) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`string` was `NULL`");
	if(x > ALO_VGA_WIDTH) return gen_error_attach_backtrace_formatted(GEN_ERROR_OUT_OF_BOUNDS, GEN_LINE_NUMBER, "`x` is outside of VGA buffer bounds");
	if(y > ALO_VGA_HEIGHT) return gen_error_attach_backtrace_formatted(GEN_ERROR_OUT_OF_BOUNDS, GEN_LINE_NUMBER, "`y` is outside of VGA buffer bounds");
	const alo_vga_offset_t offset = x + y * ALO_VGA_WIDTH;
	if(offset > ALO_VGA_LENGTH) return gen_error_attach_backtrace_formatted(GEN_ERROR_OUT_OF_BOUNDS, GEN_LINE_NUMBER, "Calculated character offset `%uz` is outside of VGA buffer bounds", offset);

	for(size_t i = 0; i < length; ++i) {
		error = alo_vga_put_char_at_colored(string[i], foreground, background, (alo_vga_dimension_t) (offset + i) % ALO_VGA_WIDTH, (alo_vga_dimension_t) (offset + i) / ALO_VGA_WIDTH);
		if(error) return error;
	}

	return NULL;
}
