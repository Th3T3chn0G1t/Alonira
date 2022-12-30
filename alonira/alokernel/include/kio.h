// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#ifndef ALO_KERNEL_IO_H
#define ALO_KERNEL_IO_H

#include <gencommon.h>


static GEN_FORCE_INLINE void alo_port_out_byte(const gen_uint16_t port, const gen_uint8_t value) {
    GEN_ASM_BLOCK(GEN_ASM(outb %[value], %[port]), :: [value]"a"(value), [port]"Nd"(port) :);
}

static GEN_FORCE_INLINE void alo_port_out_word(const gen_uint16_t port, const gen_uint16_t value) {
    GEN_ASM_BLOCK(GEN_ASM(outw %[value], %[port]), :: [value]"a"(value), [port]"Nd"(port) :);
}

static GEN_FORCE_INLINE gen_uint8_t alo_port_in_byte(const gen_uint16_t port) {
    gen_uint8_t out_value = 0;
    GEN_ASM_BLOCK(GEN_ASM(inb %[port], %[out_value]), : [out_value]"=a"(out_value) : [port]"Nd"(port) :);
    return out_value;
}

#endif
