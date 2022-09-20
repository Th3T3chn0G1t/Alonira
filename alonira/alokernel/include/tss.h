// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#ifndef ALO_KERNEL_TSS_H
#define ALO_KERNEL_TSS_H

#include <gencommon.h>
#include <alocommon.h>

typedef enum {
    ALO_IST_NONE,
    ALO_IST1,
    ALO_IST2,
    ALO_IST3,
    ALO_IST4,
    ALO_IST5,
    ALO_IST6,
    ALO_IST7,

    ALO_IST_COUNT = ALO_IST7
} alo_ist_t;

typedef uintptr_t alo_tss_entry_t;
typedef struct GEN_PACKED {
    uint32_t reserved0;
    alo_tss_entry_t rsp[3];
    alo_tss_entry_t reserved1[2];
    alo_tss_entry_t ist[ALO_IST_COUNT];
    alo_tss_entry_t reserved2[2];
    uint16_t reserved3;
    uint16_t iopb_offset;
} alo_tss_t;

// TODO: I/O Permission Bit Map
// TODO: TSS Interrupt Stack Table for IDT entries `sysenter`

extern alo_tss_t alo_tss;

extern gen_error_t* alo_tss_install(void);

#endif
