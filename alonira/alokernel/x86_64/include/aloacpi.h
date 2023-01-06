// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2023 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#ifndef ALO_KERNEL_ACPI_H
#define ALO_KERNEL_ACPI_H

#include <gencommon.h>

typedef struct GEN_PACKED {
    char signature[8];
    gen_uint8_t checksum;
    char oem_id[6];
    gen_uint8_t revision;
    gen_uint32_t rsdt_physical_address;
    gen_uint32_t length;
    gen_uintptr_t xsdt_physical_address;
    gen_uint8_t extended_checksum;
    gen_uint8_t reserved[3];
} alo_rdsp_descriptor_t;

#endif
