// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include <gencommon.h>
#include <genmemory.h>

gen_error_t* gen_memory_allocate_zeroed(void* restrict* const restrict out_address, const size_t count, const size_t size) {
	GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_memory_allocate_zeroed, GEN_FILE_NAME);
	if(error) return error;

    (void) out_address;
    (void) count;
    (void) size;

    return gen_error_attach_backtrace_formatted(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "`%t` not implemented", GEN_FUNCTION_NAME);
}

gen_error_t* gen_memory_allocate_zeroed_aligned(void* restrict* const restrict out_address, const size_t count, const size_t size, const size_t alignment) {
	GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_memory_allocate_zeroed_aligned, GEN_FILE_NAME);
	if(error) return error;

    (void) out_address;
    (void) count;
    (void) size;
    (void) alignment;

    return gen_error_attach_backtrace_formatted(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "`%t` not implemented", GEN_FUNCTION_NAME);
}

gen_error_t* gen_memory_reallocate_zeroed(void* restrict* const restrict address, const size_t old_count, const size_t count, const size_t size) {
	GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_memory_reallocate_zeroed, GEN_FILE_NAME);
	if(error) return error;

    (void) address;
    (void) old_count;
    (void) count;
    (void) size;

    return gen_error_attach_backtrace_formatted(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "`%t` not implemented", GEN_FUNCTION_NAME);
}

gen_error_t* gen_memory_free(void* restrict* const restrict address) {
	GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_memory_free, GEN_FILE_NAME);
	if(error) return error;

    (void) address;

    return gen_error_attach_backtrace_formatted(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "`%t` not implemented", GEN_FUNCTION_NAME);
}

gen_error_t* gen_memory_set(void* const restrict address, const size_t length, const unsigned char value) {
	GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_memory_set, GEN_FILE_NAME);
	if(error) return error;

	if(!address) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`address` was `NULL`");

	__builtin_memset(address, value, length);

	return NULL;
}

gen_error_t* gen_memory_copy(void* const restrict to, const size_t to_size, const void* const restrict from, const size_t from_size, const size_t limit) {
	GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_memory_copy, GEN_FILE_NAME);
	if(error) return error;

	if(!from) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`from` was `NULL`");
	if(!to) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`to` was `NULL`");
	if(limit > from_size) return gen_error_attach_backtrace(GEN_ERROR_OUT_OF_BOUNDS, GEN_LINE_NUMBER, "`limit` exceeded `from_size`");
	if(limit > to_size) return gen_error_attach_backtrace(GEN_ERROR_OUT_OF_BOUNDS, GEN_LINE_NUMBER, "`limit` exceeded `to_size`");

	__builtin_memcpy(to, from, limit);

	return NULL;
}
