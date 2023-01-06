// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2023 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#ifndef ALO_KERNEL_DISK_H
#define ALO_KERNEL_DISK_H

#include <gencommon.h>

typedef enum {
    ALO_DRIVE_TYPE_RAW,
    ALO_DRIVE_TYPE_GPT,
    ALO_DRIVE_TYPE_MBR,
    ALO_DRIVE_TYPE_ISOFS
} alo_drive_type_t;

typedef struct {
    alo_drive_type_t type;
    union {
        struct {
            gen_size_t index;
        } mbr;
        struct {
            gen_guid_t guid;
        } gpt;
        struct {
            gen_size_t index;
        } iso;
    };
} alo_drive_identifier_t;

typedef struct {
    alo_drive_identifier_t drive;
    union {
        struct {
            gen_size_t index;
        } mbr;
        struct {
            gen_guid_t guid;
        } gpt;
        struct {} iso;
    };
} alo_partition_identifier_t;

#endif
