// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2023 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#ifndef ALO_KERNEL_BOOT_H
#define ALO_KERNEL_BOOT_H

#include <gencommon.h>
#include <genversion.h>

#include <aloarchgenericboot.h>

#ifndef ALO_BOOT_LOADER_NAME_MAX
#define ALO_BOOT_LOADER_NAME_MAX 255
#endif

typedef struct {
    alo_arch_boot_info_t arch_info;
    gen_version_t protocol_version;
    gen_version_t loader_version;
    char loader_name[ALO_BOOT_LOADER_NAME_MAX];
} alo_boot_info_t;

#endif
