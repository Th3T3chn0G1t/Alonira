// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 TTG <prs.ttg+alonira@pm.me>

#include "include/kdiagnostic.h"
#include "include/vga.h"

#include <alocom.h>

ALO_DIAGNOSTIC_REGION_BEGIN
#pragma clang diagnostic ignored "-Wreserved-identifier"

typedef struct {
	const char* const filename;
	const uint32_t line;
	const uint32_t column;
} __ubsan_source_location;

typedef struct {
	const enum {
		__ubsan_type_kind_integer = 0x0000,
		__ubsan_type_kind_float = 0x0001,
		__ubsan_type_kind_unknown = 0xffff
	} type_kind;
	const uint16_t type_info;
	const char* type_name;
} __ubsan_type_descriptor;

typedef struct {
	const __ubsan_type_descriptor* const type;
	const void* const value;
} __ubsan_value_handle;

/*
  signed integer: type_kind == __ubsan_type_kind_integer &&  (type_info & 1)
unsigned integer: type_kind == __ubsan_type_kind_integer && !(type_info & 1)
		   float: type_kind == __ubsan_type_kind_float

   integer width: 1 << (type_info >> 1)
     float width: type_info
*/

typedef struct {
	const __ubsan_source_location at;
	const __ubsan_type_descriptor* const type;
	unsigned char alignment;
	unsigned char type_check_kind;
} __ubsan_type_mismatch_data;

typedef struct {
	const __ubsan_source_location at;
	const __ubsan_source_location from;
	const __ubsan_type_descriptor* const type;
} __ubsan_alignment_assumption_data;

typedef struct {
	const __ubsan_source_location at;
	const __ubsan_type_descriptor* const Type;
} __ubsan_overflow_data;

typedef struct {
	const __ubsan_source_location at;
	const __ubsan_type_descriptor* const left_type;
	const __ubsan_type_descriptor* const right_type;
} __ubsan_shift_out_of_bounds_data;

#pragma clang diagnostic ignored "-Wmissing-prototypes"
__unused noreturn void __ubsan_handle_mul_overflow(void) {
	ALO_FRAME_BEGIN(__ubsan_handle_mul_overflow);
	panic(ALO_UNKNOWN, "UBSan stub: __ubsan_handle_mul_overflow");
}
__unused noreturn void __ubsan_handle_add_overflow(void) {
	ALO_FRAME_BEGIN(__ubsan_handle_add_overflow);
	panic(ALO_UNKNOWN, "UBSan stub: __ubsan_handle_add_overflow");
}
__unused noreturn void __ubsan_handle_divrem_overflow(void) {
	ALO_FRAME_BEGIN(__ubsan_handle_divrem_overflow);
	panic(ALO_UNKNOWN, "UBSan stub: __ubsan_handle_divrem_overflow");
}
__unused noreturn void __ubsan_handle_sub_overflow(void) {
	ALO_FRAME_BEGIN(__ubsan_handle_sub_overflow);
	panic(ALO_UNKNOWN, "UBSan stub: __ubsan_handle_sub_overflow");
}
__unused noreturn void __ubsan_handle_pointer_overflow(void) {
	ALO_FRAME_BEGIN(__ubsan_handle_pointer_overflow);
	panic(ALO_UNKNOWN, "UBSan stub: __ubsan_handle_pointer_overflow");
}
__unused noreturn void __ubsan_handle_type_mismatch_v1(void) {
	ALO_FRAME_BEGIN(__ubsan_handle_type_mismatch_v1);
	panic(ALO_UNKNOWN, "UBSan stub: __ubsan_handle_type_mismatch_v1");
}
__unused noreturn void __ubsan_handle_shift_out_of_bounds(void) {
	ALO_FRAME_BEGIN(__ubsan_handle_shift_out_of_bounds);
	panic(ALO_UNKNOWN, "UBSan stub: __ubsan_handle_shift_out_of_bounds");
}
__unused noreturn void __ubsan_handle_builtin_unreachable(void) {
	ALO_FRAME_BEGIN(__ubsan_handle_builtin_unreachable);
	panic(ALO_UNKNOWN, "UBSan stub: __ubsan_handle_builtin_unreachable");
}
__unused noreturn void __ubsan_handle_out_of_bounds(void) {
	ALO_FRAME_BEGIN(__ubsan_handle_out_of_bounds);
	panic(ALO_UNKNOWN, "UBSan stub: __ubsan_handle_out_of_bounds");
}

ALO_DIAGNOSTIC_REGION_END
