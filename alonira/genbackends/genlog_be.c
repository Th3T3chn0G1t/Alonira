// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+genstone@pm.me>

#include <gencommon.h>
#include <genlog.h>
#include <genstring.h>
#include <genmemory.h>
#include <aloserial.h>

#include "include/genlog_be.h"

// TODO: Move ANSI codes to genbackends/unix/genansi.h or something to de-dup this.
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

GEN_THREAD_LOCAL static char gen_backends_alonira_internal_log_buffer[GEN_LOG_STATIC_FORMAT_BUFFER_SIZE + 1];

gen_error_t* gen_backends_alonira_log(const gen_log_level_t severity, const char* const restrict context, const char* const restrict string) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_log, GEN_FILE_NAME);
    if(error) return error;

    gen_size_t context_length = 0;
    error = gen_string_length(context, GEN_STRING_NO_BOUNDS, GEN_LOG_CONTEXT_PAD, &context_length);
    if(error) return error;

    error = gen_memory_set((void*) gen_backends_alonira_internal_log_buffer, sizeof(gen_backends_alonira_internal_log_buffer), sizeof(gen_backends_alonira_internal_log_buffer), 0);
    if(error) return error;

    static const char* const severity_names[] = {
            GEN_LOG_INTERNAL_ANSI_SEQUENCE_COLOR_BOLD(GEN_LOG_INTERNAL_ANSI_COLOR_DARK_WHITE) "trace" GEN_LOG_INTERNAL_ANSI_SEQUENCE_CLEAR,
            GEN_LOG_INTERNAL_ANSI_SEQUENCE_COLOR_BOLD(GEN_LOG_INTERNAL_ANSI_COLOR_GREEN) "debug" GEN_LOG_INTERNAL_ANSI_SEQUENCE_CLEAR,
            GEN_LOG_INTERNAL_ANSI_SEQUENCE_COLOR_BOLD(GEN_LOG_INTERNAL_ANSI_COLOR_CYAN) "info" GEN_LOG_INTERNAL_ANSI_SEQUENCE_CLEAR,
            GEN_LOG_INTERNAL_ANSI_SEQUENCE_COLOR_BOLD(GEN_LOG_INTERNAL_ANSI_COLOR_YELLOW) "warning" GEN_LOG_INTERNAL_ANSI_SEQUENCE_CLEAR,
            GEN_LOG_INTERNAL_ANSI_SEQUENCE_COLOR_BOLD(GEN_LOG_INTERNAL_ANSI_COLOR_RED) "error" GEN_LOG_INTERNAL_ANSI_SEQUENCE_CLEAR,
            GEN_LOG_INTERNAL_ANSI_SEQUENCE_COLOR_BOLD(GEN_LOG_INTERNAL_ANSI_COLOR_PURPLE) "fatal" GEN_LOG_INTERNAL_ANSI_SEQUENCE_CLEAR};

    static const gen_size_t severity_bounds[] = {
            sizeof(GEN_LOG_INTERNAL_ANSI_SEQUENCE_COLOR_BOLD(GEN_LOG_INTERNAL_ANSI_COLOR_DARK_WHITE) "trace" GEN_LOG_INTERNAL_ANSI_SEQUENCE_CLEAR),
            sizeof(GEN_LOG_INTERNAL_ANSI_SEQUENCE_COLOR_BOLD(GEN_LOG_INTERNAL_ANSI_COLOR_GREEN) "debug" GEN_LOG_INTERNAL_ANSI_SEQUENCE_CLEAR),
            sizeof(GEN_LOG_INTERNAL_ANSI_SEQUENCE_COLOR_BOLD(GEN_LOG_INTERNAL_ANSI_COLOR_CYAN) "info" GEN_LOG_INTERNAL_ANSI_SEQUENCE_CLEAR),
            sizeof(GEN_LOG_INTERNAL_ANSI_SEQUENCE_COLOR_BOLD(GEN_LOG_INTERNAL_ANSI_COLOR_YELLOW) "warning" GEN_LOG_INTERNAL_ANSI_SEQUENCE_CLEAR),
            sizeof(GEN_LOG_INTERNAL_ANSI_SEQUENCE_COLOR_BOLD(GEN_LOG_INTERNAL_ANSI_COLOR_RED) "error" GEN_LOG_INTERNAL_ANSI_SEQUENCE_CLEAR),
            sizeof(GEN_LOG_INTERNAL_ANSI_SEQUENCE_COLOR_BOLD(GEN_LOG_INTERNAL_ANSI_COLOR_PURPLE) "fatal" GEN_LOG_INTERNAL_ANSI_SEQUENCE_CLEAR)};

    static const gen_size_t severity_name_lengths[] = {
            sizeof("trace") - 1,
            sizeof("debug") - 1,
            sizeof("info") - 1,
            sizeof("warning") - 1,
            sizeof("error") - 1,
            sizeof("fatal") - 1};

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

    error = gen_string_format(GEN_LOG_STATIC_FORMAT_BUFFER_SIZE, gen_backends_alonira_internal_log_buffer, GEN_NULL, format, sizeof(format), sizeof(format) - 1, context, context_length + 1, ' ', GEN_LOG_CONTEXT_PAD - context_length, severity_names[severity], severity_bounds[severity], ' ', GEN_LOG_SEVERITY_PAD - severity_name_lengths[severity], string);
    if(error) return error;

    error = alo_serial_send_string(ALO_SERIAL_COM1, gen_backends_alonira_internal_log_buffer);
    if(error) return error;

    return GEN_NULL;
}
