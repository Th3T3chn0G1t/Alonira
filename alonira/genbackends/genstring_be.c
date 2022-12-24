// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+genstone@pm.me>

#include <gencommon.h>

#include "include/genstring_be.h"

gen_error_t* gen_backends_alonira_string_compare(const char* const restrict a, const gen_size_t a_bounds, const gen_size_t a_length, const char* const restrict b, const gen_size_t b_bounds, const gen_size_t b_length, const gen_size_t count, gen_bool_t* const restrict out_equal) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_string_compare, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_string_copy(char* const restrict destination, const gen_size_t destination_bounds, const char* const restrict source, const gen_size_t source_bounds, const gen_size_t source_length, const gen_size_t count) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_string_copy, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_string_append(char* const restrict destination, const gen_size_t destination_bounds, const gen_size_t destination_length, const char* const restrict source, const gen_size_t source_bounds, const gen_size_t source_length, const gen_size_t count) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_string_append, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_string_length(const char* const restrict string, const gen_size_t string_bounds, const gen_size_t limit, gen_size_t* const restrict out_length) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_string_length, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_string_duplicate(const char* const restrict string, const gen_size_t string_bounds, const gen_size_t string_length, const gen_size_t count, char* restrict* const restrict out_duplicated, gen_size_t* const restrict out_length) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_string_duplicate, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_string_character_first(const char* const restrict string, const gen_size_t string_bounds, const gen_size_t string_length, const char character, const gen_size_t count, gen_size_t* const restrict out_found) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_string_character_first, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_string_character_last(const char* const restrict string, const gen_size_t string_bounds, const gen_size_t string_length, const char character, const gen_size_t count, gen_size_t* const restrict out_found) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_string_character_last, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_string_number(const char* const restrict string, const gen_size_t string_bounds, const gen_size_t string_length, const gen_size_t count, gen_size_t* const restrict out_number) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_string_number, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_string_format(const gen_size_t limit, char* const restrict out_buffer, gen_size_t* out_length, const char* const restrict format, const gen_size_t format_bounds, const gen_size_t format_length, ...) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_string_format, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_string_formatv(const gen_size_t limit, char* const restrict out_buffer, gen_size_t* const restrict out_length, const char* const restrict format, const gen_size_t format_bounds, const gen_size_t format_length, gen_variadic_list_t list) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_string_formatv, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_string_contains(const char* const restrict string, const gen_size_t string_bounds, const gen_size_t string_length, const char* const restrict target, const gen_size_t target_bounds, const gen_size_t target_length, const gen_size_t count, gen_size_t* const restrict out_offset) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_string_contains, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

