// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+genstone@pm.me>

#ifndef GEN_MEMORY_BE_H
#define GEN_MEMORY_BE_H

extern gen_error_t* gen_backends_alonira_memory_allocate_zeroed(void* restrict* const restrict out_address, const gen_size_t count, const gen_size_t size);
extern gen_error_t* gen_backends_alonira_memory_allocate_zeroed_aligned(void* restrict* const restrict out_address, const gen_size_t count, const gen_size_t size, const gen_size_t alignment);
extern gen_error_t* gen_backends_alonira_memory_reallocate_zeroed(void* restrict* const restrict address, const gen_size_t old_count, const gen_size_t count, const gen_size_t size);
extern gen_error_t* gen_backends_alonira_memory_free(void* restrict* const restrict address);
extern gen_error_t* gen_backends_alonira_memory_set(void* const restrict address, const gen_size_t bounds, const gen_size_t count, const unsigned char value);
extern gen_error_t* gen_backends_alonira_memory_copy(void* const restrict to, const gen_size_t to_bounds, const void* const restrict from, const gen_size_t from_bounds, const gen_size_t count);
extern gen_error_t* gen_backends_alonira_memory_compare(const void* const restrict a, const gen_size_t a_bounds, const void* const restrict b, const gen_size_t b_bounds, const gen_size_t count, gen_bool_t* const restrict out_equal);

#endif
