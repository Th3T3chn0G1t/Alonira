// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 TTG <prs.ttg+alonira@pm.me>

#ifndef ALO_STRING_H
#define ALO_STRING_H

#include "alocom.h"

#define ALO_STRING_NO_BOUND ((size_t) -1)

#define ALO_STRING_FOREACH(member, members_length, container) for(register __typeof__((container)[0])* member = &(container)[0]; (size_t) ((member) - (container)) < (members_length); ++(member))

ALO_ERRORABLE alo_string_compare(const char* const restrict a, const size_t a_bound, const char* const restrict b, const size_t b_bound, const size_t limit, bool* const restrict out_equal);
ALO_ERRORABLE alo_string_copy(char* const restrict destination, const size_t destination_bound, const char* const restrict source, const size_t source_bound, const size_t limit);
ALO_ERRORABLE alo_string_append(char* const restrict destination, const size_t destination_bound, const char* const restrict source, const size_t source_bound, const size_t limit);
ALO_ERRORABLE alo_string_length(const char* const restrict string, const size_t string_bound, const size_t limit, size_t* const restrict out_length);
ALO_ERRORABLE alo_string_character_first(const char* const restrict string, const size_t string_bound, const char character, const size_t limit, const char* restrict* const restrict out_found);
ALO_ERRORABLE alo_string_character_last(const char* const restrict string, const size_t string_bound, const char character, const size_t limit, const char* restrict* const restrict out_found);
ALO_ERRORABLE alo_string_number(const char* const restrict string, const size_t string_bound, const size_t limit, size_t* const restrict out_number);

#endif
