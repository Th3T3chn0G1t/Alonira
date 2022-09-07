// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 TTG <prs.ttg+alonira@pm.me>

#ifndef ALO_KERNEL_TSS_H
#define ALO_KERNEL_TSS_H

#include <alocom.h>

typedef uintptr_t alo_tss_entry_t;
typedef struct __packed {
    uint32_t reserved0;
    alo_tss_entry_t rsp[3];
    alo_tss_entry_t reserved1[2];
    alo_tss_entry_t ist[7];
    alo_tss_entry_t reserved2[2];
    uint16_t reserved3;
    uint16_t iopb_offset;
} alo_tss_t;

extern alo_tss_t alo_tss;

ALO_ERRORABLE alo_tss_install(void);

#endif
