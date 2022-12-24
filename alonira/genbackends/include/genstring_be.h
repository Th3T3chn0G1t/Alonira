// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+genstone@pm.me>

#ifndef GEN_STRING_BE_H
#define GEN_STRING_BE_H

extern gen_error_t* gen_backends_alonira_string_compare(const char* const restrict a, const gen_size_t a_bounds, const gen_size_t a_length, const char* const restrict b, const gen_size_t b_bounds, const gen_size_t b_length, const gen_size_t count, gen_bool_t* const restrict out_equal);
extern gen_error_t* gen_backends_alonira_string_copy(char* const restrict destination, const gen_size_t destination_bounds, const char* const restrict source, const gen_size_t source_bounds, const gen_size_t source_length, const gen_size_t count);
extern gen_error_t* gen_backends_alonira_string_append(char* const restrict destination, const gen_size_t destination_bounds, const gen_size_t destination_length, const char* const restrict source, const gen_size_t source_bounds, const gen_size_t source_length, const gen_size_t count);
extern gen_error_t* gen_backends_alonira_string_length(const char* const restrict string, const gen_size_t string_bounds, const gen_size_t limit, gen_size_t* const restrict out_length);
extern gen_error_t* gen_backends_alonira_string_duplicate(const char* const restrict string, const gen_size_t string_bounds, const gen_size_t string_length, const gen_size_t count, char* restrict* const restrict out_duplicated, gen_size_t* const restrict out_length);
extern gen_error_t* gen_backends_alonira_string_character_first(const char* const restrict string, const gen_size_t string_bounds, const gen_size_t string_length, const char character, const gen_size_t count, gen_size_t* const restrict out_found);
extern gen_error_t* gen_backends_alonira_string_character_last(const char* const restrict string, const gen_size_t string_bounds, const gen_size_t string_length, const char character, const gen_size_t count, gen_size_t* const restrict out_found);
extern gen_error_t* gen_backends_alonira_string_number(const char* const restrict string, const gen_size_t string_bounds, const gen_size_t string_length, const gen_size_t count, gen_size_t* const restrict out_number);
extern gen_error_t* gen_backends_alonira_string_format(const gen_size_t limit, char* const restrict out_buffer, gen_size_t* out_length, const char* const restrict format, const gen_size_t format_bounds, const gen_size_t format_length, ...);
extern gen_error_t* gen_backends_alonira_string_formatv(const gen_size_t limit, char* const restrict out_buffer, gen_size_t* const restrict out_length, const char* const restrict format, const gen_size_t format_bounds, const gen_size_t format_length, gen_variadic_list_t list);
extern gen_error_t* gen_backends_alonira_string_contains(const char* const restrict string, const gen_size_t string_bounds, const gen_size_t string_length, const char* const restrict target, const gen_size_t target_bounds, const gen_size_t target_length, const gen_size_t count, gen_size_t* const restrict out_offset);

#endif
