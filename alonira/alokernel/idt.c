// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include "include/idt.h"

const alo_idt_entry_t alo_idt[256] = {0};
const alo_idt_pointer_t alo_idtr = {sizeof(alo_idt) - 1, alo_idt};

#include "include/isrs.h"

gen_error_t* alo_idt_install(void) {
	gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) alo_idt_install, GEN_FILE_NAME);
	if(error) return error;

	ALO_ASM_BLOCK(ALO_ASM(sti));

	return NULL;
}
