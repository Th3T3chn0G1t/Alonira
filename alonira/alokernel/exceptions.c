// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include <genlog.h>

#include "include/exceptions.h"

#include "include/kdiagnostic.h"
#include "include/idt.h"
#include "include/tss.h"
#include "include/vga.h"

static ALO_INTERRUPT_HANDLER_CALLABLE_ATTRIBUTES GEN_USED void alo_exception_handler_common(const alo_interrupt_frame_t* frame) {
    // TODO: The issue with this was wrong widths being passed to uz - fix!
    gen_log_formatted(GEN_LOG_LEVEL_DEBUG, "alonira-exception", "Exception %uz occurred at %p - error code: %uz || ", frame->vector, (void*) frame->rip, frame->error_code);
    if(frame->vector) alo_hang();
}

gen_error_t* alo_exceptions_populate_idt(void) {
	GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) alo_exceptions_populate_idt, GEN_FILE_NAME);
	if(error) return error;

    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_DIVIDE_BY_ZERO] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_exception_handler_divide_by_zero, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_DEBUG_TRAP] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_exception_handler_debug_trap, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_NMI] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_exception_handler_nmi, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_BREAKPOINT] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_exception_handler_breakpoint, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_OVERFLOW] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_exception_handler_overflow, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_BOUND_RANGE_EXCEEDED] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_exception_handler_bound_range_exceeded, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_INVALID_OPCODE] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_exception_handler_invalid_opcode, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_DEVICE_NOT_AVILABLE] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_exception_handler_device_not_avilable, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_DOUBLE_FAULT] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_exception_handler_double_fault, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_COPROCESSOR_SEGMENT_OVERRUN] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_exception_handler_coprocessor_segment_overrun, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_INVALID_TSS] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_exception_handler_invalid_tss, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_SEGMENT_NOT_PRESENT] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_exception_handler_segment_not_present, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_STACK_SEGMENT_FAULT] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_exception_handler_stack_segment_fault, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_GENERAL_PROTECTION_FAULT] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_exception_handler_general_protection_fault, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_PAGE_FAULT] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_exception_handler_page_fault, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED0] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_exception_handler_reserved0, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_X87_FLOATING_POINT] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_exception_handler_x87_floating_point, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_ALIGNMENT_CHECK] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_exception_handler_alignment_check, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_MACHINE_CHECK] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_exception_handler_machine_check, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_SIMD_FLOATING_POINT] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_exception_handler_simd_floating_point, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_VIRTUALIZATION] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_exception_handler_virtualization, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_CONTROL_PROTECTION] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_exception_handler_control_protection, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED1] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_exception_handler_reserved1, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED2] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_exception_handler_reserved2, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED3] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_exception_handler_reserved3, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED4] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_exception_handler_reserved4, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED5] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_exception_handler_reserved5, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED6] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_exception_handler_reserved6, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_HYPERVISOR_INJECTION] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_exception_handler_hypervisor_injection, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_VMM_COMMUNICATION] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_exception_handler_vmm_communication, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_SECURITY] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_exception_handler_security, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED7] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_exception_handler_reserved7, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);

    return GEN_NULL;
}

/*
    alo_register_t rip;
    alo_segment_selector_t cs;
    size_t pad : 48;
    union {
        alo_flags_t rflags;
        alo_register_t rfl;
    };
    alo_register_t rsp;
*/


