// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+genstone@pm.me>

#include <gencommon.h>
#include <genstring.h>

#include "include/genstring_be.h"

gen_error_t* gen_backends_alonira_string_compare(const char* const restrict a, const gen_size_t a_bounds, const gen_size_t a_length, const char* const restrict b, const gen_size_t b_bounds, const gen_size_t b_length, const gen_size_t count, gen_bool_t* const restrict out_equal) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_string_compare, GEN_FILE_NAME);
    if(error) return error;

    for(gen_size_t i = 0; i < count; ++i) {
        if(a[i] != b[i]) {
            *out_equal = gen_false;
            return GEN_NULL;
        }
    }

    *out_equal = gen_true;
    return GEN_NULL;
}

// TODO: genmemory calls these to/from and here they're destination/source - fix.
gen_error_t* gen_backends_alonira_string_copy(char* const restrict destination, const gen_size_t destination_bounds, const char* const restrict source, const gen_size_t source_bounds, const gen_size_t source_length, const gen_size_t count) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_string_copy, GEN_FILE_NAME);
    if(error) return error;

    for(gen_size_t i = 0; i < count; ++i) {
        destination[i] = source[i];
    }

    return GEN_NULL;
}

gen_error_t* gen_backends_alonira_string_append(char* const restrict destination, const gen_size_t destination_bounds, const gen_size_t destination_length, const char* const restrict source, const gen_size_t source_bounds, const gen_size_t source_length, const gen_size_t count) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_string_append, GEN_FILE_NAME);
    if(error) return error;

    error = gen_string_copy(destination + destination_length, destination_bounds - destination_length, source, source_bounds, source_length, count);
    if(error) return error;

    return GEN_NULL;
}

gen_error_t* gen_backends_alonira_string_length(const char* const restrict string, const gen_size_t string_bounds, const gen_size_t limit, gen_size_t* const restrict out_length) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_string_length, GEN_FILE_NAME);
    if(error) return error;

    gen_size_t i = 0;
    for(; i < limit && string[i]; ++i) {
        // TODO: This feels like it might allow invalid accesses on the buffer boundary where `char[N] x; x[N] == 0`
        if(i == string_bounds) return gen_error_attach_backtrace(GEN_ERROR_TOO_LONG, GEN_LINE_NUMBER, "`string` length exceeded `string_bounds`");
    }

    *out_length = i;

    return GEN_NULL;
}
