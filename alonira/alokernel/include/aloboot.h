// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2023 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#ifndef ALO_KERNEL_BOOT_H
#define ALO_KERNEL_BOOT_H

#include <gencommon.h>
#include <genversion.h>

#include <aloarchgenericboot.h>

#include "alofilesystem.h"
#include "alodisk.h"
#include "alophysicalmemory.h"

#ifndef ALO_BOOT_LOADER_NAME_MAX
#define ALO_BOOT_LOADER_NAME_MAX 255
#endif

#ifndef ALO_BOOT_MEMORY_RANGE_MAX
#define ALO_BOOT_MEMORY_RANGE_MAX 255
#endif

#ifndef ALO_BOOT_COMMAND_LINE_MAX
#define ALO_BOOT_COMMAND_LINE_MAX 512
#endif

typedef struct {
    alo_arch_boot_info_t arch_info;

    gen_version_t protocol_version;
    gen_version_t loader_version;
    char loader_name[ALO_BOOT_LOADER_NAME_MAX];

    alo_file_location_t kernel_location;

    gen_uintptr_t kernel_physical_base;
    gen_uintptr_t kernel_virtual_base;
    gen_uintptr_t kernel_size;

    alo_physical_memory_range_t physical_memory_ranges[ALO_BOOT_MEMORY_RANGE_MAX];

    char command_line[ALO_BOOT_COMMAND_LINE_MAX + 1];
} alo_boot_info_t;

#endif
