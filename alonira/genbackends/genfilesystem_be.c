// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+genstone@pm.me>

#include <gencommon.h>
#include <genfilesystem.h>

#include "include/genfilesystem_be.h"

gen_error_t* gen_backends_alonira_filesystem_path_canonicalize(const char* const restrict path, const gen_size_t path_bounds, const gen_size_t path_length, char* const restrict out_canonical, gen_size_t* const restrict out_length) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_filesystem_path_canonicalize, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_filesystem_path_exists(const char* const restrict path, const gen_size_t path_bounds, const gen_size_t path_length, gen_bool_t* const restrict out_exists) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_filesystem_path_exists, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_filesystem_path_validate(const char* const restrict path, const gen_size_t path_bounds, const gen_size_t path_length, gen_bool_t* const restrict out_valid) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_filesystem_path_validate, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_filesystem_path_create_file(const char* const restrict path, const gen_size_t path_bounds, const gen_size_t path_length) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_filesystem_path_create_file, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_filesystem_path_create_directory(const char* const restrict path, const gen_size_t path_bounds, const gen_size_t path_length) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_filesystem_path_create_directory, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_filesystem_path_delete(const char* const restrict path, const gen_size_t path_bounds, const gen_size_t path_length) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_filesystem_path_delete, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_filesystem_handle_open_anonymous(gen_filesystem_handle_t* const restrict out_handle) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_filesystem_handle_open_anonymous, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_filesystem_handle_open(const char* const restrict path, const gen_size_t path_bounds, const gen_size_t path_length, gen_filesystem_handle_t* const restrict out_handle) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_filesystem_handle_open, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_filesystem_handle_close(gen_filesystem_handle_t* const restrict handle) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_filesystem_handle_close, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_filesystem_handle_file_size(gen_filesystem_handle_t* const restrict handle, gen_size_t* const restrict out_size) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_filesystem_handle_file_size, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_filesystem_handle_file_read(gen_filesystem_handle_t* const restrict handle, const gen_size_t offset, const gen_size_t length, unsigned char* restrict out_buffer) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_filesystem_handle_file_read, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_filesystem_handle_file_write(gen_filesystem_handle_t* const restrict handle, const gen_size_t offset, const unsigned char* const restrict buffer, const gen_size_t length) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_filesystem_handle_file_write, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_filesystem_handle_directory_list(gen_filesystem_handle_t* const restrict handle, char* restrict * const restrict out_list, gen_size_t* const restrict out_lengths, gen_size_t* const restrict out_length) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_filesystem_handle_directory_list, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_filesystem_handle_lock(gen_filesystem_handle_t* const restrict handle) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_filesystem_handle_lock, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_filesystem_handle_unlock(gen_filesystem_handle_t* const restrict handle) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_filesystem_handle_unlock, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_filesystem_watcher_create(gen_filesystem_watcher_t* const restrict out_watcher) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_filesystem_watcher_create, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_filesystem_watcher_destroy(gen_filesystem_watcher_t* const restrict watcher) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_filesystem_watcher_destroy, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_filesystem_watcher_add(gen_filesystem_watcher_t* const restrict watcher, gen_filesystem_handle_t* const restrict handle, gen_filesystem_watcher_id_t* const restrict out_id) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_filesystem_watcher_add, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_filesystem_watcher_remove(gen_filesystem_watcher_t* const restrict watcher, const gen_filesystem_watcher_id_t id) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_filesystem_watcher_remove, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}

gen_error_t* gen_backends_alonira_filesystem_watcher_poll(gen_filesystem_watcher_t* const restrict watcher, gen_filesystem_watcher_event_t* const restrict out_event, gen_filesystem_watcher_id_t* const restrict out_id) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_backends_alonira_filesystem_watcher_poll, GEN_FILE_NAME);
    if(error) return error;

    return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "Not implemented");
}
