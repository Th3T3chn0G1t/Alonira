// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#ifndef ALO_KERNEL_EXCEPTIONS_H
#define ALO_KERNEL_EXCEPTIONS_H

#include "interrupts.h"

extern gen_error_t* alo_exceptions_populate_idt(void);

extern void alo_exception_handler_divide_by_zero(void);
extern void alo_exception_handler_debug_trap(void);
extern void alo_exception_handler_nmi(void);
extern void alo_exception_handler_breakpoint(void);
extern void alo_exception_handler_overflow(void);
extern void alo_exception_handler_bound_range_exceeded(void);
extern void alo_exception_handler_invalid_opcode(void);
extern void alo_exception_handler_device_not_avilable(void);
extern void alo_exception_handler_double_fault(void);
extern void alo_exception_handler_coprocessor_segment_overrun(void);
extern void alo_exception_handler_invalid_tss(void);
extern void alo_exception_handler_segment_not_present(void);
extern void alo_exception_handler_stack_segment_fault(void);
extern void alo_exception_handler_general_protection_fault(void);
extern void alo_exception_handler_page_fault(void);
extern void alo_exception_handler_reserved0(void);
extern void alo_exception_handler_x87_floating_point(void);
extern void alo_exception_handler_alignment_check(void);
extern void alo_exception_handler_machine_check(void);
extern void alo_exception_handler_simd_floating_point(void);
extern void alo_exception_handler_virtualization(void);
extern void alo_exception_handler_control_protection(void);
extern void alo_exception_handler_reserved1(void);
extern void alo_exception_handler_reserved2(void);
extern void alo_exception_handler_reserved3(void);
extern void alo_exception_handler_reserved4(void);
extern void alo_exception_handler_reserved5(void);
extern void alo_exception_handler_reserved6(void);
extern void alo_exception_handler_hypervisor_injection(void);
extern void alo_exception_handler_vmm_communication(void);
extern void alo_exception_handler_security(void);
extern void alo_exception_handler_reserved7(void);

#endif
