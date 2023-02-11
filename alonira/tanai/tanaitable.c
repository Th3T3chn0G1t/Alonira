// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2023 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include "include/tanaitable.h"

gen_error_t* tanai_fat_write(const tanai_fat_type_t type, const tanai_bpb_t* const restrict bpb, tanai_fat_t* const restrict fat, const gen_size_t index, const gen_uint32_t value) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) tanai_fat_write, GEN_FILE_NAME);
    if(error) return error;

    if(!bpb) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`bpb` was GEN_NULL");
    if(!fat) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`fat` was GEN_NULL");

    // TODO: Check fat bounds from BPB

    switch(type) {
        case TANAI_TYPE_FAT12: {
            gen_uint16_t entry = (gen_uint16_t) value;
            gen_size_t offset = index + (index / 2);
            gen_uint8_t* bytes = (gen_uint8_t*) fat->fat12;
            if(index % 2) {
                entry <<= 4;
                (*(gen_uint16_t*) &bytes[offset]) &= 0x000F;
            }
            else {
                entry &= 0x0FFF;
                (*(gen_uint16_t*) &bytes[offset]) &= 0xF000;
            }
            (*(gen_uint16_t*) &bytes[offset]) |= entry;
            break;
        }
        case TANAI_TYPE_FAT16: {
            fat->fat16[index] = (gen_uint16_t) value;
            break;
        }
        case TANAI_TYPE_FAT32: {
            fat->fat32[index] = value;
            break;
        }
    }

    return GEN_NULL;
}

gen_error_t* tanai_fat_init(const tanai_fat_type_t type, const tanai_bpb_t* const restrict bpb, tanai_fat_t* const restrict fat) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) tanai_fat_init, GEN_FILE_NAME);
    if(error) return error;

    if(!bpb) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`bpb` was GEN_NULL");
    if(!fat) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`fat` was GEN_NULL");

    error = tanai_fat_write(type, bpb, fat, 0, TANAI_FAT_ENTRY_EOF(type));
    if(error) return error;

    error = tanai_fat_write(type, bpb, fat, 1, *(const gen_uint8_t*) &bpb->media_type);
    if(error) return error;

    return GEN_NULL;
}
