// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 TTG <prs.ttg+alonira@pm.me>

#ifndef ALO_VGA_H
#define ALO_VGA_H

#include <alocom.h>

enum {
	ALO_VGA_COLOR_BLACK = 0,
	ALO_VGA_COLOR_BLUE,
	ALO_VGA_COLOR_GREEN,
	ALO_VGA_COLOR_CYAN,
	ALO_VGA_COLOR_RED,
	ALO_VGA_COLOR_MAGENTA,
	ALO_VGA_COLOR_YELLOW,
	ALO_VGA_COLOR_WHITE
};

typedef unsigned char alo_vga_color_t;
typedef unsigned short alo_vga_dimension_t;
typedef size_t alo_vga_offset_t;
typedef unsigned short alo_vga_character_t;

#define ALO_VGA_ADDRESS ((unsigned short*) 0xB8000)
#define ALO_VGA_WIDTH ((alo_vga_dimension_t) 80)
#define ALO_VGA_HEIGHT ((alo_vga_dimension_t) 25)
#define ALO_VGA_LENGTH (ALO_VGA_WIDTH * ALO_VGA_HEIGHT)

#define ALO_VGA_COLOR(color) ((alo_vga_color_t) (color))
#define ALO_VGA_COLOR_LIGHT(color) ALO_VGA_COLOR(color + 8)
#define ALO_VGA_COLOR_DARK(color) ALO_VGA_COLOR(color)
#define ALO_VGA_COLOR_LAST ALO_VGA_COLOR_LIGHT(ALO_VGA_COLOR_WHITE)

ALO_ERRORABLE alo_vga_put_char_at_colored(const char c, const alo_vga_color_t foreground, const alo_vga_color_t background, const alo_vga_dimension_t x, const alo_vga_dimension_t y);
ALO_ERRORABLE alo_vga_put_string_at_colored(const char* const restrict string, const size_t length, const alo_vga_color_t foreground, const alo_vga_color_t background, const alo_vga_dimension_t x, const alo_vga_dimension_t y);

#endif
