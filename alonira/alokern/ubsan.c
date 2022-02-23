// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 TTG <prs.ttg+alonira@pm.me>

#include "include/kdiagnostic.h"
#include "include/vga.h"

#include <alocom.h>

ALO_DIAGNOSTIC_REGION_BEGIN
struct source_location {
	const char *file;
	unsigned int line;
	unsigned int column;
};

struct type_descriptor {
	unsigned short kind;
	unsigned short info;
	char name[];
};

struct type_mismatch_info {
	struct source_location location;
	struct type_descriptor *type;
	size_t alignment;
	unsigned char type_check_kind;
};

#pragma clang diagnostic ignored "-Wgnu-variable-sized-type-not-at-end"
#pragma clang diagnostic ignored "-Wflexible-array-extensions"
struct out_of_bounds_info {
	struct source_location location;
	struct type_descriptor left_type;
	struct type_descriptor right_type;
};

#pragma clang diagnostic ignored "-Wmissing-prototypes"
#pragma clang diagnostic ignored "-Wreserved-identifier"
__unused noreturn void __ubsan_handle_mul_overflow(void) {
	panic(ALO_UNKNOWN, "UBSan stub");
}
__unused noreturn void __ubsan_handle_add_overflow(void) {
	panic(ALO_UNKNOWN, "UBSan stub");
}
__unused noreturn void __ubsan_handle_divrem_overflow(void) {
	panic(ALO_UNKNOWN, "UBSan stub");
}
__unused noreturn void __ubsan_handle_sub_overflow(void) {
	panic(ALO_UNKNOWN, "UBSan stub");
}
__unused noreturn void __ubsan_handle_pointer_overflow(void) {
	panic(ALO_UNKNOWN, "UBSan stub");
}
__unused noreturn void __ubsan_handle_type_mismatch_v1(void) {
	panic(ALO_UNKNOWN, "UBSan stub");
}
__unused noreturn void __ubsan_handle_shift_out_of_bounds(void) {
	panic(ALO_UNKNOWN, "UBSan stub");
}
__unused noreturn void __ubsan_handle_builtin_unreachable(void) {
	panic(ALO_UNKNOWN, "UBSan stub");
}
__unused noreturn void __ubsan_handle_out_of_bounds(void) {
	panic(ALO_UNKNOWN, "UBSan stub");
}

ALO_DIAGNOSTIC_REGION_END
