// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+genstone@pm.me>

#include <gencommon.h>
#include <kdiagnostic.h>

#include "include/generror_be.h"

GEN_NORETURN void gen_backends_alonira_error_abort(void) {
    alo_hang();
}
