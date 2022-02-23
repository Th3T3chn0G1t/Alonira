// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 TTG <prs.ttg+alonira@pm.me>

#ifndef ALO_TOOLED_H
#define ALO_TOOLED_H

#ifndef ALO_TOOLING_DEPTH
#define ALO_TOOLING_DEPTH 64
#endif

typedef struct {
	size_t next;
	const char* functions[ALO_TOOLING_DEPTH];
	size_t addresses[ALO_TOOLING_DEPTH];
	const char* files[ALO_TOOLING_DEPTH];
} alo_tooling_stack_t;

extern alo_tooling_stack_t alo_tooling_call_stack;

extern void alo_tooling_stack_push(const char* const restrict frame, const size_t address, const char* const restrict file);
extern void alo_tooling_stack_pop(void);
extern void alo_internal_tooling_frame_scope_end(const char* const restrict passthrough);
extern void alo_tooling_print_backtrace(void);

#define atrace alo_tooling_print_backtrace()

#define ALO_FRAME_BEGIN(function) \
	__attribute__((cleanup(alo_internal_tooling_frame_scope_end))) __unused const char alo_internal_frame_scope_tmpvar = '\0'; \
	alo_tooling_stack_push(__func__, (size_t) function, __FILE__)

#endif
