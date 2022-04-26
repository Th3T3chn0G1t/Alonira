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
	const enum
	{
		__ubsan_type_kind_integer = 0x0000,
		__ubsan_type_kind_float = 0x0001,
		__ubsan_type_kind_unknown = 0xFFFF
	} type_kind;
	const uint16_t type_info;
	const char* type_name;
} __ubsan_type_descriptor;

typedef struct {
	const __ubsan_type_descriptor* const type;
	const void* const value;
} __ubsan_value;

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
	enum
	{
		__ubsan_type_check_kind_load,
		__ubsan_type_check_kind_store,
		__ubsan_type_check_kind_reference_binding,
		__ubsan_type_check_kind_member_access,
		__ubsan_type_check_kind_member_call,
		__ubsan_type_check_kind_constructor_call,
		__ubsan_type_check_kind_downcast_pointer,
		__ubsan_type_check_kind_downcast_reference,
		__ubsan_type_check_kind_upcast,
		__ubsan_type_check_kind_upcast_to_virtual_base,
		__ubsan_type_check_kind_nonnull_assign,
		__ubsan_type_check_kind_dynamic_operation
	} kind : 8;
} __ubsan_type_mismatch_data;

typedef struct {
	const __ubsan_source_location at;
	const __ubsan_source_location from;
	const __ubsan_type_descriptor* const type;
} __ubsan_alignment_assumption_data;

typedef struct {
	const __ubsan_source_location at;
	const __ubsan_type_descriptor* const type;
} __ubsan_overflow_data;

typedef struct {
	const __ubsan_source_location at;
	const __ubsan_type_descriptor* const left_type;
	const __ubsan_type_descriptor* const right_type;
} __ubsan_shift_out_of_bounds_data;

typedef struct {
	const __ubsan_source_location at;
	const __ubsan_type_descriptor* const array_type;
	const __ubsan_type_descriptor* const index_type;
} __ubsan_out_of_bounds_data;

typedef struct {
	const __ubsan_source_location at;
} __ubsan_unreachable_data;

typedef struct {
	const __ubsan_source_location at;
	const __ubsan_type_descriptor* const type;
} __ubsan_vla_bound_data;

typedef struct {
	const __ubsan_source_location at;
	const __ubsan_type_descriptor* const from_type;
	const __ubsan_type_descriptor* const to_type;
} __ubsan_float_cast_overflow_data_v2;

typedef struct {
	const __ubsan_source_location at;
	const __ubsan_type_descriptor* const type;
} __ubsan_invalid_value_data;

typedef struct {
	const __ubsan_source_location at;
	const __ubsan_type_descriptor* const from_type;
	const __ubsan_type_descriptor* const to_type;
	enum
	{
		__ubsan_implicit_conversion_check_integer_truncation = 0,
		__ubsan_implicit_conversion_check_unsigned_integer_truncation = 1,
		__ubsan_implicit_conversion_check_signed_integer_truncation = 2,
		__ubsan_implicit_conversion_check_integer_sign_change = 3,
		__ubsan_implicit_conversion_check_signed_integer_truncation_or_sign_change = 4
	} kind : 8;
} __ubsan_implicit_conversion_data;

typedef struct {
	const __ubsan_source_location at;
	enum
	{
		__ubsan_builtin_conversion_kind_ctz_passed_zero, // Count tailing zeroes
		__ubsan_builtin_conversion_kind_clz_passed_zero, // Count leading zeroes
	} kind : 8;
} __ubsan_invalid_builtin_data;

typedef struct {
	const __ubsan_source_location at;
} __ubsan_non_null_return_data;

typedef struct {
	const __ubsan_source_location call;
	const __ubsan_source_location at;
	int arg_index;
} __ubsan_non_null_arg_data;

typedef struct {
	const __ubsan_source_location at;
} __ubsan_pointer_overflow_data;

typedef struct {
	enum
	{
		__ubsan_control_flow_integrity_type_check_kind_vcall,
		__ubsan_control_flow_integrity_type_check_kind_nvcall,
		__ubsan_control_flow_integrity_type_check_kind_derived_cast,
		__ubsan_control_flow_integrity_type_check_kind_unrelated_cast,
		__ubsan_control_flow_integrity_type_check_kind_icall,
		__ubsan_control_flow_integrity_type_check_kind_nvmfcall,
		__ubsan_control_flow_integrity_type_check_kind_vmfcall,
	} kind;
	const __ubsan_source_location at;
	const __ubsan_type_descriptor* const type;
} __ubsan_control_flow_integrity_check_fail_data;

