// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#ifndef ALO_KERNEL_ARCH_H
#define ALO_KERNEL_ARCH_H

#include <gencommon.h>

#include <aloboot.h>

extern gen_error_t* alo_arch_init(ALO_BOOT_SIGNATURE, alo_boot_info_t* const restrict out_boot_info);

#endif