// clang-format off
static GEN_USED void alo_internal_interrupt_container(void) {
// Some of these handlers are for reserved vectors that should never actually
// be triggered but it's easier to just have the entire list here.

GEN_ASM_BLOCK(
    GEN_ASM(.extern alo_exception_handler_common)

    GEN_ASM(.global alo_exception_handler_divide_by_zero)
    GEN_ASM(alo_exception_handler_divide_by_zero:)
        GEN_ASM(pushq 0)

        GEN_ASM(pushq 32(%%rsp))

        GEN_ASM(pushq 24(%%rsp))

        GEN_ASM(pushq %%r15)
        GEN_ASM(pushq %%r14)
        GEN_ASM(pushq %%r13)
        GEN_ASM(pushq %%r12)
        GEN_ASM(pushq %%r11)
        GEN_ASM(pushq %%r10)
        GEN_ASM(pushq %%r9)
        GEN_ASM(pushq %%r8)

        GEN_ASM(pushq 120(%%rsp))
        GEN_ASM(pushq %%rbp)

        GEN_ASM(pushq %%rdi)
        GEN_ASM(pushq %%rsi)

        GEN_ASM(pushq %%rdx)
        GEN_ASM(pushq %%rcx)
        GEN_ASM(pushq %%rbx)
        GEN_ASM(pushq %%rax)

        GEN_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_DIVIDE_BY_ZERO])

        GEN_ASM(movq %%rsp, %%rdi)
        GEN_ASM(cld)
        GEN_ASM(callq alo_exception_handler_common)
        
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%rax)
        GEN_ASM(popq %%rbx)
        GEN_ASM(popq %%rcx)
        GEN_ASM(popq %%rdx)

        GEN_ASM(popq %%rsi)
        GEN_ASM(popq %%rdi)

        GEN_ASM(popq %%rbp)
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%r8)
        GEN_ASM(popq %%r9)
        GEN_ASM(popq %%r10)
        GEN_ASM(popq %%r11)
        GEN_ASM(popq %%r12)
        GEN_ASM(popq %%r13)
        GEN_ASM(popq %%r14)
        GEN_ASM(popq %%r15)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(iretq)

    GEN_ASM(.global alo_exception_handler_debug_trap)
    GEN_ASM(alo_exception_handler_debug_trap:)
        GEN_ASM(pushq 0)

        GEN_ASM(pushq 32(%%rsp))

        GEN_ASM(pushq 24(%%rsp))

        GEN_ASM(pushq %%r15)
        GEN_ASM(pushq %%r14)
        GEN_ASM(pushq %%r13)
        GEN_ASM(pushq %%r12)
        GEN_ASM(pushq %%r11)
        GEN_ASM(pushq %%r10)
        GEN_ASM(pushq %%r9)
        GEN_ASM(pushq %%r8)

        GEN_ASM(pushq 120(%%rsp))
        GEN_ASM(pushq %%rbp)

        GEN_ASM(pushq %%rdi)
        GEN_ASM(pushq %%rsi)

        GEN_ASM(pushq %%rdx)
        GEN_ASM(pushq %%rcx)
        GEN_ASM(pushq %%rbx)
        GEN_ASM(pushq %%rax)

        GEN_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_DEBUG_TRAP])

        GEN_ASM(movq %%rsp, %%rdi)
        GEN_ASM(cld)
        GEN_ASM(callq alo_exception_handler_common)
        
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%rax)
        GEN_ASM(popq %%rbx)
        GEN_ASM(popq %%rcx)
        GEN_ASM(popq %%rdx)

        GEN_ASM(popq %%rsi)
        GEN_ASM(popq %%rdi)

        GEN_ASM(popq %%rbp)
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%r8)
        GEN_ASM(popq %%r9)
        GEN_ASM(popq %%r10)
        GEN_ASM(popq %%r11)
        GEN_ASM(popq %%r12)
        GEN_ASM(popq %%r13)
        GEN_ASM(popq %%r14)
        GEN_ASM(popq %%r15)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)
        
        GEN_ASM(iretq)

    GEN_ASM(.global alo_exception_handler_nmi)
    GEN_ASM(alo_exception_handler_nmi:)
        GEN_ASM(pushq 0)

        GEN_ASM(pushq 32(%%rsp))

        GEN_ASM(pushq 24(%%rsp))

        GEN_ASM(pushq %%r15)
        GEN_ASM(pushq %%r14)
        GEN_ASM(pushq %%r13)
        GEN_ASM(pushq %%r12)
        GEN_ASM(pushq %%r11)
        GEN_ASM(pushq %%r10)
        GEN_ASM(pushq %%r9)
        GEN_ASM(pushq %%r8)

        GEN_ASM(pushq 120(%%rsp))
        GEN_ASM(pushq %%rbp)

        GEN_ASM(pushq %%rdi)
        GEN_ASM(pushq %%rsi)

        GEN_ASM(pushq %%rdx)
        GEN_ASM(pushq %%rcx)
        GEN_ASM(pushq %%rbx)
        GEN_ASM(pushq %%rax)

        GEN_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_NMI])

        GEN_ASM(movq %%rsp, %%rdi)
        GEN_ASM(cld)
        GEN_ASM(callq alo_exception_handler_common)
        
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%rax)
        GEN_ASM(popq %%rbx)
        GEN_ASM(popq %%rcx)
        GEN_ASM(popq %%rdx)

        GEN_ASM(popq %%rsi)
        GEN_ASM(popq %%rdi)

        GEN_ASM(popq %%rbp)
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%r8)
        GEN_ASM(popq %%r9)
        GEN_ASM(popq %%r10)
        GEN_ASM(popq %%r11)
        GEN_ASM(popq %%r12)
        GEN_ASM(popq %%r13)
        GEN_ASM(popq %%r14)
        GEN_ASM(popq %%r15)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)
        
        GEN_ASM(iretq)

    GEN_ASM(.global alo_exception_handler_breakpoint)
    GEN_ASM(alo_exception_handler_breakpoint:)
        GEN_ASM(pushq 0)

        GEN_ASM(pushq 32(%%rsp))

        GEN_ASM(pushq 24(%%rsp))

        GEN_ASM(pushq %%r15)
        GEN_ASM(pushq %%r14)
        GEN_ASM(pushq %%r13)
        GEN_ASM(pushq %%r12)
        GEN_ASM(pushq %%r11)
        GEN_ASM(pushq %%r10)
        GEN_ASM(pushq %%r9)
        GEN_ASM(pushq %%r8)

        GEN_ASM(pushq 120(%%rsp))
        GEN_ASM(pushq %%rbp)

        GEN_ASM(pushq %%rdi)
        GEN_ASM(pushq %%rsi)

        GEN_ASM(pushq %%rdx)
        GEN_ASM(pushq %%rcx)
        GEN_ASM(pushq %%rbx)
        GEN_ASM(pushq %%rax)

        GEN_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_BREAKPOINT])
        
        GEN_ASM(movq %%rsp, %%rdi)
        GEN_ASM(cld)
        GEN_ASM(callq alo_exception_handler_common)
        
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%rax)
        GEN_ASM(popq %%rbx)
        GEN_ASM(popq %%rcx)
        GEN_ASM(popq %%rdx)

        GEN_ASM(popq %%rsi)
        GEN_ASM(popq %%rdi)

        GEN_ASM(popq %%rbp)
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%r8)
        GEN_ASM(popq %%r9)
        GEN_ASM(popq %%r10)
        GEN_ASM(popq %%r11)
        GEN_ASM(popq %%r12)
        GEN_ASM(popq %%r13)
        GEN_ASM(popq %%r14)
        GEN_ASM(popq %%r15)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)
        
        GEN_ASM(iretq)

    GEN_ASM(.global alo_exception_handler_overflow)
    GEN_ASM(alo_exception_handler_overflow:)
        GEN_ASM(pushq 0)

        GEN_ASM(pushq 32(%%rsp))

        GEN_ASM(pushq 24(%%rsp))

        GEN_ASM(pushq %%r15)
        GEN_ASM(pushq %%r14)
        GEN_ASM(pushq %%r13)
        GEN_ASM(pushq %%r12)
        GEN_ASM(pushq %%r11)
        GEN_ASM(pushq %%r10)
        GEN_ASM(pushq %%r9)
        GEN_ASM(pushq %%r8)

        GEN_ASM(pushq 120(%%rsp))
        GEN_ASM(pushq %%rbp)

        GEN_ASM(pushq %%rdi)
        GEN_ASM(pushq %%rsi)

        GEN_ASM(pushq %%rdx)
        GEN_ASM(pushq %%rcx)
        GEN_ASM(pushq %%rbx)
        GEN_ASM(pushq %%rax)

        GEN_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_OVERFLOW])
        
        GEN_ASM(movq %%rsp, %%rdi)
        GEN_ASM(cld)
        GEN_ASM(callq alo_exception_handler_common)
        
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%rax)
        GEN_ASM(popq %%rbx)
        GEN_ASM(popq %%rcx)
        GEN_ASM(popq %%rdx)

        GEN_ASM(popq %%rsi)
        GEN_ASM(popq %%rdi)

        GEN_ASM(popq %%rbp)
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%r8)
        GEN_ASM(popq %%r9)
        GEN_ASM(popq %%r10)
        GEN_ASM(popq %%r11)
        GEN_ASM(popq %%r12)
        GEN_ASM(popq %%r13)
        GEN_ASM(popq %%r14)
        GEN_ASM(popq %%r15)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)
        
        GEN_ASM(iretq)

    GEN_ASM(.global alo_exception_handler_bound_range_exceeded)
    GEN_ASM(alo_exception_handler_bound_range_exceeded:)
        GEN_ASM(pushq 0)

        GEN_ASM(pushq 32(%%rsp))

        GEN_ASM(pushq 24(%%rsp))

        GEN_ASM(pushq %%r15)
        GEN_ASM(pushq %%r14)
        GEN_ASM(pushq %%r13)
        GEN_ASM(pushq %%r12)
        GEN_ASM(pushq %%r11)
        GEN_ASM(pushq %%r10)
        GEN_ASM(pushq %%r9)
        GEN_ASM(pushq %%r8)

        GEN_ASM(pushq 120(%%rsp))
        GEN_ASM(pushq %%rbp)

        GEN_ASM(pushq %%rdi)
        GEN_ASM(pushq %%rsi)

        GEN_ASM(pushq %%rdx)
        GEN_ASM(pushq %%rcx)
        GEN_ASM(pushq %%rbx)
        GEN_ASM(pushq %%rax)

        GEN_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_BOUND_RANGE_EXCEEDED])
        
        GEN_ASM(movq %%rsp, %%rdi)
        GEN_ASM(cld)
        GEN_ASM(callq alo_exception_handler_common)
        
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%rax)
        GEN_ASM(popq %%rbx)
        GEN_ASM(popq %%rcx)
        GEN_ASM(popq %%rdx)

        GEN_ASM(popq %%rsi)
        GEN_ASM(popq %%rdi)

        GEN_ASM(popq %%rbp)
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%r8)
        GEN_ASM(popq %%r9)
        GEN_ASM(popq %%r10)
        GEN_ASM(popq %%r11)
        GEN_ASM(popq %%r12)
        GEN_ASM(popq %%r13)
        GEN_ASM(popq %%r14)
        GEN_ASM(popq %%r15)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)
        
        GEN_ASM(iretq)

    GEN_ASM(.global alo_exception_handler_invalid_opcode)
    GEN_ASM(alo_exception_handler_invalid_opcode:)
        GEN_ASM(pushq 0)

        GEN_ASM(pushq 32(%%rsp))

        GEN_ASM(pushq 24(%%rsp))

        GEN_ASM(pushq %%r15)
        GEN_ASM(pushq %%r14)
        GEN_ASM(pushq %%r13)
        GEN_ASM(pushq %%r12)
        GEN_ASM(pushq %%r11)
        GEN_ASM(pushq %%r10)
        GEN_ASM(pushq %%r9)
        GEN_ASM(pushq %%r8)

        GEN_ASM(pushq 120(%%rsp))
        GEN_ASM(pushq %%rbp)

        GEN_ASM(pushq %%rdi)
        GEN_ASM(pushq %%rsi)

        GEN_ASM(pushq %%rdx)
        GEN_ASM(pushq %%rcx)
        GEN_ASM(pushq %%rbx)
        GEN_ASM(pushq %%rax)

        GEN_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_INVALID_OPCODE])
        
        GEN_ASM(movq %%rsp, %%rdi)
        GEN_ASM(cld)
        GEN_ASM(callq alo_exception_handler_common)
        
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%rax)
        GEN_ASM(popq %%rbx)
        GEN_ASM(popq %%rcx)
        GEN_ASM(popq %%rdx)

        GEN_ASM(popq %%rsi)
        GEN_ASM(popq %%rdi)

        GEN_ASM(popq %%rbp)
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%r8)
        GEN_ASM(popq %%r9)
        GEN_ASM(popq %%r10)
        GEN_ASM(popq %%r11)
        GEN_ASM(popq %%r12)
        GEN_ASM(popq %%r13)
        GEN_ASM(popq %%r14)
        GEN_ASM(popq %%r15)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)
        
        GEN_ASM(iretq)

    GEN_ASM(.global alo_exception_handler_device_not_avilable)
    GEN_ASM(alo_exception_handler_device_not_avilable:)
        GEN_ASM(pushq 0)

        GEN_ASM(pushq 32(%%rsp))

        GEN_ASM(pushq 24(%%rsp))

        GEN_ASM(pushq %%r15)
        GEN_ASM(pushq %%r14)
        GEN_ASM(pushq %%r13)
        GEN_ASM(pushq %%r12)
        GEN_ASM(pushq %%r11)
        GEN_ASM(pushq %%r10)
        GEN_ASM(pushq %%r9)
        GEN_ASM(pushq %%r8)

        GEN_ASM(pushq 120(%%rsp))
        GEN_ASM(pushq %%rbp)

        GEN_ASM(pushq %%rdi)
        GEN_ASM(pushq %%rsi)

        GEN_ASM(pushq %%rdx)
        GEN_ASM(pushq %%rcx)
        GEN_ASM(pushq %%rbx)
        GEN_ASM(pushq %%rax)

        GEN_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_DEVICE_NOT_AVILABLE])
        
        GEN_ASM(movq %%rsp, %%rdi)
        GEN_ASM(cld)
        GEN_ASM(callq alo_exception_handler_common)
        
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%rax)
        GEN_ASM(popq %%rbx)
        GEN_ASM(popq %%rcx)
        GEN_ASM(popq %%rdx)

        GEN_ASM(popq %%rsi)
        GEN_ASM(popq %%rdi)

        GEN_ASM(popq %%rbp)
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%r8)
        GEN_ASM(popq %%r9)
        GEN_ASM(popq %%r10)
        GEN_ASM(popq %%r11)
        GEN_ASM(popq %%r12)
        GEN_ASM(popq %%r13)
        GEN_ASM(popq %%r14)
        GEN_ASM(popq %%r15)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)
        
        GEN_ASM(iretq)

    GEN_ASM(.global alo_exception_handler_double_fault)
    GEN_ASM(alo_exception_handler_double_fault:)
        GEN_ASM(pushq 32(%%rsp))

        GEN_ASM(pushq 24(%%rsp))

        GEN_ASM(pushq %%r15)
        GEN_ASM(pushq %%r14)
        GEN_ASM(pushq %%r13)
        GEN_ASM(pushq %%r12)
        GEN_ASM(pushq %%r11)
        GEN_ASM(pushq %%r10)
        GEN_ASM(pushq %%r9)
        GEN_ASM(pushq %%r8)

        GEN_ASM(pushq 120(%%rsp))
        GEN_ASM(pushq %%rbp)

        GEN_ASM(pushq %%rdi)
        GEN_ASM(pushq %%rsi)

        GEN_ASM(pushq %%rdx)
        GEN_ASM(pushq %%rcx)
        GEN_ASM(pushq %%rbx)
        GEN_ASM(pushq %%rax)

        GEN_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_DOUBLE_FAULT])
        
        GEN_ASM(movq %%rsp, %%rdi)
        GEN_ASM(cld)
        GEN_ASM(callq alo_exception_handler_common)
        
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%rax)
        GEN_ASM(popq %%rbx)
        GEN_ASM(popq %%rcx)
        GEN_ASM(popq %%rdx)

        GEN_ASM(popq %%rsi)
        GEN_ASM(popq %%rdi)

        GEN_ASM(popq %%rbp)
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%r8)
        GEN_ASM(popq %%r9)
        GEN_ASM(popq %%r10)
        GEN_ASM(popq %%r11)
        GEN_ASM(popq %%r12)
        GEN_ASM(popq %%r13)
        GEN_ASM(popq %%r14)
        GEN_ASM(popq %%r15)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)
        
        GEN_ASM(iretq)

    GEN_ASM(.global alo_exception_handler_coprocessor_segment_overrun)
    GEN_ASM(alo_exception_handler_coprocessor_segment_overrun:)
        GEN_ASM(pushq 0)

        GEN_ASM(pushq 32(%%rsp))

        GEN_ASM(pushq 24(%%rsp))

        GEN_ASM(pushq %%r15)
        GEN_ASM(pushq %%r14)
        GEN_ASM(pushq %%r13)
        GEN_ASM(pushq %%r12)
        GEN_ASM(pushq %%r11)
        GEN_ASM(pushq %%r10)
        GEN_ASM(pushq %%r9)
        GEN_ASM(pushq %%r8)

        GEN_ASM(pushq 120(%%rsp))
        GEN_ASM(pushq %%rbp)

        GEN_ASM(pushq %%rdi)
        GEN_ASM(pushq %%rsi)

        GEN_ASM(pushq %%rdx)
        GEN_ASM(pushq %%rcx)
        GEN_ASM(pushq %%rbx)
        GEN_ASM(pushq %%rax)

        GEN_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_COPROCESSOR_SEGMENT_OVERRUN])
        
        GEN_ASM(movq %%rsp, %%rdi)
        GEN_ASM(cld)
        GEN_ASM(callq alo_exception_handler_common)
        
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%rax)
        GEN_ASM(popq %%rbx)
        GEN_ASM(popq %%rcx)
        GEN_ASM(popq %%rdx)

        GEN_ASM(popq %%rsi)
        GEN_ASM(popq %%rdi)

        GEN_ASM(popq %%rbp)
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%r8)
        GEN_ASM(popq %%r9)
        GEN_ASM(popq %%r10)
        GEN_ASM(popq %%r11)
        GEN_ASM(popq %%r12)
        GEN_ASM(popq %%r13)
        GEN_ASM(popq %%r14)
        GEN_ASM(popq %%r15)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)
        
        GEN_ASM(iretq)

    GEN_ASM(.global alo_exception_handler_invalid_tss)
    GEN_ASM(alo_exception_handler_invalid_tss:)
        GEN_ASM(pushq 32(%%rsp))

        GEN_ASM(pushq 24(%%rsp))

        GEN_ASM(pushq %%r15)
        GEN_ASM(pushq %%r14)
        GEN_ASM(pushq %%r13)
        GEN_ASM(pushq %%r12)
        GEN_ASM(pushq %%r11)
        GEN_ASM(pushq %%r10)
        GEN_ASM(pushq %%r9)
        GEN_ASM(pushq %%r8)

        GEN_ASM(pushq 120(%%rsp))
        GEN_ASM(pushq %%rbp)

        GEN_ASM(pushq %%rdi)
        GEN_ASM(pushq %%rsi)

        GEN_ASM(pushq %%rdx)
        GEN_ASM(pushq %%rcx)
        GEN_ASM(pushq %%rbx)
        GEN_ASM(pushq %%rax)

        GEN_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_INVALID_TSS])
        
        GEN_ASM(movq %%rsp, %%rdi)
        GEN_ASM(cld)
        GEN_ASM(callq alo_exception_handler_common)
        
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%rax)
        GEN_ASM(popq %%rbx)
        GEN_ASM(popq %%rcx)
        GEN_ASM(popq %%rdx)

        GEN_ASM(popq %%rsi)
        GEN_ASM(popq %%rdi)

        GEN_ASM(popq %%rbp)
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%r8)
        GEN_ASM(popq %%r9)
        GEN_ASM(popq %%r10)
        GEN_ASM(popq %%r11)
        GEN_ASM(popq %%r12)
        GEN_ASM(popq %%r13)
        GEN_ASM(popq %%r14)
        GEN_ASM(popq %%r15)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)
        
        GEN_ASM(iretq)

    GEN_ASM(.global alo_exception_handler_segment_not_present)
    GEN_ASM(alo_exception_handler_segment_not_present:)
        GEN_ASM(pushq 32(%%rsp))

        GEN_ASM(pushq 24(%%rsp))

        GEN_ASM(pushq %%r15)
        GEN_ASM(pushq %%r14)
        GEN_ASM(pushq %%r13)
        GEN_ASM(pushq %%r12)
        GEN_ASM(pushq %%r11)
        GEN_ASM(pushq %%r10)
        GEN_ASM(pushq %%r9)
        GEN_ASM(pushq %%r8)

        GEN_ASM(pushq 120(%%rsp))
        GEN_ASM(pushq %%rbp)

        GEN_ASM(pushq %%rdi)
        GEN_ASM(pushq %%rsi)

        GEN_ASM(pushq %%rdx)
        GEN_ASM(pushq %%rcx)
        GEN_ASM(pushq %%rbx)
        GEN_ASM(pushq %%rax)

        GEN_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_SEGMENT_NOT_PRESENT])
        
        GEN_ASM(movq %%rsp, %%rdi)
        GEN_ASM(cld)
        GEN_ASM(callq alo_exception_handler_common)
        
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%rax)
        GEN_ASM(popq %%rbx)
        GEN_ASM(popq %%rcx)
        GEN_ASM(popq %%rdx)

        GEN_ASM(popq %%rsi)
        GEN_ASM(popq %%rdi)

        GEN_ASM(popq %%rbp)
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%r8)
        GEN_ASM(popq %%r9)
        GEN_ASM(popq %%r10)
        GEN_ASM(popq %%r11)
        GEN_ASM(popq %%r12)
        GEN_ASM(popq %%r13)
        GEN_ASM(popq %%r14)
        GEN_ASM(popq %%r15)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)
        
        GEN_ASM(iretq)

    GEN_ASM(.global alo_exception_handler_stack_segment_fault)
    GEN_ASM(alo_exception_handler_stack_segment_fault:)
        GEN_ASM(pushq 32(%%rsp))

        GEN_ASM(pushq 24(%%rsp))

        GEN_ASM(pushq %%r15)
        GEN_ASM(pushq %%r14)
        GEN_ASM(pushq %%r13)
        GEN_ASM(pushq %%r12)
        GEN_ASM(pushq %%r11)
        GEN_ASM(pushq %%r10)
        GEN_ASM(pushq %%r9)
        GEN_ASM(pushq %%r8)

        GEN_ASM(pushq 120(%%rsp))
        GEN_ASM(pushq %%rbp)

        GEN_ASM(pushq %%rdi)
        GEN_ASM(pushq %%rsi)

        GEN_ASM(pushq %%rdx)
        GEN_ASM(pushq %%rcx)
        GEN_ASM(pushq %%rbx)
        GEN_ASM(pushq %%rax)

        GEN_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_STACK_SEGMENT_FAULT])
        
        GEN_ASM(movq %%rsp, %%rdi)
        GEN_ASM(cld)
        GEN_ASM(callq alo_exception_handler_common)
        
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%rax)
        GEN_ASM(popq %%rbx)
        GEN_ASM(popq %%rcx)
        GEN_ASM(popq %%rdx)

        GEN_ASM(popq %%rsi)
        GEN_ASM(popq %%rdi)

        GEN_ASM(popq %%rbp)
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%r8)
        GEN_ASM(popq %%r9)
        GEN_ASM(popq %%r10)
        GEN_ASM(popq %%r11)
        GEN_ASM(popq %%r12)
        GEN_ASM(popq %%r13)
        GEN_ASM(popq %%r14)
        GEN_ASM(popq %%r15)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)
        
        GEN_ASM(iretq)

    GEN_ASM(.global alo_exception_handler_general_protection_fault)
    GEN_ASM(alo_exception_handler_general_protection_fault:)
        GEN_ASM(pushq 32(%%rsp))

        GEN_ASM(pushq 24(%%rsp))

        GEN_ASM(pushq %%r15)
        GEN_ASM(pushq %%r14)
        GEN_ASM(pushq %%r13)
        GEN_ASM(pushq %%r12)
        GEN_ASM(pushq %%r11)
        GEN_ASM(pushq %%r10)
        GEN_ASM(pushq %%r9)
        GEN_ASM(pushq %%r8)

        GEN_ASM(pushq 120(%%rsp))
        GEN_ASM(pushq %%rbp)

        GEN_ASM(pushq %%rdi)
        GEN_ASM(pushq %%rsi)

        GEN_ASM(pushq %%rdx)
        GEN_ASM(pushq %%rcx)
        GEN_ASM(pushq %%rbx)
        GEN_ASM(pushq %%rax)

        GEN_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_GENERAL_PROTECTION_FAULT])
        
        GEN_ASM(movq %%rsp, %%rdi)
        GEN_ASM(cld)
        GEN_ASM(callq alo_exception_handler_common)
        
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%rax)
        GEN_ASM(popq %%rbx)
        GEN_ASM(popq %%rcx)
        GEN_ASM(popq %%rdx)

        GEN_ASM(popq %%rsi)
        GEN_ASM(popq %%rdi)

        GEN_ASM(popq %%rbp)
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%r8)
        GEN_ASM(popq %%r9)
        GEN_ASM(popq %%r10)
        GEN_ASM(popq %%r11)
        GEN_ASM(popq %%r12)
        GEN_ASM(popq %%r13)
        GEN_ASM(popq %%r14)
        GEN_ASM(popq %%r15)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)
        
        GEN_ASM(iretq)

    GEN_ASM(.global alo_exception_handler_page_fault)
    GEN_ASM(alo_exception_handler_page_fault:)
        GEN_ASM(pushq 32(%%rsp))

        GEN_ASM(pushq 24(%%rsp))

        GEN_ASM(pushq %%r15)
        GEN_ASM(pushq %%r14)
        GEN_ASM(pushq %%r13)
        GEN_ASM(pushq %%r12)
        GEN_ASM(pushq %%r11)
        GEN_ASM(pushq %%r10)
        GEN_ASM(pushq %%r9)
        GEN_ASM(pushq %%r8)

        GEN_ASM(pushq 120(%%rsp))
        GEN_ASM(pushq %%rbp)

        GEN_ASM(pushq %%rdi)
        GEN_ASM(pushq %%rsi)

        GEN_ASM(pushq %%rdx)
        GEN_ASM(pushq %%rcx)
        GEN_ASM(pushq %%rbx)
        GEN_ASM(pushq %%rax)

        GEN_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_PAGE_FAULT])
        
        GEN_ASM(movq %%rsp, %%rdi)
        GEN_ASM(cld)
        GEN_ASM(callq alo_exception_handler_common)
        
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%rax)
        GEN_ASM(popq %%rbx)
        GEN_ASM(popq %%rcx)
        GEN_ASM(popq %%rdx)

        GEN_ASM(popq %%rsi)
        GEN_ASM(popq %%rdi)

        GEN_ASM(popq %%rbp)
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%r8)
        GEN_ASM(popq %%r9)
        GEN_ASM(popq %%r10)
        GEN_ASM(popq %%r11)
        GEN_ASM(popq %%r12)
        GEN_ASM(popq %%r13)
        GEN_ASM(popq %%r14)
        GEN_ASM(popq %%r15)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)
        
        GEN_ASM(iretq)

    GEN_ASM(.global alo_exception_handler_reserved0)
    GEN_ASM(alo_exception_handler_reserved0:)
        GEN_ASM(pushq 0)

        GEN_ASM(pushq 32(%%rsp))

        GEN_ASM(pushq 24(%%rsp))

        GEN_ASM(pushq %%r15)
        GEN_ASM(pushq %%r14)
        GEN_ASM(pushq %%r13)
        GEN_ASM(pushq %%r12)
        GEN_ASM(pushq %%r11)
        GEN_ASM(pushq %%r10)
        GEN_ASM(pushq %%r9)
        GEN_ASM(pushq %%r8)

        GEN_ASM(pushq 120(%%rsp))
        GEN_ASM(pushq %%rbp)

        GEN_ASM(pushq %%rdi)
        GEN_ASM(pushq %%rsi)

        GEN_ASM(pushq %%rdx)
        GEN_ASM(pushq %%rcx)
        GEN_ASM(pushq %%rbx)
        GEN_ASM(pushq %%rax)

        GEN_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED0])
        
        GEN_ASM(movq %%rsp, %%rdi)
        GEN_ASM(cld)
        GEN_ASM(callq alo_exception_handler_common)
        
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%rax)
        GEN_ASM(popq %%rbx)
        GEN_ASM(popq %%rcx)
        GEN_ASM(popq %%rdx)

        GEN_ASM(popq %%rsi)
        GEN_ASM(popq %%rdi)

        GEN_ASM(popq %%rbp)
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%r8)
        GEN_ASM(popq %%r9)
        GEN_ASM(popq %%r10)
        GEN_ASM(popq %%r11)
        GEN_ASM(popq %%r12)
        GEN_ASM(popq %%r13)
        GEN_ASM(popq %%r14)
        GEN_ASM(popq %%r15)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)
        
        GEN_ASM(iretq)

    GEN_ASM(.global alo_exception_handler_x87_floating_point)
    GEN_ASM(alo_exception_handler_x87_floating_point:)
        GEN_ASM(pushq 0)

        GEN_ASM(pushq 32(%%rsp))

        GEN_ASM(pushq 24(%%rsp))

        GEN_ASM(pushq %%r15)
        GEN_ASM(pushq %%r14)
        GEN_ASM(pushq %%r13)
        GEN_ASM(pushq %%r12)
        GEN_ASM(pushq %%r11)
        GEN_ASM(pushq %%r10)
        GEN_ASM(pushq %%r9)
        GEN_ASM(pushq %%r8)

        GEN_ASM(pushq 120(%%rsp))
        GEN_ASM(pushq %%rbp)

        GEN_ASM(pushq %%rdi)
        GEN_ASM(pushq %%rsi)

        GEN_ASM(pushq %%rdx)
        GEN_ASM(pushq %%rcx)
        GEN_ASM(pushq %%rbx)
        GEN_ASM(pushq %%rax)

        GEN_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_X87_FLOATING_POINT])
        
        GEN_ASM(movq %%rsp, %%rdi)
        GEN_ASM(cld)
        GEN_ASM(callq alo_exception_handler_common)
        
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%rax)
        GEN_ASM(popq %%rbx)
        GEN_ASM(popq %%rcx)
        GEN_ASM(popq %%rdx)

        GEN_ASM(popq %%rsi)
        GEN_ASM(popq %%rdi)

        GEN_ASM(popq %%rbp)
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%r8)
        GEN_ASM(popq %%r9)
        GEN_ASM(popq %%r10)
        GEN_ASM(popq %%r11)
        GEN_ASM(popq %%r12)
        GEN_ASM(popq %%r13)
        GEN_ASM(popq %%r14)
        GEN_ASM(popq %%r15)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)
        
        GEN_ASM(iretq)

    GEN_ASM(.global alo_exception_handler_alignment_check)
    GEN_ASM(alo_exception_handler_alignment_check:)
        GEN_ASM(pushq 32(%%rsp))

        GEN_ASM(pushq 24(%%rsp))

        GEN_ASM(pushq %%r15)
        GEN_ASM(pushq %%r14)
        GEN_ASM(pushq %%r13)
        GEN_ASM(pushq %%r12)
        GEN_ASM(pushq %%r11)
        GEN_ASM(pushq %%r10)
        GEN_ASM(pushq %%r9)
        GEN_ASM(pushq %%r8)

        GEN_ASM(pushq 120(%%rsp))
        GEN_ASM(pushq %%rbp)

        GEN_ASM(pushq %%rdi)
        GEN_ASM(pushq %%rsi)

        GEN_ASM(pushq %%rdx)
        GEN_ASM(pushq %%rcx)
        GEN_ASM(pushq %%rbx)
        GEN_ASM(pushq %%rax)

        GEN_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_ALIGNMENT_CHECK])
        
        GEN_ASM(movq %%rsp, %%rdi)
        GEN_ASM(cld)
        GEN_ASM(callq alo_exception_handler_common)
        
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%rax)
        GEN_ASM(popq %%rbx)
        GEN_ASM(popq %%rcx)
        GEN_ASM(popq %%rdx)

        GEN_ASM(popq %%rsi)
        GEN_ASM(popq %%rdi)

        GEN_ASM(popq %%rbp)
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%r8)
        GEN_ASM(popq %%r9)
        GEN_ASM(popq %%r10)
        GEN_ASM(popq %%r11)
        GEN_ASM(popq %%r12)
        GEN_ASM(popq %%r13)
        GEN_ASM(popq %%r14)
        GEN_ASM(popq %%r15)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)
        
        GEN_ASM(iretq)

    GEN_ASM(.global alo_exception_handler_machine_check)
    GEN_ASM(alo_exception_handler_machine_check:)
        GEN_ASM(pushq 0)

        GEN_ASM(pushq 32(%%rsp))

        GEN_ASM(pushq 24(%%rsp))

        GEN_ASM(pushq %%r15)
        GEN_ASM(pushq %%r14)
        GEN_ASM(pushq %%r13)
        GEN_ASM(pushq %%r12)
        GEN_ASM(pushq %%r11)
        GEN_ASM(pushq %%r10)
        GEN_ASM(pushq %%r9)
        GEN_ASM(pushq %%r8)

        GEN_ASM(pushq 120(%%rsp))
        GEN_ASM(pushq %%rbp)

        GEN_ASM(pushq %%rdi)
        GEN_ASM(pushq %%rsi)

        GEN_ASM(pushq %%rdx)
        GEN_ASM(pushq %%rcx)
        GEN_ASM(pushq %%rbx)
        GEN_ASM(pushq %%rax)

        GEN_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_MACHINE_CHECK])
        
        GEN_ASM(movq %%rsp, %%rdi)
        GEN_ASM(cld)
        GEN_ASM(callq alo_exception_handler_common)
        
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%rax)
        GEN_ASM(popq %%rbx)
        GEN_ASM(popq %%rcx)
        GEN_ASM(popq %%rdx)

        GEN_ASM(popq %%rsi)
        GEN_ASM(popq %%rdi)

        GEN_ASM(popq %%rbp)
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%r8)
        GEN_ASM(popq %%r9)
        GEN_ASM(popq %%r10)
        GEN_ASM(popq %%r11)
        GEN_ASM(popq %%r12)
        GEN_ASM(popq %%r13)
        GEN_ASM(popq %%r14)
        GEN_ASM(popq %%r15)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)
        
        GEN_ASM(iretq)

    GEN_ASM(.global alo_exception_handler_simd_floating_point)
    GEN_ASM(alo_exception_handler_simd_floating_point:)
        GEN_ASM(pushq 0)

        GEN_ASM(pushq 32(%%rsp))

        GEN_ASM(pushq 24(%%rsp))

        GEN_ASM(pushq %%r15)
        GEN_ASM(pushq %%r14)
        GEN_ASM(pushq %%r13)
        GEN_ASM(pushq %%r12)
        GEN_ASM(pushq %%r11)
        GEN_ASM(pushq %%r10)
        GEN_ASM(pushq %%r9)
        GEN_ASM(pushq %%r8)

        GEN_ASM(pushq 120(%%rsp))
        GEN_ASM(pushq %%rbp)

        GEN_ASM(pushq %%rdi)
        GEN_ASM(pushq %%rsi)

        GEN_ASM(pushq %%rdx)
        GEN_ASM(pushq %%rcx)
        GEN_ASM(pushq %%rbx)
        GEN_ASM(pushq %%rax)

        GEN_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_SIMD_FLOATING_POINT])
        
        GEN_ASM(movq %%rsp, %%rdi)
        GEN_ASM(cld)
        GEN_ASM(callq alo_exception_handler_common)
        
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%rax)
        GEN_ASM(popq %%rbx)
        GEN_ASM(popq %%rcx)
        GEN_ASM(popq %%rdx)

        GEN_ASM(popq %%rsi)
        GEN_ASM(popq %%rdi)

        GEN_ASM(popq %%rbp)
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%r8)
        GEN_ASM(popq %%r9)
        GEN_ASM(popq %%r10)
        GEN_ASM(popq %%r11)
        GEN_ASM(popq %%r12)
        GEN_ASM(popq %%r13)
        GEN_ASM(popq %%r14)
        GEN_ASM(popq %%r15)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)
        
        GEN_ASM(iretq)

    GEN_ASM(.global alo_exception_handler_virtualization)
    GEN_ASM(alo_exception_handler_virtualization:)
        GEN_ASM(pushq 0)

        GEN_ASM(pushq 32(%%rsp))

        GEN_ASM(pushq 24(%%rsp))

        GEN_ASM(pushq %%r15)
        GEN_ASM(pushq %%r14)
        GEN_ASM(pushq %%r13)
        GEN_ASM(pushq %%r12)
        GEN_ASM(pushq %%r11)
        GEN_ASM(pushq %%r10)
        GEN_ASM(pushq %%r9)
        GEN_ASM(pushq %%r8)

        GEN_ASM(pushq 120(%%rsp))
        GEN_ASM(pushq %%rbp)

        GEN_ASM(pushq %%rdi)
        GEN_ASM(pushq %%rsi)

        GEN_ASM(pushq %%rdx)
        GEN_ASM(pushq %%rcx)
        GEN_ASM(pushq %%rbx)
        GEN_ASM(pushq %%rax)

        GEN_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_VIRTUALIZATION])
        
        GEN_ASM(movq %%rsp, %%rdi)
        GEN_ASM(cld)
        GEN_ASM(callq alo_exception_handler_common)
        
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%rax)
        GEN_ASM(popq %%rbx)
        GEN_ASM(popq %%rcx)
        GEN_ASM(popq %%rdx)

        GEN_ASM(popq %%rsi)
        GEN_ASM(popq %%rdi)

        GEN_ASM(popq %%rbp)
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%r8)
        GEN_ASM(popq %%r9)
        GEN_ASM(popq %%r10)
        GEN_ASM(popq %%r11)
        GEN_ASM(popq %%r12)
        GEN_ASM(popq %%r13)
        GEN_ASM(popq %%r14)
        GEN_ASM(popq %%r15)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)
        
        GEN_ASM(iretq)

    GEN_ASM(.global alo_exception_handler_control_protection)
    GEN_ASM(alo_exception_handler_control_protection:)
        GEN_ASM(pushq 32(%%rsp))

        GEN_ASM(pushq 24(%%rsp))

        GEN_ASM(pushq %%r15)
        GEN_ASM(pushq %%r14)
        GEN_ASM(pushq %%r13)
        GEN_ASM(pushq %%r12)
        GEN_ASM(pushq %%r11)
        GEN_ASM(pushq %%r10)
        GEN_ASM(pushq %%r9)
        GEN_ASM(pushq %%r8)

        GEN_ASM(pushq 120(%%rsp))
        GEN_ASM(pushq %%rbp)

        GEN_ASM(pushq %%rdi)
        GEN_ASM(pushq %%rsi)

        GEN_ASM(pushq %%rdx)
        GEN_ASM(pushq %%rcx)
        GEN_ASM(pushq %%rbx)
        GEN_ASM(pushq %%rax)

        GEN_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_CONTROL_PROTECTION])
        
        GEN_ASM(movq %%rsp, %%rdi)
        GEN_ASM(cld)
        GEN_ASM(callq alo_exception_handler_common)
        
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%rax)
        GEN_ASM(popq %%rbx)
        GEN_ASM(popq %%rcx)
        GEN_ASM(popq %%rdx)

        GEN_ASM(popq %%rsi)
        GEN_ASM(popq %%rdi)

        GEN_ASM(popq %%rbp)
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%r8)
        GEN_ASM(popq %%r9)
        GEN_ASM(popq %%r10)
        GEN_ASM(popq %%r11)
        GEN_ASM(popq %%r12)
        GEN_ASM(popq %%r13)
        GEN_ASM(popq %%r14)
        GEN_ASM(popq %%r15)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)
        
        GEN_ASM(iretq)

    GEN_ASM(.global alo_exception_handler_reserved1)
    GEN_ASM(alo_exception_handler_reserved1:)
        GEN_ASM(pushq 0)

        GEN_ASM(pushq 32(%%rsp))

        GEN_ASM(pushq 24(%%rsp))

        GEN_ASM(pushq %%r15)
        GEN_ASM(pushq %%r14)
        GEN_ASM(pushq %%r13)
        GEN_ASM(pushq %%r12)
        GEN_ASM(pushq %%r11)
        GEN_ASM(pushq %%r10)
        GEN_ASM(pushq %%r9)
        GEN_ASM(pushq %%r8)

        GEN_ASM(pushq 120(%%rsp))
        GEN_ASM(pushq %%rbp)

        GEN_ASM(pushq %%rdi)
        GEN_ASM(pushq %%rsi)

        GEN_ASM(pushq %%rdx)
        GEN_ASM(pushq %%rcx)
        GEN_ASM(pushq %%rbx)
        GEN_ASM(pushq %%rax)

        GEN_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED1])
        
        GEN_ASM(movq %%rsp, %%rdi)
        GEN_ASM(cld)
        GEN_ASM(callq alo_exception_handler_common)
        
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%rax)
        GEN_ASM(popq %%rbx)
        GEN_ASM(popq %%rcx)
        GEN_ASM(popq %%rdx)

        GEN_ASM(popq %%rsi)
        GEN_ASM(popq %%rdi)

        GEN_ASM(popq %%rbp)
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%r8)
        GEN_ASM(popq %%r9)
        GEN_ASM(popq %%r10)
        GEN_ASM(popq %%r11)
        GEN_ASM(popq %%r12)
        GEN_ASM(popq %%r13)
        GEN_ASM(popq %%r14)
        GEN_ASM(popq %%r15)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)
        
        GEN_ASM(iretq)

    GEN_ASM(.global alo_exception_handler_reserved2)
    GEN_ASM(alo_exception_handler_reserved2:)
        GEN_ASM(pushq 0)

        GEN_ASM(pushq 32(%%rsp))

        GEN_ASM(pushq 24(%%rsp))

        GEN_ASM(pushq %%r15)
        GEN_ASM(pushq %%r14)
        GEN_ASM(pushq %%r13)
        GEN_ASM(pushq %%r12)
        GEN_ASM(pushq %%r11)
        GEN_ASM(pushq %%r10)
        GEN_ASM(pushq %%r9)
        GEN_ASM(pushq %%r8)

        GEN_ASM(pushq 120(%%rsp))
        GEN_ASM(pushq %%rbp)

        GEN_ASM(pushq %%rdi)
        GEN_ASM(pushq %%rsi)

        GEN_ASM(pushq %%rdx)
        GEN_ASM(pushq %%rcx)
        GEN_ASM(pushq %%rbx)
        GEN_ASM(pushq %%rax)

        GEN_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED2])
        
        GEN_ASM(movq %%rsp, %%rdi)
        GEN_ASM(cld)
        GEN_ASM(callq alo_exception_handler_common)
        
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%rax)
        GEN_ASM(popq %%rbx)
        GEN_ASM(popq %%rcx)
        GEN_ASM(popq %%rdx)

        GEN_ASM(popq %%rsi)
        GEN_ASM(popq %%rdi)

        GEN_ASM(popq %%rbp)
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%r8)
        GEN_ASM(popq %%r9)
        GEN_ASM(popq %%r10)
        GEN_ASM(popq %%r11)
        GEN_ASM(popq %%r12)
        GEN_ASM(popq %%r13)
        GEN_ASM(popq %%r14)
        GEN_ASM(popq %%r15)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)
        
        GEN_ASM(iretq)

    GEN_ASM(.global alo_exception_handler_reserved3)
    GEN_ASM(alo_exception_handler_reserved3:)
        GEN_ASM(pushq 0)

        GEN_ASM(pushq 32(%%rsp))

        GEN_ASM(pushq 24(%%rsp))

        GEN_ASM(pushq %%r15)
        GEN_ASM(pushq %%r14)
        GEN_ASM(pushq %%r13)
        GEN_ASM(pushq %%r12)
        GEN_ASM(pushq %%r11)
        GEN_ASM(pushq %%r10)
        GEN_ASM(pushq %%r9)
        GEN_ASM(pushq %%r8)

        GEN_ASM(pushq 120(%%rsp))
        GEN_ASM(pushq %%rbp)

        GEN_ASM(pushq %%rdi)
        GEN_ASM(pushq %%rsi)

        GEN_ASM(pushq %%rdx)
        GEN_ASM(pushq %%rcx)
        GEN_ASM(pushq %%rbx)
        GEN_ASM(pushq %%rax)

        GEN_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED3])
        
        GEN_ASM(movq %%rsp, %%rdi)
        GEN_ASM(cld)
        GEN_ASM(callq alo_exception_handler_common)
        
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%rax)
        GEN_ASM(popq %%rbx)
        GEN_ASM(popq %%rcx)
        GEN_ASM(popq %%rdx)

        GEN_ASM(popq %%rsi)
        GEN_ASM(popq %%rdi)

        GEN_ASM(popq %%rbp)
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%r8)
        GEN_ASM(popq %%r9)
        GEN_ASM(popq %%r10)
        GEN_ASM(popq %%r11)
        GEN_ASM(popq %%r12)
        GEN_ASM(popq %%r13)
        GEN_ASM(popq %%r14)
        GEN_ASM(popq %%r15)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)
        
        GEN_ASM(iretq)

    GEN_ASM(.global alo_exception_handler_reserved4)
    GEN_ASM(alo_exception_handler_reserved4:)
        GEN_ASM(pushq 0)

        GEN_ASM(pushq 32(%%rsp))

        GEN_ASM(pushq 24(%%rsp))

        GEN_ASM(pushq %%r15)
        GEN_ASM(pushq %%r14)
        GEN_ASM(pushq %%r13)
        GEN_ASM(pushq %%r12)
        GEN_ASM(pushq %%r11)
        GEN_ASM(pushq %%r10)
        GEN_ASM(pushq %%r9)
        GEN_ASM(pushq %%r8)

        GEN_ASM(pushq 120(%%rsp))
        GEN_ASM(pushq %%rbp)

        GEN_ASM(pushq %%rdi)
        GEN_ASM(pushq %%rsi)

        GEN_ASM(pushq %%rdx)
        GEN_ASM(pushq %%rcx)
        GEN_ASM(pushq %%rbx)
        GEN_ASM(pushq %%rax)

        GEN_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED4])
        
        GEN_ASM(movq %%rsp, %%rdi)
        GEN_ASM(cld)
        GEN_ASM(callq alo_exception_handler_common)
        
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%rax)
        GEN_ASM(popq %%rbx)
        GEN_ASM(popq %%rcx)
        GEN_ASM(popq %%rdx)

        GEN_ASM(popq %%rsi)
        GEN_ASM(popq %%rdi)

        GEN_ASM(popq %%rbp)
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%r8)
        GEN_ASM(popq %%r9)
        GEN_ASM(popq %%r10)
        GEN_ASM(popq %%r11)
        GEN_ASM(popq %%r12)
        GEN_ASM(popq %%r13)
        GEN_ASM(popq %%r14)
        GEN_ASM(popq %%r15)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)
        
        GEN_ASM(iretq)

    GEN_ASM(.global alo_exception_handler_reserved5)
    GEN_ASM(alo_exception_handler_reserved5:)
        GEN_ASM(pushq 0)

        GEN_ASM(pushq 32(%%rsp))

        GEN_ASM(pushq 24(%%rsp))

        GEN_ASM(pushq %%r15)
        GEN_ASM(pushq %%r14)
        GEN_ASM(pushq %%r13)
        GEN_ASM(pushq %%r12)
        GEN_ASM(pushq %%r11)
        GEN_ASM(pushq %%r10)
        GEN_ASM(pushq %%r9)
        GEN_ASM(pushq %%r8)

        GEN_ASM(pushq 120(%%rsp))
        GEN_ASM(pushq %%rbp)

        GEN_ASM(pushq %%rdi)
        GEN_ASM(pushq %%rsi)

        GEN_ASM(pushq %%rdx)
        GEN_ASM(pushq %%rcx)
        GEN_ASM(pushq %%rbx)
        GEN_ASM(pushq %%rax)

        GEN_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED5])
        
        GEN_ASM(movq %%rsp, %%rdi)
        GEN_ASM(cld)
        GEN_ASM(callq alo_exception_handler_common)
        
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%rax)
        GEN_ASM(popq %%rbx)
        GEN_ASM(popq %%rcx)
        GEN_ASM(popq %%rdx)

        GEN_ASM(popq %%rsi)
        GEN_ASM(popq %%rdi)

        GEN_ASM(popq %%rbp)
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%r8)
        GEN_ASM(popq %%r9)
        GEN_ASM(popq %%r10)
        GEN_ASM(popq %%r11)
        GEN_ASM(popq %%r12)
        GEN_ASM(popq %%r13)
        GEN_ASM(popq %%r14)
        GEN_ASM(popq %%r15)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)
        
        GEN_ASM(iretq)

    GEN_ASM(.global alo_exception_handler_reserved6)
    GEN_ASM(alo_exception_handler_reserved6:)
        GEN_ASM(pushq 0)

        GEN_ASM(pushq 32(%%rsp))

        GEN_ASM(pushq 24(%%rsp))

        GEN_ASM(pushq %%r15)
        GEN_ASM(pushq %%r14)
        GEN_ASM(pushq %%r13)
        GEN_ASM(pushq %%r12)
        GEN_ASM(pushq %%r11)
        GEN_ASM(pushq %%r10)
        GEN_ASM(pushq %%r9)
        GEN_ASM(pushq %%r8)

        GEN_ASM(pushq 120(%%rsp))
        GEN_ASM(pushq %%rbp)

        GEN_ASM(pushq %%rdi)
        GEN_ASM(pushq %%rsi)

        GEN_ASM(pushq %%rdx)
        GEN_ASM(pushq %%rcx)
        GEN_ASM(pushq %%rbx)
        GEN_ASM(pushq %%rax)

        GEN_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED6])
        
        GEN_ASM(movq %%rsp, %%rdi)
        GEN_ASM(cld)
        GEN_ASM(callq alo_exception_handler_common)
        
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%rax)
        GEN_ASM(popq %%rbx)
        GEN_ASM(popq %%rcx)
        GEN_ASM(popq %%rdx)

        GEN_ASM(popq %%rsi)
        GEN_ASM(popq %%rdi)

        GEN_ASM(popq %%rbp)
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%r8)
        GEN_ASM(popq %%r9)
        GEN_ASM(popq %%r10)
        GEN_ASM(popq %%r11)
        GEN_ASM(popq %%r12)
        GEN_ASM(popq %%r13)
        GEN_ASM(popq %%r14)
        GEN_ASM(popq %%r15)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)
        
        GEN_ASM(iretq)

    GEN_ASM(.global alo_exception_handler_hypervisor_injection)
    GEN_ASM(alo_exception_handler_hypervisor_injection:)
        GEN_ASM(pushq 0)

        GEN_ASM(pushq 32(%%rsp))

        GEN_ASM(pushq 24(%%rsp))

        GEN_ASM(pushq %%r15)
        GEN_ASM(pushq %%r14)
        GEN_ASM(pushq %%r13)
        GEN_ASM(pushq %%r12)
        GEN_ASM(pushq %%r11)
        GEN_ASM(pushq %%r10)
        GEN_ASM(pushq %%r9)
        GEN_ASM(pushq %%r8)

        GEN_ASM(pushq 120(%%rsp))
        GEN_ASM(pushq %%rbp)

        GEN_ASM(pushq %%rdi)
        GEN_ASM(pushq %%rsi)

        GEN_ASM(pushq %%rdx)
        GEN_ASM(pushq %%rcx)
        GEN_ASM(pushq %%rbx)
        GEN_ASM(pushq %%rax)

        GEN_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_HYPERVISOR_INJECTION])
        
        GEN_ASM(movq %%rsp, %%rdi)
        GEN_ASM(cld)
        GEN_ASM(callq alo_exception_handler_common)
        
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%rax)
        GEN_ASM(popq %%rbx)
        GEN_ASM(popq %%rcx)
        GEN_ASM(popq %%rdx)

        GEN_ASM(popq %%rsi)
        GEN_ASM(popq %%rdi)

        GEN_ASM(popq %%rbp)
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%r8)
        GEN_ASM(popq %%r9)
        GEN_ASM(popq %%r10)
        GEN_ASM(popq %%r11)
        GEN_ASM(popq %%r12)
        GEN_ASM(popq %%r13)
        GEN_ASM(popq %%r14)
        GEN_ASM(popq %%r15)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)
        
        GEN_ASM(iretq)

    GEN_ASM(.global alo_exception_handler_vmm_communication)
    GEN_ASM(alo_exception_handler_vmm_communication:)
        GEN_ASM(pushq 32(%%rsp))

        GEN_ASM(pushq 24(%%rsp))

        GEN_ASM(pushq %%r15)
        GEN_ASM(pushq %%r14)
        GEN_ASM(pushq %%r13)
        GEN_ASM(pushq %%r12)
        GEN_ASM(pushq %%r11)
        GEN_ASM(pushq %%r10)
        GEN_ASM(pushq %%r9)
        GEN_ASM(pushq %%r8)

        GEN_ASM(pushq 120(%%rsp))
        GEN_ASM(pushq %%rbp)

        GEN_ASM(pushq %%rdi)
        GEN_ASM(pushq %%rsi)

        GEN_ASM(pushq %%rdx)
        GEN_ASM(pushq %%rcx)
        GEN_ASM(pushq %%rbx)
        GEN_ASM(pushq %%rax)

        GEN_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_VMM_COMMUNICATION])
        
        GEN_ASM(movq %%rsp, %%rdi)
        GEN_ASM(cld)
        GEN_ASM(callq alo_exception_handler_common)
        
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%rax)
        GEN_ASM(popq %%rbx)
        GEN_ASM(popq %%rcx)
        GEN_ASM(popq %%rdx)

        GEN_ASM(popq %%rsi)
        GEN_ASM(popq %%rdi)

        GEN_ASM(popq %%rbp)
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%r8)
        GEN_ASM(popq %%r9)
        GEN_ASM(popq %%r10)
        GEN_ASM(popq %%r11)
        GEN_ASM(popq %%r12)
        GEN_ASM(popq %%r13)
        GEN_ASM(popq %%r14)
        GEN_ASM(popq %%r15)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)
        
        GEN_ASM(iretq)

    GEN_ASM(.global alo_exception_handler_security)
    GEN_ASM(alo_exception_handler_security:)
        GEN_ASM(pushq 32(%%rsp))

        GEN_ASM(pushq 24(%%rsp))

        GEN_ASM(pushq %%r15)
        GEN_ASM(pushq %%r14)
        GEN_ASM(pushq %%r13)
        GEN_ASM(pushq %%r12)
        GEN_ASM(pushq %%r11)
        GEN_ASM(pushq %%r10)
        GEN_ASM(pushq %%r9)
        GEN_ASM(pushq %%r8)

        GEN_ASM(pushq 120(%%rsp))
        GEN_ASM(pushq %%rbp)

        GEN_ASM(pushq %%rdi)
        GEN_ASM(pushq %%rsi)

        GEN_ASM(pushq %%rdx)
        GEN_ASM(pushq %%rcx)
        GEN_ASM(pushq %%rbx)
        GEN_ASM(pushq %%rax)

        GEN_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_SECURITY])
        
        GEN_ASM(movq %%rsp, %%rdi)
        GEN_ASM(cld)
        GEN_ASM(callq alo_exception_handler_common)
        
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%rax)
        GEN_ASM(popq %%rbx)
        GEN_ASM(popq %%rcx)
        GEN_ASM(popq %%rdx)

        GEN_ASM(popq %%rsi)
        GEN_ASM(popq %%rdi)

        GEN_ASM(popq %%rbp)
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%r8)
        GEN_ASM(popq %%r9)
        GEN_ASM(popq %%r10)
        GEN_ASM(popq %%r11)
        GEN_ASM(popq %%r12)
        GEN_ASM(popq %%r13)
        GEN_ASM(popq %%r14)
        GEN_ASM(popq %%r15)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)
        
        GEN_ASM(iretq)

    GEN_ASM(.global alo_exception_handler_reserved7)
    GEN_ASM(alo_exception_handler_reserved7:)
        GEN_ASM(pushq 0)

        GEN_ASM(pushq 32(%%rsp))

        GEN_ASM(pushq 24(%%rsp))

        GEN_ASM(pushq %%r15)
        GEN_ASM(pushq %%r14)
        GEN_ASM(pushq %%r13)
        GEN_ASM(pushq %%r12)
        GEN_ASM(pushq %%r11)
        GEN_ASM(pushq %%r10)
        GEN_ASM(pushq %%r9)
        GEN_ASM(pushq %%r8)

        GEN_ASM(pushq 120(%%rsp))
        GEN_ASM(pushq %%rbp)

        GEN_ASM(pushq %%rdi)
        GEN_ASM(pushq %%rsi)

        GEN_ASM(pushq %%rdx)
        GEN_ASM(pushq %%rcx)
        GEN_ASM(pushq %%rbx)
        GEN_ASM(pushq %%rax)

        GEN_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED7])
        
        GEN_ASM(movq %%rsp, %%rdi)
        GEN_ASM(cld)
        GEN_ASM(callq alo_exception_handler_common)
        
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%rax)
        GEN_ASM(popq %%rbx)
        GEN_ASM(popq %%rcx)
        GEN_ASM(popq %%rdx)

        GEN_ASM(popq %%rsi)
        GEN_ASM(popq %%rdi)

        GEN_ASM(popq %%rbp)
        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(popq %%r8)
        GEN_ASM(popq %%r9)
        GEN_ASM(popq %%r10)
        GEN_ASM(popq %%r11)
        GEN_ASM(popq %%r12)
        GEN_ASM(popq %%r13)
        GEN_ASM(popq %%r14)
        GEN_ASM(popq %%r15)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)

        GEN_ASM(subq 8, %%rsp)
        
        GEN_ASM(iretq),

    ::
        [ALO_INTERRUPT_VECTOR_EXCEPTION_DIVIDE_BY_ZERO]"n"(ALO_INTERRUPT_VECTOR_EXCEPTION_DIVIDE_BY_ZERO),
        [ALO_INTERRUPT_VECTOR_EXCEPTION_DEBUG_TRAP]"n"(ALO_INTERRUPT_VECTOR_EXCEPTION_DEBUG_TRAP),
        [ALO_INTERRUPT_VECTOR_EXCEPTION_NMI]"n"(ALO_INTERRUPT_VECTOR_EXCEPTION_NMI),
        [ALO_INTERRUPT_VECTOR_EXCEPTION_BREAKPOINT]"n"(ALO_INTERRUPT_VECTOR_EXCEPTION_BREAKPOINT),
        [ALO_INTERRUPT_VECTOR_EXCEPTION_OVERFLOW]"n"(ALO_INTERRUPT_VECTOR_EXCEPTION_OVERFLOW),
        [ALO_INTERRUPT_VECTOR_EXCEPTION_BOUND_RANGE_EXCEEDED]"n"(ALO_INTERRUPT_VECTOR_EXCEPTION_BOUND_RANGE_EXCEEDED),
        [ALO_INTERRUPT_VECTOR_EXCEPTION_INVALID_OPCODE]"n"(ALO_INTERRUPT_VECTOR_EXCEPTION_INVALID_OPCODE),
        [ALO_INTERRUPT_VECTOR_EXCEPTION_DEVICE_NOT_AVILABLE]"n"(ALO_INTERRUPT_VECTOR_EXCEPTION_DEVICE_NOT_AVILABLE),
        [ALO_INTERRUPT_VECTOR_EXCEPTION_DOUBLE_FAULT]"n"(ALO_INTERRUPT_VECTOR_EXCEPTION_DOUBLE_FAULT),
        [ALO_INTERRUPT_VECTOR_EXCEPTION_COPROCESSOR_SEGMENT_OVERRUN]"n"(ALO_INTERRUPT_VECTOR_EXCEPTION_COPROCESSOR_SEGMENT_OVERRUN),
        [ALO_INTERRUPT_VECTOR_EXCEPTION_INVALID_TSS]"n"(ALO_INTERRUPT_VECTOR_EXCEPTION_INVALID_TSS),
        [ALO_INTERRUPT_VECTOR_EXCEPTION_SEGMENT_NOT_PRESENT]"n"(ALO_INTERRUPT_VECTOR_EXCEPTION_SEGMENT_NOT_PRESENT),
        [ALO_INTERRUPT_VECTOR_EXCEPTION_STACK_SEGMENT_FAULT]"n"(ALO_INTERRUPT_VECTOR_EXCEPTION_STACK_SEGMENT_FAULT),
        [ALO_INTERRUPT_VECTOR_EXCEPTION_GENERAL_PROTECTION_FAULT]"n"(ALO_INTERRUPT_VECTOR_EXCEPTION_GENERAL_PROTECTION_FAULT),
        [ALO_INTERRUPT_VECTOR_EXCEPTION_PAGE_FAULT]"n"(ALO_INTERRUPT_VECTOR_EXCEPTION_PAGE_FAULT),
        [ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED0]"n"(ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED0),
        [ALO_INTERRUPT_VECTOR_EXCEPTION_X87_FLOATING_POINT]"n"(ALO_INTERRUPT_VECTOR_EXCEPTION_X87_FLOATING_POINT),
        [ALO_INTERRUPT_VECTOR_EXCEPTION_ALIGNMENT_CHECK]"n"(ALO_INTERRUPT_VECTOR_EXCEPTION_ALIGNMENT_CHECK),
        [ALO_INTERRUPT_VECTOR_EXCEPTION_MACHINE_CHECK]"n"(ALO_INTERRUPT_VECTOR_EXCEPTION_MACHINE_CHECK),
        [ALO_INTERRUPT_VECTOR_EXCEPTION_SIMD_FLOATING_POINT]"n"(ALO_INTERRUPT_VECTOR_EXCEPTION_SIMD_FLOATING_POINT),
        [ALO_INTERRUPT_VECTOR_EXCEPTION_VIRTUALIZATION]"n"(ALO_INTERRUPT_VECTOR_EXCEPTION_VIRTUALIZATION),
        [ALO_INTERRUPT_VECTOR_EXCEPTION_CONTROL_PROTECTION]"n"(ALO_INTERRUPT_VECTOR_EXCEPTION_CONTROL_PROTECTION),
        [ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED1]"n"(ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED1),
        [ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED2]"n"(ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED2),
        [ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED3]"n"(ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED3),
        [ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED4]"n"(ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED4),
        [ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED5]"n"(ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED5),
        [ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED6]"n"(ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED6),
        [ALO_INTERRUPT_VECTOR_EXCEPTION_HYPERVISOR_INJECTION]"n"(ALO_INTERRUPT_VECTOR_EXCEPTION_HYPERVISOR_INJECTION),
        [ALO_INTERRUPT_VECTOR_EXCEPTION_VMM_COMMUNICATION]"n"(ALO_INTERRUPT_VECTOR_EXCEPTION_VMM_COMMUNICATION),
        [ALO_INTERRUPT_VECTOR_EXCEPTION_SECURITY]"n"(ALO_INTERRUPT_VECTOR_EXCEPTION_SECURITY),
        [ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED7]"n"(ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED7)
    );
}
// clang-format on
