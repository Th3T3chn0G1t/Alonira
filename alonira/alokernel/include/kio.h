// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#ifndef ALO_KERNEL_IO_H
#define ALO_KERNEL_IO_H

#include <gencommon.h>
#include <alocommon.h>

static ALO_FORCE_INLINE void alo_port_out_byte(const uint16_t port, const uint8_t value) {
    ALO_ASM_BLOCK(ALO_ASM(outb %[value], %[port]), :: [value]"a"(value), [port]"Nd"(port) :);
}

static ALO_FORCE_INLINE uint8_t alo_port_in_byte(const uint16_t port) {
    uint8_t out_value = 0;
    ALO_ASM_BLOCK(ALO_ASM(inb %[port], %[out_value]), : [out_value]"=a"(out_value) : [port]"Nd"(port) :);
    return out_value;
}

#endif
