// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 TTG <prs.ttg+alonira@pm.me>

#include "include/alocom.h"
#include "include/alog.h"

alo_tooling_stack_t alo_tooling_call_stack;

void alo_tooling_stack_push(const char* const restrict frame, const unsigned long address, const char* const restrict file) {
	alo_tooling_call_stack.functions[alo_tooling_call_stack.next] = frame;
	alo_tooling_call_stack.addresses[alo_tooling_call_stack.next] = address;
	alo_tooling_call_stack.files[alo_tooling_call_stack.next] = file;
	++alo_tooling_call_stack.next;
}

void alo_tooling_stack_pop(void) {
	--alo_tooling_call_stack.next;
}

void alo_internal_tooling_frame_scope_end(__unused const char* const restrict passthrough) {
	alo_tooling_stack_pop();
}

void alo_tooling_print_backtrace(void) {
	for(unsigned long i = 0; i < alo_tooling_call_stack.next; ++i) {
		// alog(TRACE, "frame #%zu: 0x%p %s() %s", i, (void*) alo_tooling_call_stack.addresses[alo_tooling_call_stack.next - (i + 1)], alo_tooling_call_stack.functions[alo_tooling_call_stack.next - (i + 1)], alo_tooling_call_stack.files[alo_tooling_call_stack.next - (i + 1)]);
		alog(TRACE, "frame #%zu: 0x%p %s() %s");
	}
}
