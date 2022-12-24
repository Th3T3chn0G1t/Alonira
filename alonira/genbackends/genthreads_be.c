// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+genstone@pm.me>

#include <gencommon.h>
#include <genthreads.h>

#include "include/genthreads_be.h"

gen_error_t* gen_backends_alonira_threads_mutex_create(gen_threads_mutex_t* const restrict out_mutex) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_threads_mutex_create, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_threads_mutex_destroy(gen_threads_mutex_t* const restrict mutex) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_threads_mutex_destroy, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_threads_mutex_lock(gen_threads_mutex_t* const restrict mutex) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_threads_mutex_lock, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_threads_mutex_unlock(gen_threads_mutex_t* const restrict mutex) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_threads_mutex_unlock, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_threads_install_message_handlers(void) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_threads_install_message_handlers, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_threads_handle_set_message_mode(gen_threads_handle_t* const restrict handle, const gen_threads_message_type_t message, const gen_bool_t allow) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_threads_handle_set_message_mode, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_threads_handle_set_message_handler(gen_threads_handle_t* const restrict handle, const gen_threads_message_handler_t handler) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_threads_handle_set_message_handler, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

