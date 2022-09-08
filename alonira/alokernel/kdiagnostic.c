// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include "include/kdiagnostic.h"

GEN_NORETURN void alo_hang(void) {
    ALO_ASM_BLOCK(ALO_ASM(cli));
    while(true) ALO_ASM_BLOCK(ALO_ASM(hlt));
}
