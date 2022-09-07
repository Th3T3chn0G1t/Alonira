// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 TTG <prs.ttg+alonira@pm.me>

#include "include/kdiagnostic.h"
#include "include/vga.h"

#include <alocom.h>
#include <alomemory.h>
#include <alostring.h>

static const char alo_internal_panic_message_head[] = "ALONIRA KERNEL PANIC";

static noreturn void alo_internal_panic_impl(const alo_error_t error, const char* const restrict context, alo_registers_t* registers) {
	ALO_FRAME_BEGIN(alo_internal_panic_impl);

	alogf(FATAL, "Kernel Panic: %s (%s) - %s", alo_error_name(error), alo_error_description(error), context);

	(void) alo_memory_set(ALO_VGA_ADDRESS, ALO_VGA_WIDTH * ALO_VGA_HEIGHT * sizeof(ALO_VGA_ADDRESS[0]), 0);

	// We can't check errors here - let's just hope we didn't mess up
	(void) alo_vga_put_string_at_colored(alo_internal_panic_message_head, sizeof(alo_internal_panic_message_head) - 1, ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_RED), ALO_VGA_COLOR_LIGHT(ALO_VGA_COLOR_WHITE), ALO_VGA_WIDTH / 2 - (sizeof(alo_internal_panic_message_head) - 1) / 2, 5);

	const char* error_name = alo_error_name(error);
	size_t error_name_length = 0;
	(void) alo_string_length(error_name, ALO_STRING_NO_BOUND, ALO_STRING_NO_BOUND, &error_name_length);
	(void) alo_vga_put_string_at_colored(error_name, error_name_length, ALO_VGA_COLOR_LIGHT(ALO_VGA_COLOR_WHITE), ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_BLACK), ALO_VGA_WIDTH / 2 - (alo_vga_dimension_t) error_name_length / 2, 7);

	const char* error_description = alo_error_description(error);
	size_t error_description_length = 0;
	(void) alo_string_length(error_description, ALO_STRING_NO_BOUND, ALO_STRING_NO_BOUND, &error_description_length);
	(void) alo_vga_put_string_at_colored(error_description, error_description_length, ALO_VGA_COLOR_LIGHT(ALO_VGA_COLOR_WHITE), ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_BLACK), ALO_VGA_WIDTH / 2 - (alo_vga_dimension_t) error_description_length / 2, 8);

	size_t context_length = 0;
	(void) alo_string_length(context, ALO_STRING_NO_BOUND, ALO_STRING_NO_BOUND, &context_length);
	(void) alo_vga_put_string_at_colored(context, context_length, ALO_VGA_COLOR_LIGHT(ALO_VGA_COLOR_WHITE), ALO_VGA_COLOR_DARK(ALO_VGA_COLOR_BLACK), ALO_VGA_WIDTH / 2 - (alo_vga_dimension_t) context_length / 2, 10);

	if(registers) {
		alogf(NOTE, "Registers at panic site:\n\trax %p rbx %p rcx %p rdx %p\n\trsi %p rdi %p\n\trbp %p rsp %p\n\tr8 %p r9 %p r10 %p r11 %p r12 %p r13 %p r14 %p r15 %p\n\trip %p rflags %p", registers->rax, registers->rbx, registers->rcx, registers->rdx, registers->rsi, registers->rdi, registers->rbp, registers->rsp, registers->r8, registers->r9, registers->r10, registers->r11, registers->r12, registers->r13, registers->r14, registers->r15, registers->rip, registers->rfl);
		alogf(NOTE, "Flags at panic site:\n\tcarry %i parity %i adjust %i zero %i\n\tsign %i trap %i interrupt %i direction %i\n\toverflow %i DPL %i nested task %i resume %i\n\tv8086 %i alignment check %i vinterrupt %i vinterrupt pending %i\n\tcpuid usable %i", registers->rflags.carry, registers->rflags.parity, registers->rflags.adjust, registers->rflags.zero, registers->rflags.sign, registers->rflags.trap, registers->rflags.interrupt, registers->rflags.direction, registers->rflags.overflow, registers->rflags.privilige, registers->rflags.nested_task, registers->rflags.resume, registers->rflags.v8086, registers->rflags.alignment_check, registers->rflags.vinterrupt, registers->rflags.vinterrupt_pending, registers->rflags.cpuid_usable);
	}

	alo_hang();
}

void alo_panic(const alo_error_t error, const char* const restrict context) {
	ALO_FRAME_BEGIN(alo_panic);

	alo_internal_panic_impl(error, context, NULL);
}

void alo_panic_with_registers(const alo_error_t error, const char* const restrict context, alo_registers_t registers) {
	ALO_FRAME_BEGIN(alo_panic_with_registers);

	alo_internal_panic_impl(error, context, &registers);
}
