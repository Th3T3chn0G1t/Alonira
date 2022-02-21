// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 TTG <prs.ttg+alonira@pm.me>

#ifndef ALO_STRING_H
#define ALO_STRING_H

#include "alocom.h"

#define ALO_STRING_NO_BOUND ((unsigned long) -1)

#define ALO_STRING_FOREACH(member, members_length, container) for(register __typeof__((container)[0])* member = &(container)[0]; (unsigned long) ((member) - (container)) < (members_length); ++(member))

ALO_ERRORABLE alo_string_compare(const char* const restrict a, const unsigned long a_bound, const char* const restrict b, const unsigned long b_bound, const unsigned long limit, bool* const restrict out_equal);
ALO_ERRORABLE alo_string_copy(char* const restrict destination, const unsigned long destination_bound, const char* const restrict source, const unsigned long source_bound, const unsigned long limit);
ALO_ERRORABLE alo_string_append(char* const restrict destination, const unsigned long destination_bound, const char* const restrict source, const unsigned long source_bound, const unsigned long limit);
ALO_ERRORABLE alo_string_length(const char* const restrict string, const unsigned long string_bound, const unsigned long limit, unsigned long* const restrict out_length);
ALO_ERRORABLE alo_string_character_first(const char* const restrict string, const unsigned long string_bound, const char character, const unsigned long limit, const char* restrict* const restrict out_found);
ALO_ERRORABLE alo_string_character_last(const char* const restrict string, const unsigned long string_bound, const char character, const unsigned long limit, const char* restrict* const restrict out_found);
ALO_ERRORABLE alo_string_number(const char* const restrict string, const unsigned long string_bound, const unsigned long limit, unsigned long* const restrict out_number);

#endif
