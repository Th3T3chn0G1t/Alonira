// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+genstone@pm.me>

#ifndef GEN_FILESYSTEM_BE_H
#define GEN_FILESYSTEM_BE_H

typedef struct gen_backends_filesystem_handle_t {} gen_backends_filesystem_handle_t;

extern gen_error_t* gen_backends_alonira_filesystem_path_canonicalize(const char* const restrict path, const gen_size_t path_bounds, const gen_size_t path_length, char* const restrict out_canonical, gen_size_t* const restrict out_length);
extern gen_error_t* gen_backends_alonira_filesystem_path_exists(const char* const restrict path, const gen_size_t path_bounds, const gen_size_t path_length, gen_bool_t* const restrict out_exists);
extern gen_error_t* gen_backends_alonira_filesystem_path_validate(const char* const restrict path, const gen_size_t path_bounds, const gen_size_t path_length, gen_bool_t* const restrict out_valid);
extern gen_error_t* gen_backends_alonira_filesystem_path_create_file(const char* const restrict path, const gen_size_t path_bounds, const gen_size_t path_length);
extern gen_error_t* gen_backends_alonira_filesystem_path_create_directory(const char* const restrict path, const gen_size_t path_bounds, const gen_size_t path_length);
extern gen_error_t* gen_backends_alonira_filesystem_path_delete(const char* const restrict path, const gen_size_t path_bounds, const gen_size_t path_length);
extern gen_error_t* gen_backends_alonira_filesystem_handle_open_anonymous(gen_filesystem_handle_t* const restrict out_handle);
extern gen_error_t* gen_backends_alonira_filesystem_handle_open(const char* const restrict path, const gen_size_t path_bounds, const gen_size_t path_length, gen_filesystem_handle_t* const restrict out_handle);
extern gen_error_t* gen_backends_alonira_filesystem_handle_close(gen_filesystem_handle_t* const restrict handle);
extern gen_error_t* gen_backends_alonira_filesystem_handle_file_size(gen_filesystem_handle_t* const restrict handle, gen_size_t* const restrict out_size);
extern gen_error_t* gen_backends_alonira_filesystem_handle_file_read(gen_filesystem_handle_t* const restrict handle, const gen_size_t offset, const gen_size_t length, unsigned char* restrict out_buffer);
extern gen_error_t* gen_backends_alonira_filesystem_handle_file_write(gen_filesystem_handle_t* const restrict handle, const gen_size_t offset, const unsigned char* const restrict buffer, const gen_size_t length);
extern gen_error_t* gen_backends_alonira_filesystem_handle_directory_list(gen_filesystem_handle_t* const restrict handle, char* restrict * const restrict out_list, gen_size_t* const restrict out_lengths, gen_size_t* const restrict out_length);
extern gen_error_t* gen_backends_alonira_filesystem_handle_lock(gen_filesystem_handle_t* const restrict handle);
extern gen_error_t* gen_backends_alonira_filesystem_handle_unlock(gen_filesystem_handle_t* const restrict handle);
extern gen_error_t* gen_backends_alonira_filesystem_watcher_create(gen_filesystem_watcher_t* const restrict out_watcher);
extern gen_error_t* gen_backends_alonira_filesystem_watcher_destroy(gen_filesystem_watcher_t* const restrict watcher);
extern gen_error_t* gen_backends_alonira_filesystem_watcher_add(gen_filesystem_watcher_t* const restrict watcher, gen_filesystem_handle_t* const restrict handle, gen_filesystem_watcher_id_t* const restrict out_id);
extern gen_error_t* gen_backends_alonira_filesystem_watcher_remove(gen_filesystem_watcher_t* const restrict watcher, const gen_filesystem_watcher_id_t id);
extern gen_error_t* gen_backends_alonira_filesystem_watcher_poll(gen_filesystem_watcher_t* const restrict watcher, gen_filesystem_watcher_event_t* const restrict out_event, gen_filesystem_watcher_id_t* const restrict out_id);

#endif
