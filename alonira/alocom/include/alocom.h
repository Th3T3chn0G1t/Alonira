// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 TTG <prs.ttg+alonira@pm.me>

#ifndef ALO_COMMON_H
#define ALO_COMMON_H

#define NULL ((void*) 0)
typedef _Bool bool;
#define true ((bool) 1)
#define false ((bool) 0)

#define noreturn _Noreturn
#define pragma _Pragma
#define generic _Generic

#define ALO_DIAGNOSTIC_REGION_BEGIN pragma("clang diagnostic push")
#define ALO_DIAGNOSTIC_REGION_END pragma("clang diagnostic pop")
#define ALO_DIAGNOSTIC_IGNORE_ALL pragma("clang diagnostic ignored \"-Weverything\"")

ALO_DIAGNOSTIC_REGION_BEGIN
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#ifndef __unused
#define __unused __attribute__((unused))
#endif
#ifndef __forceinline
#define __forceinline __attribute__((always_inline)) __attribute__((artificial)) inline
#endif
#ifndef __deprecated
#define __deprecated(msg) __attribute__((deprecated(msg)))
#endif
#ifndef __nodiscard
#define __nodiscard __attribute__((warn_unused_result))
#endif
ALO_DIAGNOSTIC_REGION_END

typedef enum {
	ALO_OK = 0,
	ALO_UNKNOWN,
	ALO_PERMISSION,
	ALO_INVALID_PARAMETER,
	ALO_IO,
	ALO_TOO_LONG,
	ALO_NO_SUCH_OBJECT,
	ALO_OUT_OF_MEMORY,
	ALO_WRONG_OBJECT_TYPE,
	ALO_ALREADY_EXISTS,
	ALO_OUT_OF_SPACE,
	ALO_OUT_OF_HANDLES,
	ALO_TOO_SHORT,
	ALO_BAD_CONTENT,
	ALO_BAD_OPERATION,
	ALO_IN_USE,
	ALO_NOT_IMPLEMENTED,
	ALO_OUT_OF_BOUNDS
} alo_error_t;

#define ALO_ERRORABLE extern __nodiscard alo_error_t

extern const char* alo_error_name(const alo_error_t error);
extern const char* alo_error_description(const alo_error_t error);

#define ALO_INTERNAL_OUTPUT_ERROR_MESSAGE(error, message)

#define ALO_ALL_OK return ALO_OK
#define ALO_ERROR_OUT(error, message) \
	do { \
		ALO_INTERNAL_OUTPUT_ERROR_MESSAGE(error, message); \
		return error; \
	} while(0)
#define ALO_ERROR_OUT_IF(error, message) if(error != ALO_OK) ALO_ERROR_OUT(error, message)
#define ALO_NULL_CHECK(param) if(!param) ALO_ERROR_OUT(ALO_INVALID_PARAMETER, "`" #param "` was NULL")

ALO_DIAGNOSTIC_REGION_BEGIN
#pragma clang diagnostic ignored "-Wlanguage-extension-token"
static noreturn __forceinline void hang(void) { while(true) asm("hlt"); }
ALO_DIAGNOSTIC_REGION_END

#define ALO_FRAME_BEGIN(function) (void) NULL

#endif
