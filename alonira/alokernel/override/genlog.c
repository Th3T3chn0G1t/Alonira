// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+genstone@pm.me>

#include <genlog.h>

#include <gencommon.h>
#include <genmemory.h>
#include <genstring.h>
#include <genthreads.h>

#include "../include/serial.h"

GEN_PRAGMA(GEN_PRAGMA_DIAGNOSTIC_REGION_BEGIN)
GEN_PRAGMA(GEN_PRAGMA_DIAGNOSTIC_REGION_IGNORE("-Wunused-macros"))
#define GEN_LOG_INTERNAL_ANSI_COLOR_GRAY "30"
#define GEN_LOG_INTERNAL_ANSI_COLOR_RED "31"
#define GEN_LOG_INTERNAL_ANSI_COLOR_GREEN "32"
#define GEN_LOG_INTERNAL_ANSI_COLOR_YELLOW "33"
#define GEN_LOG_INTERNAL_ANSI_COLOR_BLUE "34"
#define GEN_LOG_INTERNAL_ANSI_COLOR_PURPLE "35"
#define GEN_LOG_INTERNAL_ANSI_COLOR_CYAN "36"
#define GEN_LOG_INTERNAL_ANSI_COLOR_WHITE "37"

#define GEN_LOG_INTERNAL_ANSI_COLOR_DARK_GRAY "90"
#define GEN_LOG_INTERNAL_ANSI_COLOR_DARK_RED "91"
#define GEN_LOG_INTERNAL_ANSI_COLOR_DARK_GREEN "92"
#define GEN_LOG_INTERNAL_ANSI_COLOR_DARK_YELLOW "93"
#define GEN_LOG_INTERNAL_ANSI_COLOR_DARK_BLUE "94"
#define GEN_LOG_INTERNAL_ANSI_COLOR_DARK_PURPLE "95"
#define GEN_LOG_INTERNAL_ANSI_COLOR_DARK_CYAN "96"
#define GEN_LOG_INTERNAL_ANSI_COLOR_DARK_WHITE "97"

#define GEN_LOG_INTERNAL_ANSI_CLEAR "0;"
#define GEN_LOG_INTERNAL_ANSI_BOLD "1;"

#define GEN_LOG_INTERNAL_ANSI_SEQUENCE_PREFIX "\033["
#define GEN_LOG_INTERNAL_ANSI_SEQUENCE_SUFFIX "m"

#define GEN_LOG_INTERNAL_ANSI_SEQUENCE_COLOR(color) GEN_LOG_INTERNAL_ANSI_SEQUENCE_PREFIX GEN_LOG_INTERNAL_ANSI_CLEAR color GEN_LOG_INTERNAL_ANSI_SEQUENCE_SUFFIX
#define GEN_LOG_INTERNAL_ANSI_SEQUENCE_COLOR_BOLD(color) GEN_LOG_INTERNAL_ANSI_SEQUENCE_PREFIX GEN_LOG_INTERNAL_ANSI_BOLD color GEN_LOG_INTERNAL_ANSI_SEQUENCE_SUFFIX
#define GEN_LOG_INTERNAL_ANSI_SEQUENCE_CLEAR GEN_LOG_INTERNAL_ANSI_SEQUENCE_PREFIX GEN_LOG_INTERNAL_ANSI_CLEAR GEN_LOG_INTERNAL_ANSI_SEQUENCE_SUFFIX
#define GEN_LOG_INTERNAL_ANSI_SEQUENCE_BOLD GEN_LOG_INTERNAL_ANSI_SEQUENCE_PREFIX GEN_LOG_INTERNAL_ANSI_BOLD GEN_LOG_INTERNAL_ANSI_SEQUENCE_SUFFIX
GEN_PRAGMA(GEN_PRAGMA_DIAGNOSTIC_REGION_END)

#ifndef GEN_LOG_CONTEXT_PAD
/**
 * The width the pad out context strings to.
 */
#define GEN_LOG_CONTEXT_PAD 18
#endif