__unused static const char* const __ubsan_type_check_kinds[] = {
	"Load of", "Store to", "Reference binding to", "Member access within",
	"Member call on", "Constructor call on", "Downcast of", "Downcast of",
	"Upcast of", "Cast to virtual base of", "`_Nonnull` binding to",
	"Dynamic operation on"};

#pragma clang diagnostic ignored "-Wmissing-prototypes"
__nosanitize __unused noreturn void __ubsan_handle_type_mismatch_v1(const __ubsan_type_mismatch_data* const restrict data, const __ubsan_value* const restrict pointer) {
	ALO_FRAME_BEGIN(__ubsan_handle_type_mismatch_v1);
	alogf(FATAL, "At %s:%u:%u", data->at.filename, data->at.line, data->at.column);
	(void) pointer;
	// if(!pointer)
	// 	alogf(FATAL, "%s null pointer of type %s", __ubsan_type_check_kinds[data->kind], data->type->type_name);
	// else if((uintptr_t) pointer->value & (data->alignment - 1))
	// 	alogf(FATAL, "%s misaligned address %p for type %s which requires %zu", __ubsan_type_check_kinds[data->kind], pointer, data->type->type_name, 1 << data->alignment);
	// else
	// 	alogf(FATAL, "%s address %p with insufficient space for an object of type %s", __ubsan_type_check_kinds[data->kind], pointer, data->type->type_name);
	panic(ALO_WRONG_OBJECT_TYPE, "`__ubsan_handle_type_mismatch_v1` tripped");
}

#pragma clang diagnostic ignored "-Wpointer-arith"
__nosanitize __unused noreturn void __ubsan_handle_alignment_assumption(const __ubsan_alignment_assumption_data* const restrict data, const __ubsan_value* const restrict pointer, const __ubsan_value* const restrict alignment, const __ubsan_value* const restrict offset) {
	ALO_FRAME_BEGIN(__ubsan_handle_alignment_assumption);
	alogf(FATAL, "At %s:%u:%u", data->at.filename, data->at.line, data->at.column);
	(void) pointer;
	(void) alignment;
	(void) offset;
	// alogf(FATAL, "From %s:%u:%u", data->from.filename, data->from.line, data->from.column);
	// const uintptr_t real_pointer = (uintptr_t) pointer->value - (uintptr_t) offset->value;
	// if(!offset->value)
	// 	alogf(FATAL, "Assumption of %zu byte alignment for pointer of type %s failed", alignment->value, data->type->type_name);
	// else
	// 	alogf(FATAL, "%p is aligned to %zu, misalignment offset is %zu", real_pointer, 1 << __builtin_ctzl(real_pointer), (uintptr_t) real_pointer & (uintptr_t) (alignment->value - 1));
	panic(ALO_BAD_ALIGNMENT, "`__ubsan_handle_alignment_assumption` tripped");
}

__unused void __ubsan_handle_overflow(const __ubsan_overflow_data* const restrict data, const __ubsan_value* const restrict left, const char operator, const size_t right) {
	ALO_FRAME_BEGIN(__ubsan_handle_overflow);
	alogf(FATAL, "At %s:%u:%u", data->at.filename, data->at.line, data->at.column);
	(void) operator;
	(void) left;
	(void) right;
	// if(data) panic(ALO_UNKNOWN, "???");
	// if(data->type->type_info & 1)
	// alogf(FATAL, "Signed integer overflow: %c %i cannot be represented in type %s", operator, right, data->type);
	// alogf(FATAL, "Signed integer overflow: %li %c %li cannot be represented in type %s", left->value, operator, right, data->type->type_name);
	// else
	// 	alogf(FATAL, "Unsigned integer overflow: %lu %c %lu cannot be represented in type %s", left->value, operator, right, data->type->type_name);
}
__nosanitize __unused noreturn void __ubsan_handle_mul_overflow(const __ubsan_overflow_data* const restrict data, const __ubsan_value* const restrict left, const __ubsan_value* const restrict right) {
	ALO_FRAME_BEGIN(__ubsan_handle_mul_overflow);
	alogf(FATAL, "At %s:%u:%u", data->at.filename, data->at.line, data->at.column);
	(void) left;
	(void) right;
	// __ubsan_handle_overflow(data, left, '*', (size_t) right->value);
	panic(ALO_TOO_LONG, "`__ubsan_handle_mul_overflow` was tripped");
}
__nosanitize __unused noreturn void __ubsan_handle_add_overflow(const __ubsan_overflow_data* const restrict data, const __ubsan_value* const restrict left, const __ubsan_value* const restrict right) {
	ALO_FRAME_BEGIN(__ubsan_handle_add_overflow);
	alogf(FATAL, "At %s:%u:%u", data->at.filename, data->at.line, data->at.column);
	(void) left;
	(void) right;
	// __ubsan_handle_overflow(data, left, '+', (size_t) right->value);
	panic(ALO_TOO_LONG, "`__ubsan_handle_add_overflow` was tripped");
}
__nosanitize __unused noreturn void __ubsan_handle_sub_overflow(const __ubsan_overflow_data* const restrict data, const __ubsan_value* const restrict left, const __ubsan_value* const restrict right) {
	ALO_FRAME_BEGIN(__ubsan_handle_sub_overflow);
	alogf(FATAL, "At %s:%u:%u", data->at.filename, data->at.line, data->at.column);
	(void) left;
	(void) right;
	// __ubsan_handle_overflow(data, left, '-', (size_t) right->value);
	panic(ALO_TOO_LONG, "`__ubsan_handle_sub_overflow` was tripped");
}

