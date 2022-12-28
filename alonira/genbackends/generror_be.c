// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+genstone@pm.me>

#include <gencommon.h>
#include <kdiagnostic.h>
#include <vga.h>

#include "include/generror_be.h"

GEN_NORETURN void gen_backends_alonira_error_abort(void) {
    alo_vga_put_char_at_colored('E', ALO_VGA_COLOR_RED, ALO_VGA_COLOR_WHITE, 0, 0);
    alo_hang();
}
