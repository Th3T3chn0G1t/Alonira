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
	ALO_VGA_COLOR_LIGHT(ALO_VGA_COLOR_BLACK),
	ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_WHITE),
	ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_GREEN),
	ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_CYAN),
	ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_BLUE),
	ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_YELLOW),
	ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_RED),
	ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_MAGENTA)};
static const char* const level_name_table[] = {
	"TRACE: ",
	"PERFORMANCE: ",
	"DEBUG: ",
	"NOTE: ",
	"INFO: ",
	"WARNING: ",
	"ERROR: ",
	"FATAL: "};

void alog(const alo_log_level_t level, const char* const restrict string) {
	ALO_FRAME_BEGIN(alog);

	alo_internal_cursor_x = 0;

	size_t string_length = 0;
	alo_error_t error = alo_string_length(string, ALO_STRING_NO_BOUND, ALO_STRING_NO_BOUND, &string_length);
	ALO_REQUIRE_NO_ERROR_K(error);

	size_t level_name_length = 0;
	error = alo_string_length(level_name_table[level], ALO_STRING_NO_BOUND, ALO_STRING_NO_BOUND, &level_name_length);
	ALO_REQUIRE_NO_ERROR_K(error);

	error = alo_vga_put_string_at_colored(level_name_table[level], level_name_length, color_table[level], ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_BLACK), alo_internal_cursor_x, alo_internal_cursor_y);
	ALO_REQUIRE_NO_ERROR_K(error);

	alo_internal_cursor_x += level_name_length;

	error = alo_vga_put_string_at_colored(string, string_length, ALO_VGA_COLOR_LIGHT(ALO_VGA_COLOR_WHITE), ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_BLACK), alo_internal_cursor_x, alo_internal_cursor_y);
	ALO_REQUIRE_NO_ERROR_K(error);

	++alo_internal_cursor_y;

	if(level >= ERROR) atrace;
}

