// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 TTG <prs.ttg+alonira@pm.me>

#include "include/kdiagnostic.h"
#include "include/serial.h"

#include <alocom.h>
#include <alog.h>
#include <alostring.h>

#define ALO_INTERNAL_KALOG_SERIAL_PORT ALO_SERIAL_COM1

static const char* const level_name_table_colored[] = {
	ALO_ANSI_COLOR_LIGHT(ALO_ANSI_COLOR_BLACK) ALO_ANSI_SEQUENCE(ALO_ANSI_BOLD) "TRACE: " ALO_ANSI_SEQUENCE(ALO_ANSI_CLEAR),
	ALO_ANSI_COLOR_DARK(ALO_ANSI_COLOR_BLACK) ALO_ANSI_SEQUENCE(ALO_ANSI_BOLD) "PERFORMANCE: " ALO_ANSI_SEQUENCE(ALO_ANSI_CLEAR),
	ALO_ANSI_COLOR_LIGHT(ALO_ANSI_COLOR_GREEN) ALO_ANSI_SEQUENCE(ALO_ANSI_BOLD) "DEBUG: " ALO_ANSI_SEQUENCE(ALO_ANSI_CLEAR),
	ALO_ANSI_COLOR_LIGHT(ALO_ANSI_COLOR_CYAN) ALO_ANSI_SEQUENCE(ALO_ANSI_BOLD) "NOTE: " ALO_ANSI_SEQUENCE(ALO_ANSI_CLEAR),
	ALO_ANSI_COLOR_LIGHT(ALO_ANSI_COLOR_BLUE) ALO_ANSI_SEQUENCE(ALO_ANSI_BOLD) "INFO: " ALO_ANSI_SEQUENCE(ALO_ANSI_CLEAR),
	ALO_ANSI_COLOR_LIGHT(ALO_ANSI_COLOR_YELLOW) ALO_ANSI_SEQUENCE(ALO_ANSI_BOLD) "WARNING: " ALO_ANSI_SEQUENCE(ALO_ANSI_CLEAR),
	ALO_ANSI_COLOR_LIGHT(ALO_ANSI_COLOR_RED) ALO_ANSI_SEQUENCE(ALO_ANSI_BOLD) "ERROR: " ALO_ANSI_SEQUENCE(ALO_ANSI_CLEAR),
	ALO_ANSI_COLOR_LIGHT(ALO_ANSI_COLOR_MAGENTA) ALO_ANSI_SEQUENCE(ALO_ANSI_BOLD) "FATAL: " ALO_ANSI_SEQUENCE(ALO_ANSI_CLEAR)};

void alog(const alo_log_level_t level, const char* const restrict string) {
	ALO_FRAME_BEGIN(alog);

	alo_error_t error = alo_serial_send_string(ALO_INTERNAL_KALOG_SERIAL_PORT, level_name_table_colored[level]);
	ALO_REQUIRE_NO_ERROR_K(error);

	error = alo_serial_send_string(ALO_INTERNAL_KALOG_SERIAL_PORT, string);
	ALO_REQUIRE_NO_ERROR_K(error);

	error = alo_serial_send(ALO_INTERNAL_KALOG_SERIAL_PORT, '\n');
	ALO_REQUIRE_NO_ERROR_K(error);

	if(level >= ERROR) atrace;
}

