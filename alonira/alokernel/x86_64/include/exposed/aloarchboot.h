// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#ifndef ALO_KERNEL_X86_64_ARCH_BOOT_H
#define ALO_KERNEL_X86_64_ARCH_BOOT_H

#include <gencommon.h>
#include <genversion.h>

GEN_PRAGMA(GEN_PRAGMA_DIAGNOSTIC_REGION_BEGIN)
GEN_PRAGMA(GEN_PRAGMA_DIAGNOSTIC_REGION_IGNORE("-Weverything"))
#include <ultra_protocol.h>
GEN_PRAGMA(GEN_PRAGMA_DIAGNOSTIC_REGION_END)

#define ALO_BOOT_SIGNATURE GEN_MAYBE_UNUSED struct ultra_boot_context* boot_data, GEN_MAYBE_UNUSED const unsigned int magic
#define ALO_BOOT_PASSTHROUGH boot_data, magic
#define ALO_BOOT_BLOCK GEN_ASM_BLOCK(GEN_ASM(cli))

typedef enum {
    ALO_BOOT_MODE_BIOS,
    ALO_BOOT_MODE_UEFI
} alo_boot_mode_t;

typedef struct {
    alo_boot_mode_t mode;
} alo_arch_boot_info_t;

#endif
