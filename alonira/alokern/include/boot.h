// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 TTG <prs.ttg+alonira@pm.me>

#ifndef ALO_BOOT_H
#define ALO_BOOT_H

#include <alocom.h>

#if ALO_BOOT_PROTOCOL == ALO_BOOT_PROTOCOL_STIVALE

ALO_DIAGNOSTIC_REGION_BEGIN
ALO_DIAGNOSTIC_IGNORE_ALL
#include <stivale2.h>
ALO_DIAGNOSTIC_REGION_END

static unsigned char stack[8192];

ALO_DIAGNOSTIC_REGION_BEGIN
#pragma clang diagnostic ignored "-Wgnu-binary-literal"
__attribute__((section(".stivale2hdr"), used)) static struct stivale2_header stivale_header = {
	.entry_point = 0,
	.stack = (unsigned long) stack + sizeof(stack),
	.flags = 0b00011110,
	.tags = 0
};
ALO_DIAGNOSTIC_REGION_END

#define ALO_BOOT_SIGNATURE __maybe_unused const struct stivale2_struct bootdata, __maybe_unused const unsigned int magic

#elif ALO_BOOT_PROTOCOL == ALO_BOOT_PROTOCOL_ULTRA

ALO_DIAGNOSTIC_REGION_BEGIN
ALO_DIAGNOSTIC_IGNORE_ALL
#include <ultra_protocol.h>
ALO_DIAGNOSTIC_REGION_END

#define ALO_BOOT_SIGNATURE __maybe_unused struct ultra_boot_context;

#endif
#endif
