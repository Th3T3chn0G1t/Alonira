// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2023 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#ifndef TANAI_FILES_H
#define TANAI_FILES_H

#include <gencommon.h>

typedef enum GEN_FLAG_ENUM {
    TANAI_FILE_ATTRIBUTE_NONE      = 0,
    TANAI_FILE_ATTRIBUTE_READ_ONLY = 1 << 0,
    TANAI_FILE_ATTRIBUTE_HIDDEN    = 1 << 1,
    TANAI_FILE_ATTRIBUTE_SYSTEM    = 1 << 2,
    TANAI_FILE_ATTRIBUTE_VOLUME_ID = 1 << 3,
    TANAI_FILE_ATTRIBUTE_DIRECTORY = 1 << 4,
    TANAI_FILE_ATTRIBUTE_ARCHIVE   = 1 << 5,

    TANAI_FILE_ATTRIBUTE_LONG_NAME = TANAI_FILE_ATTRIBUTE_READ_ONLY | TANAI_FILE_ATTRIBUTE_HIDDEN | TANAI_FILE_ATTRIBUTE_SYSTEM | TANAI_FILE_ATTRIBUTE_VOLUME_ID
} file_attributes_t;

typedef union {
    struct {
        char name[8];
        char extension[3];
    };
    char fullname[11];
} tanai_filename_t;

typedef enum {
    FAT_MONTH_JANUARY = 1,
    FAT_MONTH_FEBRUARY,
    FAT_MONTH_MARCH,
    FAT_MONTH_APRIL,
    FAT_MONTH_MAY,
    FAT_MONTH_JUNE,
    FAT_MONTH_JULY,
    FAT_MONTH_AUGUST,
    FAT_MONTH_SEPTEMBER,
    FAT_MONTH_OCTOBER,
    FAT_MONTH_NOVEMBER,
    FAT_MONTH_DECEMBER
} tanai_date_month_t;

typedef struct GEN_PACKED {
    gen_uint8_t day : 5;
    tanai_date_month_t month : 4;
    gen_uint8_t years_since_1980 : 7;
} tanai_date_t;

typedef struct GEN_PACKED {
    gen_uint8_t duoseconds : 5;
    gen_uint8_t minutes : 6;
    gen_uint8_t hours : 5;
} tanai_time_t;

typedef struct {
    gen_uint8_t duocentiseconds;
    tanai_time_t time;
    tanai_date_t date;
} tanai_timestamp_t;

typedef struct GEN_PACKED {
    tanai_filename_t name;

    struct GEN_PACKED {
        file_attributes_t attributes : 6;
        gen_uint8_t reserved0 : 2;
    };
    gen_uint8_t reserved1;

    tanai_timestamp_t creation_time;

    tanai_date_t access_date;

    gen_uint16_t file_cluster_high;

    tanai_time_t write_time;
    tanai_date_t write_date;

    gen_uint16_t file_cluster_low;

    gen_uint32_t file_size;
} tanai_directory_entry_t;

#define TANAI_FATH_FILENAME_PAD 0x20
#define TANAI_FATH_FILENAME_EMPTY 0xE5

#endif
