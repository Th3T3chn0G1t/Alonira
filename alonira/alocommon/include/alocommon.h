// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#ifndef ALO_COMMON_H
#define ALO_COMMON_H

#define ALO_ASM_BLOCK(ops, ...) asm volatile(ops __VA_ARGS__)
#define ALO_ASM(...) #__VA_ARGS__ "\n"

#define ALO_PACKED __attribute__((packed))
#define ALO_USED __attribute__((used))
#define ALO_FORCE_INLINE __attribute__((always_inline)) __attribute__((artificial)) inline
#define ALO_NO_INLINE __attribute__((noinline))

#define ALO_FLAG_ENUM __attribute__((enum_extensibility(closed), flag_enum))

#define ALO_NO_SANITIZE [[clang::disable_sanitizer_instrumentation]]

#endif
