// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 TTG <prs.ttg+alonira@pm.me>

#ifndef ALO_BOOT_H
#define ALO_BOOT_H

#include <alocom.h>

#if ALO_BOOT_PROTOCOL == ALO_BOOT_PROTOCOL_ULTRA

ALO_DIAGNOSTIC_REGION_BEGIN
ALO_DIAGNOSTIC_IGNORE_ALL
#include <ultra_protocol.h>
ALO_DIAGNOSTIC_REGION_END

#define ALO_BOOT_SIGNATURE __maybe_unused struct ultra_boot_context bootdata , __maybe_unused const unsigned int magic

#endif
#endif
