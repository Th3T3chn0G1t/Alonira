// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2023 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include "include/aloarchcommon.h"
#include "include/alocpu.h"

GEN_NORETURN void alo_debug_vm_shutdown_bochs(void) {
    alo_port_out_word(0xB004, 0x2000);
    GEN_UNREACHABLE;
}

GEN_NORETURN void alo_debug_vm_shutdown_qemu(void) {
    alo_port_out_word(0x604, 0x2000);
    GEN_UNREACHABLE;
}
