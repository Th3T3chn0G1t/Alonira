
// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 TTG <prs.ttg+alonira@pm.me>

#include "include/alostring.h"

alo_error_t alo_string_compare(const char* const restrict a, const unsigned long a_bound, const char* const restrict b, const unsigned long b_bound, const unsigned long limit, bool* const restrict out_equal) {
	ALO_FRAME_BEGIN(alo_string_compare);

	ALO_NULL_CHECK(a);
	ALO_NULL_CHECK(b);
	ALO_NULL_CHECK(out_equal);

	*out_equal = true;

	if(!limit) ALO_ALL_OK;

	unsigned long a_length = 0;
	alo_error_t error = alo_string_length(a, a_bound, limit, &a_length);
	ALO_ERROR_OUT_IF(error, "`alo_string_length` failed");

	unsigned long b_length = 0;
	error = alo_string_length(b, b_bound, limit, &b_length);
	ALO_ERROR_OUT_IF(error, "`alo_string_length` failed");

	unsigned long compare_length = a_length;
	if(limit < compare_length) compare_length = limit;
	if(compare_length > b_length) compare_length = b_length;

	ALO_STRING_FOREACH(c, compare_length, a) {
		if(*c != b[c - a]) {
			*out_equal = false;
			ALO_ALL_OK;
		}
	}

	ALO_ALL_OK;
}

alo_error_t alo_string_copy(char* const restrict destination, const unsigned long destination_bound, const char* const restrict source, const unsigned long source_bound, const unsigned long limit) {
	ALO_FRAME_BEGIN(alo_string_copy);

	ALO_NULL_CHECK(destination);
	ALO_NULL_CHECK(source);

	if(!limit) ALO_ALL_OK;

	ALO_STRING_FOREACH(c, limit < destination_bound ? limit : destination_bound, destination)* c = '\0';

	unsigned long destination_length = 0;
	alo_error_t error = alo_string_length(destination, destination_bound, limit, &destination_length);
	ALO_ERROR_OUT_IF(error, "`alo_string_length` failed");

	unsigned long source_length = 0;
	error = alo_string_length(source, source_bound, limit, &source_length);
	ALO_ERROR_OUT_IF(error, "`alo_string_length` failed");

	unsigned long copy_length = source_length;
	if(limit < copy_length) copy_length = limit;

	ALO_STRING_FOREACH(c, copy_length, destination) {
		*c = source[c - destination];
	}

	ALO_ALL_OK;
}

alo_error_t alo_string_append(char* const restrict destination, const unsigned long destination_bound, const char* const restrict source, const unsigned long source_bound, const unsigned long limit) {
	ALO_FRAME_BEGIN(alo_string_append);

	ALO_NULL_CHECK(destination);
	ALO_NULL_CHECK(source);

	if(!limit) ALO_ALL_OK;

	unsigned long destination_length = 0;
	alo_error_t error = alo_string_length(destination, destination_bound, ALO_STRING_NO_BOUND, &destination_length);
	ALO_ERROR_OUT_IF(error, "`alo_string_length` failed");

	unsigned long source_length = 0;
	error = alo_string_length(source, source_bound, limit, &source_length);
	ALO_ERROR_OUT_IF(error, "`alo_string_length` failed");

	unsigned long append_length = source_length;
	if(limit < append_length) append_length = limit;

	if(destination_length + append_length + 1 > destination_bound) ALO_ERROR_OUT(ALO_TOO_SHORT, "Length of data to append was greater than string bounds");

	error = alo_string_copy(destination + destination_length, destination_bound - destination_length, source, source_bound, append_length);
	ALO_ERROR_OUT_IF(error, "`alo_string_copy` failed");

	ALO_ALL_OK;
}

alo_error_t alo_string_length(const char* const restrict string, const unsigned long string_bound, const unsigned long limit, unsigned long* const restrict out_length) {
	ALO_FRAME_BEGIN(alo_string_length);

	ALO_NULL_CHECK(string);
	ALO_NULL_CHECK(out_length);

	if(!limit) ALO_ALL_OK;

	*out_length = 0;

	ALO_STRING_FOREACH(c, string_bound, string) {
		if(!*c) ALO_ALL_OK;
		++*out_length;
	}

	if(*out_length > limit) *out_length = limit;
	if(limit == ALO_STRING_NO_BOUND) ALO_ERROR_OUT(ALO_TOO_SHORT, "String length exceeded string bounds");

	ALO_ALL_OK;
}

alo_error_t alo_string_character_first(const char* const restrict string, const unsigned long string_bound, const char character, const unsigned long limit, const char* restrict* const restrict out_found) {
	ALO_FRAME_BEGIN(alo_string_character_first);

	ALO_NULL_CHECK(string);
	ALO_NULL_CHECK(out_found);

	*out_found = NULL;

	if(!limit) ALO_ALL_OK;

	unsigned long string_length = 0;
	alo_error_t error = alo_string_length(string, string_bound, limit, &string_length);
	ALO_ERROR_OUT_IF(error, "`alo_string_length` failed");

	unsigned long search_length = string_length;
	if(limit < search_length) search_length = limit;

	ALO_STRING_FOREACH(c, search_length, string) {
		if(*c == character) {
			*out_found = c;
			ALO_ALL_OK;
		}
	}

	ALO_ALL_OK;
}

alo_error_t alo_string_character_last(const char* const restrict string, const unsigned long string_bound, const char character, const unsigned long limit, const char* restrict* const restrict out_found) {
	ALO_FRAME_BEGIN(alo_string_character_last);

	ALO_NULL_CHECK(string);

	*out_found = NULL;
	ALO_NULL_CHECK(out_found);

	if(!limit) ALO_ALL_OK;

	unsigned long string_length = 0;
	alo_error_t error = alo_string_length(string, string_bound, limit, &string_length);
	ALO_ERROR_OUT_IF(error, "`alo_string_length` failed");

	unsigned long search_length = string_length;
	if(limit < search_length) search_length = limit;

	ALO_STRING_FOREACH(c, search_length, string) {
		const char* const current = ((string + (string_length - 1)) - (c - string));
		if(*current == character) {
			*out_found = current;
			ALO_ALL_OK;
		}
	}

	ALO_ALL_OK;
}

alo_error_t alo_string_number(const char* const restrict string, const unsigned long string_bound, const unsigned long limit, unsigned long* const restrict out_number) {
	ALO_FRAME_BEGIN(alo_string_number);

	ALO_NULL_CHECK(string);
	ALO_NULL_CHECK(out_number);

	unsigned long length = 0;
	alo_error_t error = alo_string_length(string, string_bound, limit, &length);
	ALO_ERROR_OUT_IF(error, "`alo_string_length` failed");

	ALO_STRING_FOREACH(c, limit, string) {
		if(*c > '9' || *c < '0') ALO_ERROR_OUT(ALO_BAD_CONTENT, "`string` contained a non-numeric character");
		unsigned long digit = (unsigned long) (*c - '0');
		*out_number *= 10;
		*out_number += digit;
	}

	ALO_ALL_OK;
}
