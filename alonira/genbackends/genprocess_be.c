// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+genstone@pm.me>

#include <gencommon.h>
#include <genfilesystem.h>
#include <genprocess.h>

#include "include/genprocess_be.h"

gen_error_t* gen_backends_alonira_process_create_with_redirect(const char* const restrict executable_path, const gen_size_t executable_path_bounds, const gen_size_t executable_path_length, const char* const* const restrict arguments, const gen_size_t* const restrict argument_lengths, const gen_size_t arguments_length, const char* const restrict * const restrict environment, const gen_size_t* const restrict environment_lengths, const gen_size_t environment_length, gen_filesystem_handle_t* const restrict filesystem_handle, gen_process_handle_t* const restrict out_process) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_process_create_with_redirect, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_process_wait(const gen_process_handle_t* const restrict process, int* const restrict out_exitcode) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_process_wait, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_process_kill(const gen_process_handle_t* const restrict process) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_process_kill, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_process_check(const gen_process_handle_t* const restrict process, gen_bool_t* const restrict out_alive) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_process_check, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_process_get_environment(char* restrict * const restrict out_environment, gen_size_t* const restrict out_lengths, gen_size_t* const restrict out_length) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_process_get_environment, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}
