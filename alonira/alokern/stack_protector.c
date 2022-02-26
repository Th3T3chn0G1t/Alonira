// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 TTG <prs.ttg+alonira@pm.me>

#include "include/kdiagnostic.h"

#include <alocom.h>

ALO_DIAGNOSTIC_REGION_BEGIN
#pragma clang diagnostic ignored "-Wreserved-identifier"

#pragma clang diagnostic ignored "-Wmissing-variable-declarations"
__unused uintptr_t __stack_chk_guard = 0xAFAFAFAFAFAFAFAF;

#pragma clang diagnostic ignored "-Wmissing-prototypes"
__unused noreturn void __stack_chk_fail(void) {
	atrace;
	panic(ALO_OUT_OF_BOUNDS, "Stack smashing detected");
}
ALO_DIAGNOSTIC_REGION_END