static const char hex_table[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

void alogf(const alo_log_level_t level, const char* const restrict string, ...) {
	ALO_FRAME_BEGIN(alogf);

	alo_error_t error = alo_serial_send_string(ALO_INTERNAL_KALOG_SERIAL_PORT, level_name_table_colored[level]);
	ALO_REQUIRE_NO_ERROR_K(error);

	va_list list;
	va_start(list, string);

	size_t string_length = 0;
	error = alo_string_length(string, ALO_STRING_NO_BOUND, ALO_STRING_NO_BOUND, &string_length);
	ALO_REQUIRE_NO_ERROR_K(error);

	for(size_t i = 0; i < string_length; ++i) {
		char c = string[i];

		if(c != '%') {
			error = alo_serial_send(ALO_INTERNAL_KALOG_SERIAL_PORT, c);
			ALO_REQUIRE_NO_ERROR_K(error);
			continue;
		}

		c = string[++i];

		if(c == 'l' || c == 'z' || c == 't' || c == 'j') {
			switch(string[++i]) {
				case 'i':
				case 'd': {
					long accum = va_arg(list, long);
					if(accum < 0) {
						error = alo_serial_send(ALO_INTERNAL_KALOG_SERIAL_PORT, '-');
						ALO_REQUIRE_NO_ERROR_K(error);
					}
					char out[20] = {0};
					size_t idx = 0;
					do {
						out[idx++] = '0' + (accum % 10);
						accum /= 10;
					} while(accum);
					for(size_t j = sizeof(out) - 1; j != SIZE_MAX; --j) {
						if(!out[j]) continue;
						error = alo_serial_send(ALO_INTERNAL_KALOG_SERIAL_PORT, out[j]);
						ALO_REQUIRE_NO_ERROR_K(error);
					}
					continue;
				}
				case 'o': {
					size_t accum = va_arg(list, size_t);
					char out[22] = {0};
					size_t idx = 0;
					error = alo_serial_send(ALO_INTERNAL_KALOG_SERIAL_PORT, '0');
					ALO_REQUIRE_NO_ERROR_K(error);
					do {
						out[idx++] = '0' + accum % 8;
						accum >>= 3;
					} while(accum);
					for(size_t j = sizeof(out) - 1; j != SIZE_MAX; --j) {
						if(!out[j]) continue;
						error = alo_serial_send(ALO_INTERNAL_KALOG_SERIAL_PORT, out[j]);
						ALO_REQUIRE_NO_ERROR_K(error);
					}
					continue;
				}
				case 'x': {
					size_t accum = va_arg(list, size_t);
					char out[16] = {0};
					size_t idx = 0;
					error = alo_serial_send_string(ALO_INTERNAL_KALOG_SERIAL_PORT, "0x");
					ALO_REQUIRE_NO_ERROR_K(error);
					do {
						out[idx++] = hex_table[accum % 16];
						accum >>= 4;
					} while(accum);
					for(size_t j = sizeof(out) - 1; j != SIZE_MAX; --j) {
						if(!out[j]) continue;
						error = alo_serial_send(ALO_INTERNAL_KALOG_SERIAL_PORT, out[j]);
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
						error = alo_serial_send(ALO_INTERNAL_KALOG_SERIAL_PORT, out[j]);
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
					error = alo_serial_send(ALO_INTERNAL_KALOG_SERIAL_PORT, '%');
					ALO_REQUIRE_NO_ERROR_K(error);
					continue;
				}
				case 'c': {
					error = alo_serial_send(ALO_INTERNAL_KALOG_SERIAL_PORT, (char) va_arg(list, int));
					ALO_REQUIRE_NO_ERROR_K(error);
					continue;
				}
				case 's': {
					error = alo_serial_send_string(ALO_INTERNAL_KALOG_SERIAL_PORT, va_arg(list, char*));
					ALO_REQUIRE_NO_ERROR_K(error);
					continue;
				}
				case 'i':
				case 'd': {
					int accum = va_arg(list, int);
					if(accum < 0) {
						error = alo_serial_send(ALO_INTERNAL_KALOG_SERIAL_PORT, '-');
						ALO_REQUIRE_NO_ERROR_K(error);
					}
					char out[10] = {0};
					size_t idx = 0;
					do {
						out[idx++] = '0' + (accum % 10);
						accum /= 10;
					} while(accum);
					for(size_t j = sizeof(out) - 1; j != SIZE_MAX; --j) {
						if(!out[j]) continue;
						error = alo_serial_send(ALO_INTERNAL_KALOG_SERIAL_PORT, out[j]);
						ALO_REQUIRE_NO_ERROR_K(error);
					}
					continue;
				}
				case 'o': {
					unsigned int accum = va_arg(list, unsigned int);
					char out[11] = {0};
					size_t idx = 0;
					error = alo_serial_send(ALO_INTERNAL_KALOG_SERIAL_PORT, '0');
					ALO_REQUIRE_NO_ERROR_K(error);
					do {
						out[idx++] = '0' + accum % 8;
						accum >>= 3;
					} while(accum);
					for(size_t j = sizeof(out) - 1; j != SIZE_MAX; --j) {
						if(!out[j]) continue;
						error = alo_serial_send(ALO_INTERNAL_KALOG_SERIAL_PORT, out[j]);
						ALO_REQUIRE_NO_ERROR_K(error);
					}
					continue;
				}
				case 'x': {
					unsigned int accum = va_arg(list, unsigned int);
					char out[8] = {0};
					size_t idx = 0;
					error = alo_serial_send_string(ALO_INTERNAL_KALOG_SERIAL_PORT, "0x");
					ALO_REQUIRE_NO_ERROR_K(error);
					do {
						out[idx++] = hex_table[accum % 16];
						accum >>= 4;
					} while(accum);
					for(size_t j = sizeof(out) - 1; j != SIZE_MAX; --j) {
						if(!out[j]) continue;
						error = alo_serial_send(ALO_INTERNAL_KALOG_SERIAL_PORT, out[j]);
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
						error = alo_serial_send(ALO_INTERNAL_KALOG_SERIAL_PORT, out[j]);
						ALO_REQUIRE_NO_ERROR_K(error);
					}
					continue;
				}
				case 'p': {
					uintptr_t accum = (uintptr_t) va_arg(list, void*);
					char out[16] = {'0'};
					size_t idx = 0;
					error = alo_serial_send_string(ALO_INTERNAL_KALOG_SERIAL_PORT, "0x");
					ALO_REQUIRE_NO_ERROR_K(error);
					do {
						out[idx++] = hex_table[accum % 16];
						accum >>= 4;
					} while(accum);
					for(size_t j = sizeof(out) - 1; j != SIZE_MAX; --j) {
						error = alo_serial_send(ALO_INTERNAL_KALOG_SERIAL_PORT, out[j]);
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

	error = alo_serial_send(ALO_INTERNAL_KALOG_SERIAL_PORT, '\n');
	ALO_REQUIRE_NO_ERROR_K(error);

	va_end(list);

	if(level >= ERROR) atrace;
}
