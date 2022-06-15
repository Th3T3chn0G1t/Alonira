// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 TTG <prs.ttg+alonira@pm.me>

#include "include/idt.h"

const alo_idt_entry_t alo_idt[256] = {0};
const alo_idt_pointer_t alo_idtr = {sizeof(alo_idt) - 1, alo_idt};

#include "include/isrs.h"

alo_error_t alo_idt_install(void) {
	ALO_FRAME_BEGIN(alo_idt_install);

	iasm(as(sti));

	ALO_ALL_OK;
}
