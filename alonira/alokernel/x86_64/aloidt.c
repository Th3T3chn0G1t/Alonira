// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include <gencommon.h>

#include "include/aloidt.h"
#include "include/alotss.h"

alo_idt_entry_t alo_idt[ALO_INTERRUPT_VECTOR_COUNT] = {0};
alo_idt_pointer_t alo_idtr = {sizeof(alo_idt) - 1, alo_idt};

gen_error_t* alo_idt_install(void) {
	GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) alo_idt_install, GEN_FILE_NAME);
	if(error) return error;

    error = alo_interrupts_install_exception_handlers();
	if(error) return error;

    error = alo_interrupts_install_irq_handlers();
    if(error) return error;

	// clang-format off
	GEN_ASM_BLOCK(
        GEN_ASM(lidtq %[idtr])

        GEN_ASM(sti),
    :: [idtr] "m" (alo_idtr) :);
	// clang-format on

    return GEN_NULL;
}
