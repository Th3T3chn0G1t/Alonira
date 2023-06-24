// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2023 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include <gencommon.h>
#include <genbackends.h>

#include "include/alocpu.h"

GEN_USED void gen_alonira_terminal_write(const char* const restrict s) {
    for(gen_size_t i = 0; s[i]; ++i) {
        alo_port_out_byte(0xE9, (gen_uint8_t) s[i]);
    }
    alo_port_out_byte(0xE9, (gen_uint8_t) '\n');
}
