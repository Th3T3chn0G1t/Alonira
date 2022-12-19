// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include "include/kdiagnostic.h"

GEN_NORETURN void alo_hang(void) {
    GEN_ASM_BLOCK(GEN_ASM(cli));
    while(gen_true) GEN_ASM_BLOCK(GEN_ASM(hlt));
}
