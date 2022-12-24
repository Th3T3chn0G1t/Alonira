// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+genstone@pm.me>

#ifndef GEN_DYNAMIC_LIBRARY_BE_H
#define GEN_DYNAMIC_LIBRARY_BE_H

typedef struct gen_backends_dynamic_library_handle_t {} gen_backends_dynamic_library_handle_t;

extern gen_error_t* gen_backends_alonira_dynamic_library_handle_open(const char* const restrict library_name, const gen_size_t library_name_bounds, const gen_size_t library_name_length, gen_dynamic_library_handle_t* const restrict out_dynamic_library);
extern gen_error_t* gen_backends_alonira_dynamic_library_handle_close(gen_dynamic_library_handle_t* const restrict dynamic_library);
extern gen_error_t* gen_backends_alonira_dynamic_library_handle_get_symbol(const gen_dynamic_library_handle_t* const restrict dynamic_library, const char* const restrict symbol_name, const gen_size_t symbol_name_bounds, const gen_size_t symbol_name_length, void* restrict* const restrict out_address);

#endif
