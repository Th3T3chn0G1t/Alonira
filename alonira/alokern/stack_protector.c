// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 TTG <prs.ttg+alonira@pm.me>

#include "include/kdiagnostic.h"

#include <alocom.h>

ALO_DIAGNOSTIC_REGION_BEGIN
#pragma clang diagnostic ignored "-Wreserved-identifier"

extern uintptr_t __stack_chk_guard;
__used uintptr_t __stack_chk_guard = 0xAFAFAFAFAFAFAFAF;

extern noreturn void __stack_chk_fail(void);
__used noreturn void __stack_chk_fail(void) {
	atrace;
	alo_panic(ALO_OUT_OF_BOUNDS, "Stack smashing detected");
}
ALO_DIAGNOSTIC_REGION_END
