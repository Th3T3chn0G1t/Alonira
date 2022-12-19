// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#ifndef ALO_VGA_H
#define ALO_VGA_H

#include <gencommon.h>

typedef enum {
	ALO_VGA_COLOR_GRAY,
	ALO_VGA_COLOR_BLUE,
	ALO_VGA_COLOR_GREEN,
	ALO_VGA_COLOR_CYAN,
	ALO_VGA_COLOR_RED,
	ALO_VGA_COLOR_MAGENTA,
	ALO_VGA_COLOR_YELLOW,
	ALO_VGA_COLOR_WHITE,

	ALO_VGA_COLOR_DARK_GRAY,
	ALO_VGA_COLOR_DARK_BLUE,
	ALO_VGA_COLOR_DARK_GREEN,
	ALO_VGA_COLOR_DARK_CYAN,
	ALO_VGA_COLOR_DARK_RED,
	ALO_VGA_COLOR_DARK_MAGENTA,
	ALO_VGA_COLOR_DARK_YELLOW,
	ALO_VGA_COLOR_DARK_WHITE
} alo_vga_color_t;

typedef unsigned short alo_vga_dimension_t;
typedef gen_size_t alo_vga_offset_t;
typedef unsigned short alo_vga_character_t;

// TODO: Declare as a pointer-to-array with the correct size
#define ALO_VGA_ADDRESS ((unsigned short*) 0xB8000)
#define ALO_VGA_WIDTH ((alo_vga_dimension_t) 80)
#define ALO_VGA_HEIGHT ((alo_vga_dimension_t) 25)
#define ALO_VGA_LENGTH (ALO_VGA_WIDTH * ALO_VGA_HEIGHT)

extern gen_error_t* alo_vga_put_char_at_colored(const char c, const alo_vga_color_t foreground, const alo_vga_color_t background, const alo_vga_dimension_t x, const alo_vga_dimension_t y);
extern gen_error_t* alo_vga_put_string_at_colored(const char* const restrict string, const gen_size_t length, const alo_vga_color_t foreground, const alo_vga_color_t background, const alo_vga_dimension_t x, const alo_vga_dimension_t y);

#endif
