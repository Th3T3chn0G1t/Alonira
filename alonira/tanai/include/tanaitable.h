// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2023 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#ifndef TANAI_TABLE_H
#define TANAI_TABLE_H

#include <gencommon.h>

#include "tanaibpb.h"

#define TANAI_FAT_ENTRY_FREE 0

typedef gen_uint16_t* tanai_fat12_t;
typedef gen_uint16_t* tanai_fat16_t;
typedef gen_uint32_t* tanai_fat32_t;

typedef union GEN_PACKED {
    tanai_fat12_t fat12;
    tanai_fat16_t fat16;
    tanai_fat32_t fat32;
} tanai_fat_t;

#define TANAI_FAT12_ENTRY_EOF 0xFFF
#define TANAI_FAT16_ENTRY_EOF 0xFFFF
#define TANAI_FAT32_ENTRY_EOF 0xFFFFFFFF
#define TANAI_FAT_ENTRY_EOF(type) \
    ((gen_uint32_t[]){ \
        [TANAI_TYPE_FAT12] = TANAI_FAT12_ENTRY_EOF, \
        [TANAI_TYPE_FAT16] = TANAI_FAT16_ENTRY_EOF, \
        [TANAI_TYPE_FAT32] = TANAI_FAT32_ENTRY_EOF \
    }[type])

#define TANAI_FAT12_ENTRY_BAD 0xFF7
#define TANAI_FAT16_ENTRY_BAD 0xFFF7
#define TANAI_FAT32_ENTRY_BAD 0xFFFFFFF7
#define TANAI_FAT_ENTRY_BAD(type) \
    ((gen_uint32_t[]){ \
        [TANAI_TYPE_FAT12] = TANAI_FAT12_ENTRY_BAD, \
        [TANAI_TYPE_FAT16] = TANAI_FAT16_ENTRY_BAD, \
        [TANAI_TYPE_FAT32] = TANAI_FAT32_ENTRY_BAD \
    }[type])

extern gen_error_t* tanai_fat_write(const tanai_fat_type_t type, const tanai_bpb_t* const restrict bpb, tanai_fat_t* const restrict fat, const gen_size_t index, const gen_uint32_t value);
extern gen_error_t* tanai_fat_init(const tanai_fat_type_t type, const tanai_bpb_t* const restrict bpb, tanai_fat_t* const restrict fat);

#endif