#ifndef GEN_LOG_SEVERITY_PAD
/**
 * The width the pad out severity strings to.
 */
#define GEN_LOG_SEVERITY_PAD 8
#endif

#ifndef ALO_GEN_LOG_OVERRIDE_LOG_BUFFER_SIZE
/**
 * The length of the log buffer for formatting log output.
 */
#define ALO_GEN_LOG_OVERRIDE_LOG_BUFFER_SIZE 4096
#endif

static GEN_THREAD_LOCAL char formatted[ALO_GEN_LOG_OVERRIDE_LOG_BUFFER_SIZE + 1] = {0};

gen_error_t* gen_log(const gen_log_level_t severity, const char* const restrict context, const char* const restrict string) {
	GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_log, GEN_FILE_NAME);
	if(error) return error;

	if(!context) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`context` was `NULL`");
	if(!string) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`string` was `NULL`");

	size_t context_length = 0;
	error = gen_string_length(context, GEN_STRING_NO_BOUNDS, GEN_LOG_CONTEXT_PAD, &context_length);
	if(error) return error;

	static const char* const severity_names[] = {
		GEN_LOG_INTERNAL_ANSI_SEQUENCE_COLOR_BOLD(GEN_LOG_INTERNAL_ANSI_COLOR_DARK_WHITE) "trace" GEN_LOG_INTERNAL_ANSI_SEQUENCE_CLEAR,
		GEN_LOG_INTERNAL_ANSI_SEQUENCE_COLOR_BOLD(GEN_LOG_INTERNAL_ANSI_COLOR_GREEN) "debug" GEN_LOG_INTERNAL_ANSI_SEQUENCE_CLEAR,
		GEN_LOG_INTERNAL_ANSI_SEQUENCE_COLOR_BOLD(GEN_LOG_INTERNAL_ANSI_COLOR_CYAN) "info" GEN_LOG_INTERNAL_ANSI_SEQUENCE_CLEAR,
		GEN_LOG_INTERNAL_ANSI_SEQUENCE_COLOR_BOLD(GEN_LOG_INTERNAL_ANSI_COLOR_YELLOW) "warning" GEN_LOG_INTERNAL_ANSI_SEQUENCE_CLEAR,
		GEN_LOG_INTERNAL_ANSI_SEQUENCE_COLOR_BOLD(GEN_LOG_INTERNAL_ANSI_COLOR_RED) "error" GEN_LOG_INTERNAL_ANSI_SEQUENCE_CLEAR,
		GEN_LOG_INTERNAL_ANSI_SEQUENCE_COLOR_BOLD(GEN_LOG_INTERNAL_ANSI_COLOR_PURPLE) "fatal" GEN_LOG_INTERNAL_ANSI_SEQUENCE_CLEAR};

	static const size_t severity_lengths[] = {
		sizeof(GEN_LOG_INTERNAL_ANSI_SEQUENCE_COLOR_BOLD(GEN_LOG_INTERNAL_ANSI_COLOR_DARK_WHITE) "trace" GEN_LOG_INTERNAL_ANSI_SEQUENCE_CLEAR),
		sizeof(GEN_LOG_INTERNAL_ANSI_SEQUENCE_COLOR_BOLD(GEN_LOG_INTERNAL_ANSI_COLOR_GREEN) "debug" GEN_LOG_INTERNAL_ANSI_SEQUENCE_CLEAR),
		sizeof(GEN_LOG_INTERNAL_ANSI_SEQUENCE_COLOR_BOLD(GEN_LOG_INTERNAL_ANSI_COLOR_CYAN) "info" GEN_LOG_INTERNAL_ANSI_SEQUENCE_CLEAR),
		sizeof(GEN_LOG_INTERNAL_ANSI_SEQUENCE_COLOR_BOLD(GEN_LOG_INTERNAL_ANSI_COLOR_YELLOW) "warning" GEN_LOG_INTERNAL_ANSI_SEQUENCE_CLEAR),
		sizeof(GEN_LOG_INTERNAL_ANSI_SEQUENCE_COLOR_BOLD(GEN_LOG_INTERNAL_ANSI_COLOR_RED) "error" GEN_LOG_INTERNAL_ANSI_SEQUENCE_CLEAR),
		sizeof(GEN_LOG_INTERNAL_ANSI_SEQUENCE_COLOR_BOLD(GEN_LOG_INTERNAL_ANSI_COLOR_PURPLE) "fatal" GEN_LOG_INTERNAL_ANSI_SEQUENCE_CLEAR)};

	static const size_t severity_name_lengths[] = {
		sizeof("trace") - 1,
		sizeof("debug") - 1,
		sizeof("info") - 1,
		sizeof("warning") - 1,
		sizeof("error") - 1,
		sizeof("fatal") - 1};

    error = gen_memory_set(formatted, ALO_GEN_LOG_OVERRIDE_LOG_BUFFER_SIZE + 1, 0);
	if(error) return error;

	// `clang-format` has a bit of an aneurism here
	// clang-format off
	static const char format[] =
		GEN_LOG_INTERNAL_ANSI_SEQUENCE_COLOR_BOLD(GEN_LOG_INTERNAL_ANSI_COLOR_GRAY) "["
        GEN_LOG_INTERNAL_ANSI_SEQUENCE_COLOR_BOLD(GEN_LOG_INTERNAL_ANSI_COLOR_WHITE) "%tz%cz"
		GEN_LOG_INTERNAL_ANSI_SEQUENCE_COLOR_BOLD(GEN_LOG_INTERNAL_ANSI_COLOR_GRAY) "] "

		GEN_LOG_INTERNAL_ANSI_SEQUENCE_COLOR_BOLD(GEN_LOG_INTERNAL_ANSI_COLOR_GRAY) "["
        GEN_LOG_INTERNAL_ANSI_SEQUENCE_COLOR_BOLD(GEN_LOG_INTERNAL_ANSI_COLOR_WHITE) "%tz%cz"
		GEN_LOG_INTERNAL_ANSI_SEQUENCE_COLOR_BOLD(GEN_LOG_INTERNAL_ANSI_COLOR_GRAY) "] "

        GEN_LOG_INTERNAL_ANSI_SEQUENCE_CLEAR "%t\n";
	// clang-format on

	error = gen_string_format(ALO_GEN_LOG_OVERRIDE_LOG_BUFFER_SIZE, formatted, NULL, format, sizeof(format) - 1, context, context_length, ' ', GEN_LOG_CONTEXT_PAD - context_length, severity_names[severity], severity_lengths[severity], ' ', GEN_LOG_SEVERITY_PAD - severity_name_lengths[severity], string);
	if(error) return error;

    error = alo_serial_send_string(ALO_SERIAL_COM1, formatted);
	if(error) return error;

	return NULL;
}

static GEN_THREAD_LOCAL char logf_formatted[ALO_GEN_LOG_OVERRIDE_LOG_BUFFER_SIZE + 1] = {0};

gen_error_t* gen_log_formatted(const gen_log_level_t severity, const char* const restrict context, const char* const restrict format, ...) {
	GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_log_formatted, GEN_FILE_NAME);
	if(error) return error;

	if(!format) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`string` was `NULL`");

	va_list args;
	va_list args_copy;
	va_start(args, format);
	va_copy(args_copy, args);

	size_t format_length = 0;
	error = gen_string_length(format, GEN_STRING_NO_BOUNDS, GEN_STRING_NO_BOUNDS, &format_length);
	if(error) return error;

    error = gen_memory_set(logf_formatted, ALO_GEN_LOG_OVERRIDE_LOG_BUFFER_SIZE + 1, 0);
	if(error) return error;

	error = gen_string_formatv(ALO_GEN_LOG_OVERRIDE_LOG_BUFFER_SIZE, logf_formatted, NULL, format, format_length, args_copy);
	if(error) return error;

	return gen_log(severity, context, logf_formatted);
}
