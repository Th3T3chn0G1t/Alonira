// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2023 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#ifndef ALO_KERNEL_X86_64_ARCH_COMMON_H
#define ALO_KERNEL_X86_64_ARCH_COMMON_H

#include <gencommon.h>

GEN_NORETURN void alo_debug_vm_shutdown_bochs(void);
GEN_NORETURN void alo_debug_vm_shutdown_qemu(void);

#endif
