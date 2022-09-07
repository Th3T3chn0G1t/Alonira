// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 TTG <prs.ttg+alonira@pm.me>

#ifndef ALO_BOOT_H
#define ALO_BOOT_H

#include <gencommon.h>

#if ALO_BOOT_PROTOCOL == ALO_BOOT_PROTOCOL_ULTRA

GEN_PRAGMA(GEN_PRAGMA_DIAGNOSTIC_REGION_BEGIN)
GEN_PRAGMA(GEN_PRAGMA_DIAGNOSTIC_REGION_IGNORE)
#include <ultra_protocol.h>
GEN_PRAGMA(GEN_PRAGMA_DIAGNOSTIC_REGION_END)

#define ALO_BOOT_SIGNATURE __maybe_unused struct ultra_boot_context bootdata , __maybe_unused const unsigned int magic

#endif
#endif
