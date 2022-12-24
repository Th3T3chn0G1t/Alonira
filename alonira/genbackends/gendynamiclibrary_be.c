// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+genstone@pm.me>

#include <gencommon.h>
#include <gendynamiclibrary.h>

#include "include/gendynamiclibrary_be.h"

gen_error_t* gen_backends_alonira_dynamic_library_handle_open(const char* const restrict library_name, const gen_size_t library_name_bounds, const gen_size_t library_name_length, gen_dynamic_library_handle_t* const restrict out_dynamic_library) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_dynamic_library_handle_open, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_dynamic_library_handle_close(gen_dynamic_library_handle_t* const restrict dynamic_library) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_dynamic_library_handle_close, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_dynamic_library_handle_get_symbol(const gen_dynamic_library_handle_t* const restrict dynamic_library, const char* const restrict symbol_name, const gen_size_t symbol_name_bounds, const gen_size_t symbol_name_length, void* restrict* const restrict out_address) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_dynamic_library_handle_get_symbol, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}
