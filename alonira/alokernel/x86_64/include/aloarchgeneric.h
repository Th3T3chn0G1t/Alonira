// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#ifndef ALO_KERNEL_X86_64_ARCH_GENERIC_H
#define ALO_KERNEL_X86_64_ARCH_GENERIC_H

#include <gencommon.h>

#include "aloboot.h"

#define ALO_BOOT_BLOCK GEN_ASM_BLOCK(GEN_ASM(cli))

extern GEN_NORETURN void alo_hang(void);
extern gen_error_t* alo_arch_generic_init(ALO_BOOT_SIGNATURE);

#endif
