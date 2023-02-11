// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2023 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#ifndef TANAI_COMMON_H
#define TANAI_COMMON_H

#define TANAI_SECTOR 512

typedef enum {
    TANAI_TYPE_FAT12,
    TANAI_TYPE_FAT16,
    TANAI_TYPE_FAT32,

    TANAI_FAT_TYPE_MAX = TANAI_TYPE_FAT32
} tanai_fat_type_t;

#endif
