// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include "include/idt.h"

#include "include/exceptions.h"
#include "include/isrs.h"

alo_idt_entry_t alo_idt[ALO_INTERRUPT_VECTOR_COUNT] = {0};
alo_idt_pointer_t alo_idtr = {sizeof(alo_idt) - 1, alo_idt};

gen_error_t* alo_idt_install(void) {
	GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) alo_idt_install, GEN_FILE_NAME);
	if(error) return error;

    error = alo_exceptions_populate_idt();
	if(error) return error;

    // error = alo_isrs_populate_idt();
	// if(error) return error;

	// clang-format off
	ALO_ASM_BLOCK(
        ALO_ASM(movq %[idtr], %%rax)
        ALO_ASM(lidtq (%%rax))

        ALO_ASM(sti),
    :: [idtr]"p"(&alo_idtr) : "rax");
	// clang-format on

	return NULL;
}