static const char hex_table[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

void alogf(const alo_log_level_t level, const char* const restrict string, ...) {
	ALO_FRAME_BEGIN(alogf);

	alo_internal_cursor_x = 0;

	size_t level_name_length = 0;
	alo_error_t error = alo_string_length(level_name_table[level], ALO_STRING_NO_BOUND, ALO_STRING_NO_BOUND, &level_name_length);
	ALO_REQUIRE_NO_ERROR_K(error);

	error = alo_vga_put_string_at_colored(level_name_table[level], level_name_length, color_table[level], ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_BLACK), alo_internal_cursor_x, alo_internal_cursor_y);
	ALO_REQUIRE_NO_ERROR_K(error);

	alo_internal_cursor_x += level_name_length;

	va_list list;
	va_start(list, string);

	size_t string_length = 0;
	error = alo_string_length(string, ALO_STRING_NO_BOUND, ALO_STRING_NO_BOUND, &string_length);
	ALO_REQUIRE_NO_ERROR_K(error);

	for(size_t i = 0; i < string_length; ++i) {
		char c = string[i];

		if(c != '%') {
			error = alo_vga_put_char_at_colored(c, ALO_VGA_COLOR_LIGHT(ALO_VGA_COLOR_WHITE), ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_BLACK), alo_internal_cursor_x++, alo_internal_cursor_y);
			ALO_REQUIRE_NO_ERROR_K(error);
			continue;
		}

		c = string[++i];

		if(c == 'l' || c == 'z' || c == 't' || c == 'j') {
			switch(string[++i]) {
				case 'i':
				case 'd': {
					long accum = va_arg(list, long);
					char out[20] = {0};
					size_t idx = 0;
					do {
						out[idx++] = '0' + (accum % 10);
						accum /= 10;
					} while(accum);
					for(size_t j = sizeof(out) - 1; j != SIZE_MAX; --j) {
						if(!out[j]) continue;
						error = alo_vga_put_char_at_colored(out[j], ALO_VGA_COLOR_LIGHT(ALO_VGA_COLOR_WHITE), ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_BLACK), alo_internal_cursor_x++, alo_internal_cursor_y);
						ALO_REQUIRE_NO_ERROR_K(error);
					}
					continue;
				}
				case 'o': {
					size_t accum = va_arg(list, size_t);
					char out[22] = {0};
					size_t idx = 0;
					error = alo_vga_put_char_at_colored('0', ALO_VGA_COLOR_LIGHT(ALO_VGA_COLOR_WHITE), ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_BLACK), alo_internal_cursor_x++, alo_internal_cursor_y);
					ALO_REQUIRE_NO_ERROR_K(error);
					do {
						out[idx++] = '0' + accum % 8;
						accum >>= 3;
					} while(accum);
					for(size_t j = sizeof(out) - 1; j != SIZE_MAX; --j) {
						if(!out[j]) continue;
						error = alo_vga_put_char_at_colored(out[j], ALO_VGA_COLOR_LIGHT(ALO_VGA_COLOR_WHITE), ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_BLACK), alo_internal_cursor_x++, alo_internal_cursor_y);
						ALO_REQUIRE_NO_ERROR_K(error);
					}
					continue;
				}
				case 'x': {
					size_t accum = va_arg(list, size_t);
					char out[16] = {0};
					size_t idx = 0;
					error = alo_vga_put_char_at_colored('0', ALO_VGA_COLOR_LIGHT(ALO_VGA_COLOR_WHITE), ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_BLACK), alo_internal_cursor_x++, alo_internal_cursor_y);
					ALO_REQUIRE_NO_ERROR_K(error);
					error = alo_vga_put_char_at_colored('x', ALO_VGA_COLOR_LIGHT(ALO_VGA_COLOR_WHITE), ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_BLACK), alo_internal_cursor_x++, alo_internal_cursor_y);
					ALO_REQUIRE_NO_ERROR_K(error);
					do {
						out[idx++] = hex_table[accum % 16];
						accum >>= 4;
					} while(accum);
					for(size_t j = sizeof(out) - 1; j != SIZE_MAX; --j) {
						if(!out[j]) continue;
						error = alo_vga_put_char_at_colored(out[j], ALO_VGA_COLOR_LIGHT(ALO_VGA_COLOR_WHITE), ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_BLACK), alo_internal_cursor_x++, alo_internal_cursor_y);
						ALO_REQUIRE_NO_ERROR_K(error);
					}
					continue;
				}
				case 'u': {
					size_t accum = va_arg(list, size_t);
					char out[20] = {0};
					size_t idx = 0;
					do {
						out[idx++] = '0' + (accum % 10);
						accum /= 10;
					} while(accum);
					for(size_t j = sizeof(out) - 1; j != SIZE_MAX; --j) {
						if(!out[j]) continue;
						error = alo_vga_put_char_at_colored(out[j], ALO_VGA_COLOR_LIGHT(ALO_VGA_COLOR_WHITE), ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_BLACK), alo_internal_cursor_x++, alo_internal_cursor_y);
						ALO_REQUIRE_NO_ERROR_K(error);
					}
					continue;
				}
				default: {
					ALO_REQUIRE_NO_REACH_K;
				}
			}
		}
		else {
			switch(c) {
				case '%': {
					error = alo_vga_put_char_at_colored('%', ALO_VGA_COLOR_LIGHT(ALO_VGA_COLOR_WHITE), ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_BLACK), alo_internal_cursor_x++, alo_internal_cursor_y);
					ALO_REQUIRE_NO_ERROR_K(error);
					continue;
				}
				case 'c': {
					error = alo_vga_put_char_at_colored((char) va_arg(list, int), ALO_VGA_COLOR_LIGHT(ALO_VGA_COLOR_WHITE), ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_BLACK), alo_internal_cursor_x++, alo_internal_cursor_y);
					ALO_REQUIRE_NO_ERROR_K(error);
					continue;
				}
				case 's': {
					const char* const str = va_arg(list, char*);
					size_t len = 0;
					error = alo_string_length(str, ALO_STRING_NO_BOUND, ALO_STRING_NO_BOUND, &len);
					ALO_REQUIRE_NO_ERROR_K(error);
					error = alo_vga_put_string_at_colored(str, len, ALO_VGA_COLOR_LIGHT(ALO_VGA_COLOR_WHITE), ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_BLACK), alo_internal_cursor_x, alo_internal_cursor_y);
					alo_internal_cursor_x += len;
					ALO_REQUIRE_NO_ERROR_K(error);
					continue;
				}
				case 'i':
				case 'd': {
					int accum = va_arg(list, int);
					char out[10] = {0};
					size_t idx = 0;
					do {
						out[idx++] = '0' + (accum % 10);
						accum /= 10;
					} while(accum);
					for(size_t j = sizeof(out) - 1; j != SIZE_MAX; --j) {
						if(!out[j]) continue;
						error = alo_vga_put_char_at_colored(out[j], ALO_VGA_COLOR_LIGHT(ALO_VGA_COLOR_WHITE), ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_BLACK), alo_internal_cursor_x++, alo_internal_cursor_y);
						ALO_REQUIRE_NO_ERROR_K(error);
					}
					continue;
				}
				case 'o': {
					unsigned int accum = va_arg(list, unsigned int);
					char out[11] = {0};
					size_t idx = 0;
					error = alo_vga_put_char_at_colored('0', ALO_VGA_COLOR_LIGHT(ALO_VGA_COLOR_WHITE), ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_BLACK), alo_internal_cursor_x++, alo_internal_cursor_y);
					ALO_REQUIRE_NO_ERROR_K(error);
					do {
						out[idx++] = '0' + accum % 8;
						accum >>= 3;
					} while(accum);
					for(size_t j = sizeof(out) - 1; j != SIZE_MAX; --j) {
						if(!out[j]) continue;
						error = alo_vga_put_char_at_colored(out[j], ALO_VGA_COLOR_LIGHT(ALO_VGA_COLOR_WHITE), ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_BLACK), alo_internal_cursor_x++, alo_internal_cursor_y);
						ALO_REQUIRE_NO_ERROR_K(error);
					}
					continue;
				}
				case 'x': {
					unsigned int accum = va_arg(list, unsigned int);
					char out[8] = {0};
					size_t idx = 0;
					error = alo_vga_put_char_at_colored('0', ALO_VGA_COLOR_LIGHT(ALO_VGA_COLOR_WHITE), ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_BLACK), alo_internal_cursor_x++, alo_internal_cursor_y);
					ALO_REQUIRE_NO_ERROR_K(error);
					error = alo_vga_put_char_at_colored('x', ALO_VGA_COLOR_LIGHT(ALO_VGA_COLOR_WHITE), ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_BLACK), alo_internal_cursor_x++, alo_internal_cursor_y);
					ALO_REQUIRE_NO_ERROR_K(error);
					do {
						out[idx++] = hex_table[accum % 16];
						accum >>= 4;
					} while(accum);
					for(size_t j = sizeof(out) - 1; j != SIZE_MAX; --j) {
						if(!out[j]) continue;
						error = alo_vga_put_char_at_colored(out[j], ALO_VGA_COLOR_LIGHT(ALO_VGA_COLOR_WHITE), ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_BLACK), alo_internal_cursor_x++, alo_internal_cursor_y);
						ALO_REQUIRE_NO_ERROR_K(error);
					}
					continue;
				}
				case 'u': {
					unsigned int accum = va_arg(list, unsigned int);
					char out[10] = {0};
					size_t idx = 0;
					do {
						out[idx++] = '0' + (accum % 10);
						accum /= 10;
					} while(accum);
					for(size_t j = sizeof(out) - 1; j != SIZE_MAX; --j) {
						if(!out[j]) continue;
						error = alo_vga_put_char_at_colored(out[j], ALO_VGA_COLOR_LIGHT(ALO_VGA_COLOR_WHITE), ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_BLACK), alo_internal_cursor_x++, alo_internal_cursor_y);
						ALO_REQUIRE_NO_ERROR_K(error);
					}
					continue;
				}
				case 'p': {
					uintptr_t accum = (uintptr_t) va_arg(list, void*);
					char out[16] = {'0'};
					size_t idx = 0;
					error = alo_vga_put_char_at_colored('0', ALO_VGA_COLOR_LIGHT(ALO_VGA_COLOR_WHITE), ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_BLACK), alo_internal_cursor_x++, alo_internal_cursor_y);
					ALO_REQUIRE_NO_ERROR_K(error);
					error = alo_vga_put_char_at_colored('x', ALO_VGA_COLOR_LIGHT(ALO_VGA_COLOR_WHITE), ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_BLACK), alo_internal_cursor_x++, alo_internal_cursor_y);
					ALO_REQUIRE_NO_ERROR_K(error);
					do {
						out[idx++] = hex_table[accum % 16];
						accum >>= 4;
					} while(accum);
					for(size_t j = sizeof(out) - 1; j != SIZE_MAX; --j) {
						error = alo_vga_put_char_at_colored(out[j], ALO_VGA_COLOR_LIGHT(ALO_VGA_COLOR_WHITE), ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_BLACK), alo_internal_cursor_x++, alo_internal_cursor_y);
						ALO_REQUIRE_NO_ERROR_K(error);
					}
					continue;
				}
				default: {
					ALO_REQUIRE_NO_REACH_K;
				}
			}
		}
	}

	++alo_internal_cursor_y;
	va_end(list);

	if(level >= ERROR) atrace;
}
