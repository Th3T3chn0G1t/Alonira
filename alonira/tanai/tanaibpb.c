// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2023 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include "include/tanaibpb.h"

#include <genmemory.h>
#include <genstring.h>

gen_error_t* tanai_bpb_create(const tanai_fat_type_t type, const gen_size_t sectors, const gen_size_t fats, const gen_size_t fat_sectors, const gen_size_t root_directory_length, const char* const restrict label, tanai_bpb_t* const restrict out_bpb) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) tanai_bpb_create, GEN_FILE_NAME);
    if(error) return error;

    if(!out_bpb) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`out_bpb` was GEN_NULL");

    char disk_label[TANAI_BPB_VOLUME_NAME_SIZE] = TANAI_BPB_LABEL_NONAME;
    if(label) {
        error = gen_memory_set(disk_label, TANAI_BPB_VOLUME_NAME_SIZE, TANAI_BPB_VOLUME_NAME_SIZE, ' ');
        if(error) return error;

        gen_size_t length = 0;
        error = gen_string_length(label, GEN_STRING_NO_BOUNDS, TANAI_BPB_VOLUME_NAME_SIZE, &length);
        if(error) return error;

        error = gen_memory_copy(disk_label, TANAI_BPB_VOLUME_NAME_SIZE, label, length + 1, length);
        if(error) return error;
    }

    static const gen_size_pair_t table_fat12[] = {
        {0, 0},
        {1, TANAI_BPB_1_SECTORS_PER_CLUSTER},
        {8400, 0}
    };

    // These tables are just from the spec
    static const gen_size_pair_t table_fat16[] = {
        {8400, 0},
        {32680, TANAI_BPB_2_SECTORS_PER_CLUSTER},
        {262144, TANAI_BPB_4_SECTORS_PER_CLUSTER},
        {524288, TANAI_BPB_8_SECTORS_PER_CLUSTER},
        {1048576, TANAI_BPB_16_SECTORS_PER_CLUSTER},
        {2097152, TANAI_BPB_32_SECTORS_PER_CLUSTER},
        {4194304, TANAI_BPB_64_SECTORS_PER_CLUSTER},
        {0xFFFFFFFF, 0}
    };

    static const gen_size_pair_t table_fat32[] = {
        {66600, 0},
        {532480, TANAI_BPB_1_SECTORS_PER_CLUSTER},
        {16777216, TANAI_BPB_8_SECTORS_PER_CLUSTER},
        {33554432, TANAI_BPB_16_SECTORS_PER_CLUSTER},
        {67108864, TANAI_BPB_32_SECTORS_PER_CLUSTER},
        {0xFFFFFFFF, TANAI_BPB_64_SECTORS_PER_CLUSTER}
    };

    const gen_size_pair_t* table = GEN_NULL;
    gen_size_t table_length = 0;
    switch(type) {
        case TANAI_TYPE_FAT12: table = table_fat12; table_length = GEN_ARRAY_LENGTH(table_fat12); break;
        case TANAI_TYPE_FAT16: table = table_fat16; table_length = GEN_ARRAY_LENGTH(table_fat16); break;
        case TANAI_TYPE_FAT32: table = table_fat32; table_length = GEN_ARRAY_LENGTH(table_fat32); break;
    }

    gen_size_t sectors_per_cluster = 0;
    for(gen_size_t i = 0; i < table_length - 1; ++i) {
        if(sectors >= table[i][0] && sectors < table[i + 1][0]) {
            sectors_per_cluster = table[i][1];
            break;
        }
    }

    if(!sectors_per_cluster) {
        gen_size_t last = table[table_length - 1][0];
        if(!table[table_length - 1][1]) last = table[table_length - 2][0]; // We don't want to print the bounding values
        return gen_error_attach_backtrace_formatted(GEN_ERROR_OUT_OF_BOUNDS, GEN_LINE_NUMBER, "Input data size of %zu sectors is out of range of FAT%u %u-%zu\n", sectors, type, table[0][0], last);
    }

    gen_size_t total_sectors = sectors + fat_sectors + 1;

    tanai_bpb_t bpb = {
        TANAI_BPB_JMP_INIT,
        TANAI_BPB_OEM,
        TANAI_BPB_512_BYTES_PER_SECTOR,
        (gen_uint16_t) sectors_per_cluster,
        1, /* Reserved sector count - sector count of bpb for here */
        (gen_uint8_t) fats,
        (gen_uint16_t) root_directory_length,
        total_sectors < GEN_UINT16_MAX ? (gen_uint16_t) total_sectors : 0 /* Account for BPB */,
        { gen_false, gen_false, gen_false, 0b11111 /* Must be all ones */ }, /* Non-removable, single-sided, non-8-sector disk - i.e. hard disk */
        (gen_uint16_t) fat_sectors, /* Sectors per FAT */
        1, 1, /* Dummy CHS stuff */
        0,
        total_sectors > GEN_UINT16_MAX ? (gen_uint32_t) total_sectors : 0,
        { 0 },
        TANAI_BPB_SIGNATURE_INIT
    };

    switch(type) {
        case TANAI_TYPE_FAT12: GEN_FALLTHROUGH;
        case TANAI_TYPE_FAT16: {
            bpb.fat12_16.drive_number = TANAI_BPB_DRIVE_NUMBER_00;
            bpb.fat12_16.boot_signature = TANAI_BPB_BOOT_SIGNATURE_PRESENT;
            bpb.fat12_16.volume_id = 0;
            error = gen_memory_copy(bpb.fat12_16.volume_name, TANAI_BPB_VOLUME_NAME_SIZE, disk_label, TANAI_BPB_VOLUME_NAME_SIZE, TANAI_BPB_VOLUME_NAME_SIZE);
            if(error) return error;
            error = gen_memory_copy(bpb.fat12_16.filesystem_type, sizeof(bpb.fat12_16.filesystem_type), type == TANAI_TYPE_FAT12 ? "FAT12  " : "FAT16  ", sizeof(bpb.fat12_16.filesystem_type), sizeof(bpb.fat12_16.filesystem_type));
            if(error) return error;
            break;
        }
        case TANAI_TYPE_FAT32: return gen_error_attach_backtrace(GEN_ERROR_NOT_IMPLEMENTED, GEN_LINE_NUMBER, "FAT32 BPB writer not implemented");
    }

    *out_bpb = bpb;

    return GEN_NULL;
}
