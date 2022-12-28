// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#ifndef ALO_BOOT_H
#define ALO_BOOT_H

#include <gencommon.h>

#if ALO_BOOT_PROTOCOL == ALO_BOOT_PROTOCOL_ULTRA

GEN_PRAGMA(GEN_PRAGMA_DIAGNOSTIC_REGION_BEGIN)
GEN_PRAGMA(GEN_PRAGMA_DIAGNOSTIC_REGION_IGNORE("-Weverything"))
#include <ultra_protocol.h>
GEN_PRAGMA(GEN_PRAGMA_DIAGNOSTIC_REGION_END)

#define ALO_BOOT_SIGNATURE GEN_MAYBE_UNUSED struct ultra_boot_context boot_data, GEN_MAYBE_UNUSED const unsigned int magic
#define ALO_BOOT_PASSTHROUGH boot_data, magic

#endif

#endif
