// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+genstone@pm.me>

#include <gencommon.h>

#include "include/genmemory_be.h"

gen_error_t* gen_backends_alonira_memory_allocate_zeroed(void* restrict* const restrict out_address, const gen_size_t count, const gen_size_t size) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_memory_allocate_zeroed, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_memory_allocate_zeroed_aligned(void* restrict* const restrict out_address, const gen_size_t count, const gen_size_t size, const gen_size_t alignment) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_memory_allocate_zeroed_aligned, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_memory_reallocate_zeroed(void* restrict* const restrict address, const gen_size_t old_count, const gen_size_t count, const gen_size_t size) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_memory_reallocate_zeroed, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_memory_free(void* restrict* const restrict address) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_memory_free, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_memory_set(void* const restrict address, const gen_size_t bounds, const gen_size_t count, const unsigned char value) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_memory_set, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_memory_copy(void* const restrict to, const gen_size_t to_bounds, const void* const restrict from, const gen_size_t from_bounds, const gen_size_t count) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_memory_copy, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_memory_compare(const void* const restrict a, const gen_size_t a_bounds, const void* const restrict b, const gen_size_t b_bounds, const gen_size_t count, gen_bool_t* const restrict out_equal) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_memory_compare, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}
