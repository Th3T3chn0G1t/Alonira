// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2023 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#ifndef TANAI_BPB_H
#define TANAI_BPB_H

#include <gencommon.h>

#include "tanaicommon.h"

typedef enum {
    TANAI_BPB_512_BYTES_PER_SECTOR = 512,
    TANAI_BPB_1024_BYTES_PER_SECTOR = 1024,
    TANAI_BPB_2048_BYTES_PER_SECTOR = 2048,
    TANAI_BPB_4096_BYTES_PER_SECTOR = 4096
} tanai_bpb_bytes_per_sector_t;

typedef enum {
    TANAI_BPB_1_SECTORS_PER_CLUSTER = 1,
    TANAI_BPB_2_SECTORS_PER_CLUSTER = 2,
    TANAI_BPB_4_SECTORS_PER_CLUSTER = 4,
    TANAI_BPB_8_SECTORS_PER_CLUSTER = 8,
    TANAI_BPB_16_SECTORS_PER_CLUSTER = 16,
    TANAI_BPB_32_SECTORS_PER_CLUSTER = 32,
    TANAI_BPB_64_SECTORS_PER_CLUSTER = 64,
    TANAI_BPB_128_SECTORS_PER_CLUSTER = 128
} tanai_bpb_sectors_per_cluster_t;

typedef enum {
    // TODO: This actually has more possible values for completeness' sake.
    TANAI_BPB_DRIVE_NUMBER_00 = 0,
    TANAI_BPB_DRIVE_NUMBER_80 = 0x80
} tanai_bpb_drive_number_t;

typedef enum {
    TANAI_BPB_BOOT_SIGNATURE_NOT_PRESENT = 0,
    TANAI_BPB_BOOT_SIGNATURE_PRESENT = 0x29
} tanai_bpb_boot_signature_t;

typedef enum {
    TANAI_BPB_NO_BACKUP = 0,
    TANAI_BPB_BACKUP_SECTOR_6 = 6
} tanai_bpb_backup_mode_t;

typedef struct GEN_PACKED {
    gen_uint8_t jmp[3];
    char oem_name[8];
    tanai_bpb_bytes_per_sector_t bytes_per_sector : 16;
    tanai_bpb_sectors_per_cluster_t sectors_per_cluster : 8;
    gen_uint16_t reserved_sectors;
    gen_uint8_t fat_count;
    gen_uint16_t root_directory_entries;
    gen_uint16_t total_sectors_16;
    struct {
        gen_bool_t two_sided : 1;
        gen_bool_t eight_sector : 1;
        gen_bool_t removable : 1;
        gen_uint8_t reserved : 5; // Must be 1
    } media_type;
    gen_uint16_t fat_size_16;
    gen_uint16_t sectors_per_track;
    gen_uint16_t head_count;
    gen_uint32_t hidden_sectors;
    gen_uint32_t total_sectors_32;
    union {
        struct GEN_PACKED {
            tanai_bpb_drive_number_t drive_number : 8;
            gen_uint8_t reserved0;
            tanai_bpb_boot_signature_t boot_signature : 8;
            gen_uint32_t volume_id;
            char volume_name[11];
            char filesystem_type[8];
            gen_uint8_t reserved1[448];
        } fat12_16;
        struct GEN_PACKED {
            gen_uint32_t fat_size_32;
            struct {
                gen_uint8_t active_fat_index : 4;
                gen_uint8_t reserved0 : 3;
                gen_bool_t mirrored : 1;
                gen_uint8_t reserved1;
            } flags;
            gen_uint16_t version;
            gen_uint32_t root_cluster;
            gen_uint16_t fs_info_sector;
            tanai_bpb_backup_mode_t backup_mode : 16;
            gen_uint8_t reserved0[12];
            tanai_bpb_drive_number_t drive_number : 8;
            gen_uint8_t reserved1;
            tanai_bpb_boot_signature_t boot_signature : 8;
            gen_uint32_t volume_id;
            char volume_name[11];
            char filesystem_type[8];
            gen_uint8_t reserved2[420];
        } fat32;
    };
    gen_uint8_t signature[2];
} tanai_bpb_t;

#define TANAI_BPB_OEM "TANAI  "

// TODO: Consider doing VBR for completeness' sake
#define TANAI_BPB_JMP_INIT { 0xEB, 0x3C, 0x90 }
#define TANAI_BPB_SIGNATURE_INIT { 0x55, 0xAA }

#define TANAI_BPB_LABEL_NONAME "NO NAME   "

// Just use one of them since they're the same
// Avoids making the API user distinguish needlessly
#define TANAI_BPB_VOLUME_NAME_SIZE GEN_MEMBER_SIZE(tanai_bpb_t, fat12_16.volume_name)

extern gen_error_t* tanai_bpb_create(const tanai_fat_type_t type, const gen_size_t sectors, const gen_size_t fats, const gen_size_t fat_sectors, const gen_size_t root_directory_length, const char* const restrict label, tanai_bpb_t* const restrict out_bpb);

#endif
