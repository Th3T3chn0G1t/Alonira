// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 TTG <prs.ttg+alonira@pm.me>

#include "include/vga.h"

alo_error_t alo_vga_put_char_at_colored(const char c, const alo_vga_color_t foreground, const alo_vga_color_t background, const alo_vga_dimension_t x, const alo_vga_dimension_t y) {
	ALO_FRAME_BEGIN(alo_vga_put_char_at_colored);

	if(foreground > ALO_VGA_COLOR_LAST) ALO_ERROR_OUT(ALO_INVALID_PARAMETER, "`foreground` was not a valid color");
	if(background > ALO_VGA_COLOR_LAST) ALO_ERROR_OUT(ALO_INVALID_PARAMETER, "`background` was not a valid color");
	const alo_vga_offset_t offset = x + y * ALO_VGA_WIDTH;
	if(offset > ALO_VGA_LENGTH) ALO_ERROR_OUT(ALO_OUT_OF_BOUNDS, "Calculated character offset is outside of VGA buffer bounds");

	ALO_VGA_ADDRESS[offset] = (alo_vga_character_t) c | (alo_vga_character_t) ((alo_vga_character_t) ((alo_vga_color_t) foreground | (alo_vga_color_t) background << 4) << 8);

	ALO_ALL_OK;
}

alo_error_t alo_vga_put_string_at_colored(const char* const restrict string, const size_t length, const alo_vga_color_t foreground, const alo_vga_color_t background, const alo_vga_dimension_t x, const alo_vga_dimension_t y) {
	ALO_FRAME_BEGIN(alo_vga_put_string_at_colored);

	if(foreground > ALO_VGA_COLOR_LAST) ALO_ERROR_OUT(ALO_INVALID_PARAMETER, "`foreground` was not a valid color");
	if(background > ALO_VGA_COLOR_LAST) ALO_ERROR_OUT(ALO_INVALID_PARAMETER, "`background` was not a valid color");
	ALO_NULL_CHECK(string);
	if(x > ALO_VGA_WIDTH) ALO_ERROR_OUT(ALO_OUT_OF_BOUNDS, "`x` is outside of VGA buffer bounds");
	if(y > ALO_VGA_HEIGHT) ALO_ERROR_OUT(ALO_OUT_OF_BOUNDS, "`y` is outside of VGA buffer bounds");
	const alo_vga_offset_t offset = x + y * ALO_VGA_WIDTH;
	const alo_vga_offset_t end = length;
	if(end > ALO_VGA_LENGTH) ALO_ERROR_OUT(ALO_OUT_OF_BOUNDS, "Calculated character offset is outside of VGA buffer bounds");

	for(size_t i = 0; i < length; ++i) {
		alo_error_t error = alo_vga_put_char_at_colored(string[i], foreground, background, (alo_vga_dimension_t) (offset + i) % ALO_VGA_WIDTH, (alo_vga_dimension_t) (offset + i) / ALO_VGA_WIDTH);
		ALO_ERROR_OUT_IF(error, "`alo_vga_put_char_colored` failed");
	}

	ALO_ALL_OK;
}