__nosanitize __unused noreturn void __ubsan_handle_divrem_overflow(const __ubsan_overflow_data* const restrict data, const __ubsan_value* const restrict left, const __ubsan_value* const restrict right) {
	ALO_FRAME_BEGIN(__ubsan_handle_divrem_overflow);
	alogf(FATAL, "At %s:%u:%u", data->at.filename, data->at.line, data->at.column);
	(void) left;
	(void) right;
	panic(ALO_TOO_LONG, "`__ubsan_handle_divrem_overflow` was tripped");
}
__nosanitize __unused noreturn void __ubsan_handle_pointer_overflow(const __ubsan_pointer_overflow_data* const restrict data, const __ubsan_value* const restrict base, const __ubsan_value* const restrict result) {
	ALO_FRAME_BEGIN(__ubsan_handle_pointer_overflow);
	alogf(FATAL, "At %s:%u:%u", data->at.filename, data->at.line, data->at.column);
	(void) base;
	(void) result;
	panic(ALO_TOO_LONG, "`__ubsan_handle_pointer_overflow` was tripped");
}
__nosanitize __unused noreturn void __ubsan_handle_invalid_builtin(const __ubsan_invalid_builtin_data* const restrict data) {
	ALO_FRAME_BEGIN(__ubsan_handle_invalid_builtin);
	alogf(FATAL, "At %s:%u:%u", data->at.filename, data->at.line, data->at.column);
	panic(ALO_INVALID_PARAMETER, "`__ubsan_handle_invalid_builtin` was tripped");
}
__nosanitize __unused noreturn void __ubsan_handle_shift_out_of_bounds(const __ubsan_shift_out_of_bounds_data* const restrict data, const __ubsan_value* const restrict left, const __ubsan_value* const restrict right) {
	ALO_FRAME_BEGIN(__ubsan_handle_shift_out_of_bounds);
	alogf(FATAL, "At %s:%u:%u", data->at.filename, data->at.line, data->at.column);
	(void) left;
	(void) right;
	panic(ALO_OUT_OF_BOUNDS, "`__ubsan_handle_shift_out_of_bounds` was tripped");
}
__nosanitize __unused noreturn void __ubsan_handle_builtin_unreachable(const __ubsan_unreachable_data* const restrict data) {
	ALO_FRAME_BEGIN(__ubsan_handle_builtin_unreachable);
	alogf(FATAL, "At %s:%u:%u", data->at.filename, data->at.line, data->at.column);
	panic(ALO_INVALID_CONTROL, "`__ubsan_handle_builtin_unreachable` was tripped");
}
__nosanitize __unused noreturn void __ubsan_handle_out_of_bounds(const __ubsan_out_of_bounds_data* const restrict data, const __ubsan_value* const restrict offset) {
	ALO_FRAME_BEGIN(__ubsan_handle_out_of_bounds);
	alogf(FATAL, "At %s:%u:%u", data->at.filename, data->at.line, data->at.column);
	(void) offset;
	panic(ALO_OUT_OF_BOUNDS, "`__ubsan_handle_out_of_bounds` was tripped");
}

ALO_DIAGNOSTIC_REGION_END
