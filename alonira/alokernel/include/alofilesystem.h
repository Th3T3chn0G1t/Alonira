// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2023 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#ifndef ALO_KERNEL_FILESYSTEM_H
#define ALO_KERNEL_FILESYSTEM_H

#include "alodisk.h"

#define ALO_FILESYSTEM_PATH_MAX (4096)

typedef struct {
    alo_partition_identifier_t location;
    char path[ALO_FILESYSTEM_PATH_MAX + 1];
} alo_file_location_t;

#endif
