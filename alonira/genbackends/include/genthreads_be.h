// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+genstone@pm.me>

#ifndef GEN_THREADS_BE_H
#define GEN_THREADS_BE_H

typedef struct gen_backends_threads_mutex_t {} gen_backends_threads_mutex_t;

typedef struct gen_backends_threads_handle_t {} gen_backends_threads_handle_t;

extern gen_error_t* gen_backends_alonira_threads_mutex_create(gen_threads_mutex_t* const restrict out_mutex);
extern gen_error_t* gen_backends_alonira_threads_mutex_destroy(gen_threads_mutex_t* const restrict mutex);
extern gen_error_t* gen_backends_alonira_threads_mutex_lock(gen_threads_mutex_t* const restrict mutex);
extern gen_error_t* gen_backends_alonira_threads_mutex_unlock(gen_threads_mutex_t* const restrict mutex);
extern gen_error_t* gen_backends_alonira_threads_install_message_handlers(void);
extern gen_error_t* gen_backends_alonira_threads_handle_set_message_mode(gen_threads_handle_t* const restrict handle, const gen_threads_message_type_t message, const gen_bool_t allow);
extern gen_error_t* gen_backends_alonira_threads_handle_set_message_handler(gen_threads_handle_t* const restrict handle, const gen_threads_message_handler_t handler);

#endif
