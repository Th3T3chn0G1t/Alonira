// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+genstone@pm.me>

#ifndef GEN_PROCESS_BE_H
#define GEN_PROCESS_BE_H

typedef struct gen_backends_process_handle_t {} gen_backends_process_handle_t;

extern gen_error_t* gen_backends_alonira_process_create_with_redirect(const char* const restrict executable_path, const gen_size_t executable_path_bounds, const gen_size_t executable_path_length, const char* const* const restrict arguments, const gen_size_t* const restrict argument_lengths, const gen_size_t arguments_length, const char* const restrict * const restrict environment, const gen_size_t* const restrict environment_lengths, const gen_size_t environment_length, gen_filesystem_handle_t* const restrict filesystem_handle, gen_process_handle_t* const restrict out_process);
extern gen_error_t* gen_backends_alonira_process_wait(const gen_process_handle_t* const restrict process, int* const restrict out_exitcode);
extern gen_error_t* gen_backends_alonira_process_kill(const gen_process_handle_t* const restrict process);
extern gen_error_t* gen_backends_alonira_process_check(const gen_process_handle_t* const restrict process, gen_bool_t* const restrict out_alive);
extern gen_error_t* gen_backends_alonira_process_get_environment(char* restrict * const restrict out_environment, gen_size_t* const restrict out_lengths, gen_size_t* const restrict out_length);

#endif
