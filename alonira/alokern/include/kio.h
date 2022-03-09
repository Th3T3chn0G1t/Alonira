// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 TTG <prs.ttg+alonira@pm.me>

#ifndef ALO_KERNEL_IO_H
#define ALO_KERNEL_IO_H

#include <alocom.h>

ALO_DIAGNOSTIC_REGION_BEGIN
#pragma clang diagnostic ignored "-Wlanguage-extension-token"
static __forceinline void alo_port_out_byte(const uint16_t port, const uint8_t value) {
    asm volatile("outb %0, %1" : : "a"(value), "Nd"(port));
}

static __forceinline uint8_t alo_port_in_byte(const uint16_t port) {
    uint8_t ret = 0;
    asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

ALO_DIAGNOSTIC_REGION_END

#endif
