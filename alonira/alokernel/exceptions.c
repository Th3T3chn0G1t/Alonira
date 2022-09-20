// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include <genlog.h>

#include "include/exceptions.h"

#include "include/kdiagnostic.h"
#include "include/idt.h"
#include "include/tss.h"
#include "include/vga.h"

static ALO_INTERRUPT_HANDLER_CALLABLE_ATTRIBUTES ALO_USED void alo_exception_handler_common(const alo_interrupt_frame_t* frame) {
    gen_log_formatted(GEN_LOG_LEVEL_DEBUG, "alonira-exception", "Exception %uz occurred at %p - error code: %uz || ", frame->vector, (void*) frame->rip, frame->error_code);
    if(frame->vector) alo_hang();
}

gen_error_t* alo_exceptions_populate_idt(void) {
	GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) alo_exceptions_populate_idt, GEN_FILE_NAME);
	if(error) return error;

    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_DIVIDE_BY_ZERO] = ALO_IDT_MAKE_ENTRY((uintptr_t) alo_exception_handler_divide_by_zero, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_DEBUG_TRAP] = ALO_IDT_MAKE_ENTRY((uintptr_t) alo_exception_handler_debug_trap, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_NMI] = ALO_IDT_MAKE_ENTRY((uintptr_t) alo_exception_handler_nmi, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_BREAKPOINT] = ALO_IDT_MAKE_ENTRY((uintptr_t) alo_exception_handler_breakpoint, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_OVERFLOW] = ALO_IDT_MAKE_ENTRY((uintptr_t) alo_exception_handler_overflow, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_BOUND_RANGE_EXCEEDED] = ALO_IDT_MAKE_ENTRY((uintptr_t) alo_exception_handler_bound_range_exceeded, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_INVALID_OPCODE] = ALO_IDT_MAKE_ENTRY((uintptr_t) alo_exception_handler_invalid_opcode, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_DEVICE_NOT_AVILABLE] = ALO_IDT_MAKE_ENTRY((uintptr_t) alo_exception_handler_device_not_avilable, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_DOUBLE_FAULT] = ALO_IDT_MAKE_ENTRY((uintptr_t) alo_exception_handler_double_fault, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_COPROCESSOR_SEGMENT_OVERRUN] = ALO_IDT_MAKE_ENTRY((uintptr_t) alo_exception_handler_coprocessor_segment_overrun, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_INVALID_TSS] = ALO_IDT_MAKE_ENTRY((uintptr_t) alo_exception_handler_invalid_tss, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_SEGMENT_NOT_PRESENT] = ALO_IDT_MAKE_ENTRY((uintptr_t) alo_exception_handler_segment_not_present, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_STACK_SEGMENT_FAULT] = ALO_IDT_MAKE_ENTRY((uintptr_t) alo_exception_handler_stack_segment_fault, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_GENERAL_PROTECTION_FAULT] = ALO_IDT_MAKE_ENTRY((uintptr_t) alo_exception_handler_general_protection_fault, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_PAGE_FAULT] = ALO_IDT_MAKE_ENTRY((uintptr_t) alo_exception_handler_page_fault, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED0] = ALO_IDT_MAKE_ENTRY((uintptr_t) alo_exception_handler_reserved0, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_X87_FLOATING_POINT] = ALO_IDT_MAKE_ENTRY((uintptr_t) alo_exception_handler_x87_floating_point, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_ALIGNMENT_CHECK] = ALO_IDT_MAKE_ENTRY((uintptr_t) alo_exception_handler_alignment_check, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_MACHINE_CHECK] = ALO_IDT_MAKE_ENTRY((uintptr_t) alo_exception_handler_machine_check, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_SIMD_FLOATING_POINT] = ALO_IDT_MAKE_ENTRY((uintptr_t) alo_exception_handler_simd_floating_point, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_VIRTUALIZATION] = ALO_IDT_MAKE_ENTRY((uintptr_t) alo_exception_handler_virtualization, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_CONTROL_PROTECTION] = ALO_IDT_MAKE_ENTRY((uintptr_t) alo_exception_handler_control_protection, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED1] = ALO_IDT_MAKE_ENTRY((uintptr_t) alo_exception_handler_reserved1, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED2] = ALO_IDT_MAKE_ENTRY((uintptr_t) alo_exception_handler_reserved2, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED3] = ALO_IDT_MAKE_ENTRY((uintptr_t) alo_exception_handler_reserved3, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED4] = ALO_IDT_MAKE_ENTRY((uintptr_t) alo_exception_handler_reserved4, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED5] = ALO_IDT_MAKE_ENTRY((uintptr_t) alo_exception_handler_reserved5, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED6] = ALO_IDT_MAKE_ENTRY((uintptr_t) alo_exception_handler_reserved6, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_HYPERVISOR_INJECTION] = ALO_IDT_MAKE_ENTRY((uintptr_t) alo_exception_handler_hypervisor_injection, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_VMM_COMMUNICATION] = ALO_IDT_MAKE_ENTRY((uintptr_t) alo_exception_handler_vmm_communication, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_SECURITY] = ALO_IDT_MAKE_ENTRY((uintptr_t) alo_exception_handler_security, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED7] = ALO_IDT_MAKE_ENTRY((uintptr_t) alo_exception_handler_reserved7, ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILIGE_RING0);

    return NULL;
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
static ALO_USED void alo_internal_interrupt_container(void) {
// Some of these handlers are for reserved vectors that should never actually
// be triggered but it's easier to just have the entire list here.

ALO_ASM_BLOCK(
    ALO_ASM(.extern alo_exception_handler_common)

    ALO_ASM(.global alo_exception_handler_divide_by_zero)
    ALO_ASM(alo_exception_handler_divide_by_zero:)
        ALO_ASM(pushq 0)

        ALO_ASM(pushq 32(%%rsp))

        ALO_ASM(pushq 24(%%rsp))

        ALO_ASM(pushq %%r15)
        ALO_ASM(pushq %%r14)
        ALO_ASM(pushq %%r13)
        ALO_ASM(pushq %%r12)
        ALO_ASM(pushq %%r11)
        ALO_ASM(pushq %%r10)
        ALO_ASM(pushq %%r9)
        ALO_ASM(pushq %%r8)

        ALO_ASM(pushq 120(%%rsp))
        ALO_ASM(pushq %%rbp)

        ALO_ASM(pushq %%rdi)
        ALO_ASM(pushq %%rsi)

        ALO_ASM(pushq %%rdx)
        ALO_ASM(pushq %%rcx)
        ALO_ASM(pushq %%rbx)
        ALO_ASM(pushq %%rax)

        ALO_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_DIVIDE_BY_ZERO])

        ALO_ASM(movq %%rsp, %%rdi)
        ALO_ASM(cld)
        ALO_ASM(callq alo_exception_handler_common)
        
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%rax)
        ALO_ASM(popq %%rbx)
        ALO_ASM(popq %%rcx)
        ALO_ASM(popq %%rdx)

        ALO_ASM(popq %%rsi)
        ALO_ASM(popq %%rdi)

        ALO_ASM(popq %%rbp)
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%r8)
        ALO_ASM(popq %%r9)
        ALO_ASM(popq %%r10)
        ALO_ASM(popq %%r11)
        ALO_ASM(popq %%r12)
        ALO_ASM(popq %%r13)
        ALO_ASM(popq %%r14)
        ALO_ASM(popq %%r15)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(iretq)

    ALO_ASM(.global alo_exception_handler_debug_trap)
    ALO_ASM(alo_exception_handler_debug_trap:)
        ALO_ASM(pushq 0)

        ALO_ASM(pushq 32(%%rsp))

        ALO_ASM(pushq 24(%%rsp))

        ALO_ASM(pushq %%r15)
        ALO_ASM(pushq %%r14)
        ALO_ASM(pushq %%r13)
        ALO_ASM(pushq %%r12)
        ALO_ASM(pushq %%r11)
        ALO_ASM(pushq %%r10)
        ALO_ASM(pushq %%r9)
        ALO_ASM(pushq %%r8)

        ALO_ASM(pushq 120(%%rsp))
        ALO_ASM(pushq %%rbp)

        ALO_ASM(pushq %%rdi)
        ALO_ASM(pushq %%rsi)

        ALO_ASM(pushq %%rdx)
        ALO_ASM(pushq %%rcx)
        ALO_ASM(pushq %%rbx)
        ALO_ASM(pushq %%rax)

        ALO_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_DEBUG_TRAP])

        ALO_ASM(movq %%rsp, %%rdi)
        ALO_ASM(cld)
        ALO_ASM(callq alo_exception_handler_common)
        
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%rax)
        ALO_ASM(popq %%rbx)
        ALO_ASM(popq %%rcx)
        ALO_ASM(popq %%rdx)

        ALO_ASM(popq %%rsi)
        ALO_ASM(popq %%rdi)

        ALO_ASM(popq %%rbp)
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%r8)
        ALO_ASM(popq %%r9)
        ALO_ASM(popq %%r10)
        ALO_ASM(popq %%r11)
        ALO_ASM(popq %%r12)
        ALO_ASM(popq %%r13)
        ALO_ASM(popq %%r14)
        ALO_ASM(popq %%r15)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)
        
        ALO_ASM(iretq)

    ALO_ASM(.global alo_exception_handler_nmi)
    ALO_ASM(alo_exception_handler_nmi:)
        ALO_ASM(pushq 0)

        ALO_ASM(pushq 32(%%rsp))

        ALO_ASM(pushq 24(%%rsp))

        ALO_ASM(pushq %%r15)
        ALO_ASM(pushq %%r14)
        ALO_ASM(pushq %%r13)
        ALO_ASM(pushq %%r12)
        ALO_ASM(pushq %%r11)
        ALO_ASM(pushq %%r10)
        ALO_ASM(pushq %%r9)
        ALO_ASM(pushq %%r8)

        ALO_ASM(pushq 120(%%rsp))
        ALO_ASM(pushq %%rbp)

        ALO_ASM(pushq %%rdi)
        ALO_ASM(pushq %%rsi)

        ALO_ASM(pushq %%rdx)
        ALO_ASM(pushq %%rcx)
        ALO_ASM(pushq %%rbx)
        ALO_ASM(pushq %%rax)

        ALO_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_NMI])

        ALO_ASM(movq %%rsp, %%rdi)
        ALO_ASM(cld)
        ALO_ASM(callq alo_exception_handler_common)
        
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%rax)
        ALO_ASM(popq %%rbx)
        ALO_ASM(popq %%rcx)
        ALO_ASM(popq %%rdx)

        ALO_ASM(popq %%rsi)
        ALO_ASM(popq %%rdi)

        ALO_ASM(popq %%rbp)
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%r8)
        ALO_ASM(popq %%r9)
        ALO_ASM(popq %%r10)
        ALO_ASM(popq %%r11)
        ALO_ASM(popq %%r12)
        ALO_ASM(popq %%r13)
        ALO_ASM(popq %%r14)
        ALO_ASM(popq %%r15)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)
        
        ALO_ASM(iretq)

    ALO_ASM(.global alo_exception_handler_breakpoint)
    ALO_ASM(alo_exception_handler_breakpoint:)
        ALO_ASM(pushq 0)

        ALO_ASM(pushq 32(%%rsp))

        ALO_ASM(pushq 24(%%rsp))

        ALO_ASM(pushq %%r15)
        ALO_ASM(pushq %%r14)
        ALO_ASM(pushq %%r13)
        ALO_ASM(pushq %%r12)
        ALO_ASM(pushq %%r11)
        ALO_ASM(pushq %%r10)
        ALO_ASM(pushq %%r9)
        ALO_ASM(pushq %%r8)

        ALO_ASM(pushq 120(%%rsp))
        ALO_ASM(pushq %%rbp)

        ALO_ASM(pushq %%rdi)
        ALO_ASM(pushq %%rsi)

        ALO_ASM(pushq %%rdx)
        ALO_ASM(pushq %%rcx)
        ALO_ASM(pushq %%rbx)
        ALO_ASM(pushq %%rax)

        ALO_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_BREAKPOINT])
        
        ALO_ASM(movq %%rsp, %%rdi)
        ALO_ASM(cld)
        ALO_ASM(callq alo_exception_handler_common)
        
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%rax)
        ALO_ASM(popq %%rbx)
        ALO_ASM(popq %%rcx)
        ALO_ASM(popq %%rdx)

        ALO_ASM(popq %%rsi)
        ALO_ASM(popq %%rdi)

        ALO_ASM(popq %%rbp)
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%r8)
        ALO_ASM(popq %%r9)
        ALO_ASM(popq %%r10)
        ALO_ASM(popq %%r11)
        ALO_ASM(popq %%r12)
        ALO_ASM(popq %%r13)
        ALO_ASM(popq %%r14)
        ALO_ASM(popq %%r15)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)
        
        ALO_ASM(iretq)

    ALO_ASM(.global alo_exception_handler_overflow)
    ALO_ASM(alo_exception_handler_overflow:)
        ALO_ASM(pushq 0)

        ALO_ASM(pushq 32(%%rsp))

        ALO_ASM(pushq 24(%%rsp))

        ALO_ASM(pushq %%r15)
        ALO_ASM(pushq %%r14)
        ALO_ASM(pushq %%r13)
        ALO_ASM(pushq %%r12)
        ALO_ASM(pushq %%r11)
        ALO_ASM(pushq %%r10)
        ALO_ASM(pushq %%r9)
        ALO_ASM(pushq %%r8)

        ALO_ASM(pushq 120(%%rsp))
        ALO_ASM(pushq %%rbp)

        ALO_ASM(pushq %%rdi)
        ALO_ASM(pushq %%rsi)

        ALO_ASM(pushq %%rdx)
        ALO_ASM(pushq %%rcx)
        ALO_ASM(pushq %%rbx)
        ALO_ASM(pushq %%rax)

        ALO_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_OVERFLOW])
        
        ALO_ASM(movq %%rsp, %%rdi)
        ALO_ASM(cld)
        ALO_ASM(callq alo_exception_handler_common)
        
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%rax)
        ALO_ASM(popq %%rbx)
        ALO_ASM(popq %%rcx)
        ALO_ASM(popq %%rdx)

        ALO_ASM(popq %%rsi)
        ALO_ASM(popq %%rdi)

        ALO_ASM(popq %%rbp)
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%r8)
        ALO_ASM(popq %%r9)
        ALO_ASM(popq %%r10)
        ALO_ASM(popq %%r11)
        ALO_ASM(popq %%r12)
        ALO_ASM(popq %%r13)
        ALO_ASM(popq %%r14)
        ALO_ASM(popq %%r15)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)
        
        ALO_ASM(iretq)

    ALO_ASM(.global alo_exception_handler_bound_range_exceeded)
    ALO_ASM(alo_exception_handler_bound_range_exceeded:)
        ALO_ASM(pushq 0)

        ALO_ASM(pushq 32(%%rsp))

        ALO_ASM(pushq 24(%%rsp))

        ALO_ASM(pushq %%r15)
        ALO_ASM(pushq %%r14)
        ALO_ASM(pushq %%r13)
        ALO_ASM(pushq %%r12)
        ALO_ASM(pushq %%r11)
        ALO_ASM(pushq %%r10)
        ALO_ASM(pushq %%r9)
        ALO_ASM(pushq %%r8)

        ALO_ASM(pushq 120(%%rsp))
        ALO_ASM(pushq %%rbp)

        ALO_ASM(pushq %%rdi)
        ALO_ASM(pushq %%rsi)

        ALO_ASM(pushq %%rdx)
        ALO_ASM(pushq %%rcx)
        ALO_ASM(pushq %%rbx)
        ALO_ASM(pushq %%rax)

        ALO_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_BOUND_RANGE_EXCEEDED])
        
        ALO_ASM(movq %%rsp, %%rdi)
        ALO_ASM(cld)
        ALO_ASM(callq alo_exception_handler_common)
        
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%rax)
        ALO_ASM(popq %%rbx)
        ALO_ASM(popq %%rcx)
        ALO_ASM(popq %%rdx)

        ALO_ASM(popq %%rsi)
        ALO_ASM(popq %%rdi)

        ALO_ASM(popq %%rbp)
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%r8)
        ALO_ASM(popq %%r9)
        ALO_ASM(popq %%r10)
        ALO_ASM(popq %%r11)
        ALO_ASM(popq %%r12)
        ALO_ASM(popq %%r13)
        ALO_ASM(popq %%r14)
        ALO_ASM(popq %%r15)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)
        
        ALO_ASM(iretq)

    ALO_ASM(.global alo_exception_handler_invalid_opcode)
    ALO_ASM(alo_exception_handler_invalid_opcode:)
        ALO_ASM(pushq 0)

        ALO_ASM(pushq 32(%%rsp))

        ALO_ASM(pushq 24(%%rsp))

        ALO_ASM(pushq %%r15)
        ALO_ASM(pushq %%r14)
        ALO_ASM(pushq %%r13)
        ALO_ASM(pushq %%r12)
        ALO_ASM(pushq %%r11)
        ALO_ASM(pushq %%r10)
        ALO_ASM(pushq %%r9)
        ALO_ASM(pushq %%r8)

        ALO_ASM(pushq 120(%%rsp))
        ALO_ASM(pushq %%rbp)

        ALO_ASM(pushq %%rdi)
        ALO_ASM(pushq %%rsi)

        ALO_ASM(pushq %%rdx)
        ALO_ASM(pushq %%rcx)
        ALO_ASM(pushq %%rbx)
        ALO_ASM(pushq %%rax)

        ALO_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_INVALID_OPCODE])
        
        ALO_ASM(movq %%rsp, %%rdi)
        ALO_ASM(cld)
        ALO_ASM(callq alo_exception_handler_common)
        
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%rax)
        ALO_ASM(popq %%rbx)
        ALO_ASM(popq %%rcx)
        ALO_ASM(popq %%rdx)

        ALO_ASM(popq %%rsi)
        ALO_ASM(popq %%rdi)

        ALO_ASM(popq %%rbp)
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%r8)
        ALO_ASM(popq %%r9)
        ALO_ASM(popq %%r10)
        ALO_ASM(popq %%r11)
        ALO_ASM(popq %%r12)
        ALO_ASM(popq %%r13)
        ALO_ASM(popq %%r14)
        ALO_ASM(popq %%r15)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)
        
        ALO_ASM(iretq)

    ALO_ASM(.global alo_exception_handler_device_not_avilable)
    ALO_ASM(alo_exception_handler_device_not_avilable:)
        ALO_ASM(pushq 0)

        ALO_ASM(pushq 32(%%rsp))

        ALO_ASM(pushq 24(%%rsp))

        ALO_ASM(pushq %%r15)
        ALO_ASM(pushq %%r14)
        ALO_ASM(pushq %%r13)
        ALO_ASM(pushq %%r12)
        ALO_ASM(pushq %%r11)
        ALO_ASM(pushq %%r10)
        ALO_ASM(pushq %%r9)
        ALO_ASM(pushq %%r8)

        ALO_ASM(pushq 120(%%rsp))
        ALO_ASM(pushq %%rbp)

        ALO_ASM(pushq %%rdi)
        ALO_ASM(pushq %%rsi)

        ALO_ASM(pushq %%rdx)
        ALO_ASM(pushq %%rcx)
        ALO_ASM(pushq %%rbx)
        ALO_ASM(pushq %%rax)

        ALO_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_DEVICE_NOT_AVILABLE])
        
        ALO_ASM(movq %%rsp, %%rdi)
        ALO_ASM(cld)
        ALO_ASM(callq alo_exception_handler_common)
        
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%rax)
        ALO_ASM(popq %%rbx)
        ALO_ASM(popq %%rcx)
        ALO_ASM(popq %%rdx)

        ALO_ASM(popq %%rsi)
        ALO_ASM(popq %%rdi)

        ALO_ASM(popq %%rbp)
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%r8)
        ALO_ASM(popq %%r9)
        ALO_ASM(popq %%r10)
        ALO_ASM(popq %%r11)
        ALO_ASM(popq %%r12)
        ALO_ASM(popq %%r13)
        ALO_ASM(popq %%r14)
        ALO_ASM(popq %%r15)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)
        
        ALO_ASM(iretq)

    ALO_ASM(.global alo_exception_handler_double_fault)
    ALO_ASM(alo_exception_handler_double_fault:)
        ALO_ASM(pushq 32(%%rsp))

        ALO_ASM(pushq 24(%%rsp))

        ALO_ASM(pushq %%r15)
        ALO_ASM(pushq %%r14)
        ALO_ASM(pushq %%r13)
        ALO_ASM(pushq %%r12)
        ALO_ASM(pushq %%r11)
        ALO_ASM(pushq %%r10)
        ALO_ASM(pushq %%r9)
        ALO_ASM(pushq %%r8)

        ALO_ASM(pushq 120(%%rsp))
        ALO_ASM(pushq %%rbp)

        ALO_ASM(pushq %%rdi)
        ALO_ASM(pushq %%rsi)

        ALO_ASM(pushq %%rdx)
        ALO_ASM(pushq %%rcx)
        ALO_ASM(pushq %%rbx)
        ALO_ASM(pushq %%rax)

        ALO_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_DOUBLE_FAULT])
        
        ALO_ASM(movq %%rsp, %%rdi)
        ALO_ASM(cld)
        ALO_ASM(callq alo_exception_handler_common)
        
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%rax)
        ALO_ASM(popq %%rbx)
        ALO_ASM(popq %%rcx)
        ALO_ASM(popq %%rdx)

        ALO_ASM(popq %%rsi)
        ALO_ASM(popq %%rdi)

        ALO_ASM(popq %%rbp)
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%r8)
        ALO_ASM(popq %%r9)
        ALO_ASM(popq %%r10)
        ALO_ASM(popq %%r11)
        ALO_ASM(popq %%r12)
        ALO_ASM(popq %%r13)
        ALO_ASM(popq %%r14)
        ALO_ASM(popq %%r15)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)
        
        ALO_ASM(iretq)

    ALO_ASM(.global alo_exception_handler_coprocessor_segment_overrun)
    ALO_ASM(alo_exception_handler_coprocessor_segment_overrun:)
        ALO_ASM(pushq 0)

        ALO_ASM(pushq 32(%%rsp))

        ALO_ASM(pushq 24(%%rsp))

        ALO_ASM(pushq %%r15)
        ALO_ASM(pushq %%r14)
        ALO_ASM(pushq %%r13)
        ALO_ASM(pushq %%r12)
        ALO_ASM(pushq %%r11)
        ALO_ASM(pushq %%r10)
        ALO_ASM(pushq %%r9)
        ALO_ASM(pushq %%r8)

        ALO_ASM(pushq 120(%%rsp))
        ALO_ASM(pushq %%rbp)

        ALO_ASM(pushq %%rdi)
        ALO_ASM(pushq %%rsi)

        ALO_ASM(pushq %%rdx)
        ALO_ASM(pushq %%rcx)
        ALO_ASM(pushq %%rbx)
        ALO_ASM(pushq %%rax)

        ALO_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_COPROCESSOR_SEGMENT_OVERRUN])
        
        ALO_ASM(movq %%rsp, %%rdi)
        ALO_ASM(cld)
        ALO_ASM(callq alo_exception_handler_common)
        
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%rax)
        ALO_ASM(popq %%rbx)
        ALO_ASM(popq %%rcx)
        ALO_ASM(popq %%rdx)

        ALO_ASM(popq %%rsi)
        ALO_ASM(popq %%rdi)

        ALO_ASM(popq %%rbp)
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%r8)
        ALO_ASM(popq %%r9)
        ALO_ASM(popq %%r10)
        ALO_ASM(popq %%r11)
        ALO_ASM(popq %%r12)
        ALO_ASM(popq %%r13)
        ALO_ASM(popq %%r14)
        ALO_ASM(popq %%r15)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)
        
        ALO_ASM(iretq)

    ALO_ASM(.global alo_exception_handler_invalid_tss)
    ALO_ASM(alo_exception_handler_invalid_tss:)
        ALO_ASM(pushq 32(%%rsp))

        ALO_ASM(pushq 24(%%rsp))

        ALO_ASM(pushq %%r15)
        ALO_ASM(pushq %%r14)
        ALO_ASM(pushq %%r13)
        ALO_ASM(pushq %%r12)
        ALO_ASM(pushq %%r11)
        ALO_ASM(pushq %%r10)
        ALO_ASM(pushq %%r9)
        ALO_ASM(pushq %%r8)

        ALO_ASM(pushq 120(%%rsp))
        ALO_ASM(pushq %%rbp)

        ALO_ASM(pushq %%rdi)
        ALO_ASM(pushq %%rsi)

        ALO_ASM(pushq %%rdx)
        ALO_ASM(pushq %%rcx)
        ALO_ASM(pushq %%rbx)
        ALO_ASM(pushq %%rax)

        ALO_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_INVALID_TSS])
        
        ALO_ASM(movq %%rsp, %%rdi)
        ALO_ASM(cld)
        ALO_ASM(callq alo_exception_handler_common)
        
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%rax)
        ALO_ASM(popq %%rbx)
        ALO_ASM(popq %%rcx)
        ALO_ASM(popq %%rdx)

        ALO_ASM(popq %%rsi)
        ALO_ASM(popq %%rdi)

        ALO_ASM(popq %%rbp)
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%r8)
        ALO_ASM(popq %%r9)
        ALO_ASM(popq %%r10)
        ALO_ASM(popq %%r11)
        ALO_ASM(popq %%r12)
        ALO_ASM(popq %%r13)
        ALO_ASM(popq %%r14)
        ALO_ASM(popq %%r15)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)
        
        ALO_ASM(iretq)

    ALO_ASM(.global alo_exception_handler_segment_not_present)
    ALO_ASM(alo_exception_handler_segment_not_present:)
        ALO_ASM(pushq 32(%%rsp))

        ALO_ASM(pushq 24(%%rsp))

        ALO_ASM(pushq %%r15)
        ALO_ASM(pushq %%r14)
        ALO_ASM(pushq %%r13)
        ALO_ASM(pushq %%r12)
        ALO_ASM(pushq %%r11)
        ALO_ASM(pushq %%r10)
        ALO_ASM(pushq %%r9)
        ALO_ASM(pushq %%r8)

        ALO_ASM(pushq 120(%%rsp))
        ALO_ASM(pushq %%rbp)

        ALO_ASM(pushq %%rdi)
        ALO_ASM(pushq %%rsi)

        ALO_ASM(pushq %%rdx)
        ALO_ASM(pushq %%rcx)
        ALO_ASM(pushq %%rbx)
        ALO_ASM(pushq %%rax)

        ALO_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_SEGMENT_NOT_PRESENT])
        
        ALO_ASM(movq %%rsp, %%rdi)
        ALO_ASM(cld)
        ALO_ASM(callq alo_exception_handler_common)
        
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%rax)
        ALO_ASM(popq %%rbx)
        ALO_ASM(popq %%rcx)
        ALO_ASM(popq %%rdx)

        ALO_ASM(popq %%rsi)
        ALO_ASM(popq %%rdi)

        ALO_ASM(popq %%rbp)
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%r8)
        ALO_ASM(popq %%r9)
        ALO_ASM(popq %%r10)
        ALO_ASM(popq %%r11)
        ALO_ASM(popq %%r12)
        ALO_ASM(popq %%r13)
        ALO_ASM(popq %%r14)
        ALO_ASM(popq %%r15)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)
        
        ALO_ASM(iretq)

    ALO_ASM(.global alo_exception_handler_stack_segment_fault)
    ALO_ASM(alo_exception_handler_stack_segment_fault:)
        ALO_ASM(pushq 32(%%rsp))

        ALO_ASM(pushq 24(%%rsp))

        ALO_ASM(pushq %%r15)
        ALO_ASM(pushq %%r14)
        ALO_ASM(pushq %%r13)
        ALO_ASM(pushq %%r12)
        ALO_ASM(pushq %%r11)
        ALO_ASM(pushq %%r10)
        ALO_ASM(pushq %%r9)
        ALO_ASM(pushq %%r8)

        ALO_ASM(pushq 120(%%rsp))
        ALO_ASM(pushq %%rbp)

        ALO_ASM(pushq %%rdi)
        ALO_ASM(pushq %%rsi)

        ALO_ASM(pushq %%rdx)
        ALO_ASM(pushq %%rcx)
        ALO_ASM(pushq %%rbx)
        ALO_ASM(pushq %%rax)

        ALO_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_STACK_SEGMENT_FAULT])
        
        ALO_ASM(movq %%rsp, %%rdi)
        ALO_ASM(cld)
        ALO_ASM(callq alo_exception_handler_common)
        
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%rax)
        ALO_ASM(popq %%rbx)
        ALO_ASM(popq %%rcx)
        ALO_ASM(popq %%rdx)

        ALO_ASM(popq %%rsi)
        ALO_ASM(popq %%rdi)

        ALO_ASM(popq %%rbp)
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%r8)
        ALO_ASM(popq %%r9)
        ALO_ASM(popq %%r10)
        ALO_ASM(popq %%r11)
        ALO_ASM(popq %%r12)
        ALO_ASM(popq %%r13)
        ALO_ASM(popq %%r14)
        ALO_ASM(popq %%r15)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)
        
        ALO_ASM(iretq)

    ALO_ASM(.global alo_exception_handler_general_protection_fault)
    ALO_ASM(alo_exception_handler_general_protection_fault:)
        ALO_ASM(pushq 32(%%rsp))

        ALO_ASM(pushq 24(%%rsp))

        ALO_ASM(pushq %%r15)
        ALO_ASM(pushq %%r14)
        ALO_ASM(pushq %%r13)
        ALO_ASM(pushq %%r12)
        ALO_ASM(pushq %%r11)
        ALO_ASM(pushq %%r10)
        ALO_ASM(pushq %%r9)
        ALO_ASM(pushq %%r8)

        ALO_ASM(pushq 120(%%rsp))
        ALO_ASM(pushq %%rbp)

        ALO_ASM(pushq %%rdi)
        ALO_ASM(pushq %%rsi)

        ALO_ASM(pushq %%rdx)
        ALO_ASM(pushq %%rcx)
        ALO_ASM(pushq %%rbx)
        ALO_ASM(pushq %%rax)

        ALO_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_GENERAL_PROTECTION_FAULT])
        
        ALO_ASM(movq %%rsp, %%rdi)
        ALO_ASM(cld)
        ALO_ASM(callq alo_exception_handler_common)
        
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%rax)
        ALO_ASM(popq %%rbx)
        ALO_ASM(popq %%rcx)
        ALO_ASM(popq %%rdx)

        ALO_ASM(popq %%rsi)
        ALO_ASM(popq %%rdi)

        ALO_ASM(popq %%rbp)
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%r8)
        ALO_ASM(popq %%r9)
        ALO_ASM(popq %%r10)
        ALO_ASM(popq %%r11)
        ALO_ASM(popq %%r12)
        ALO_ASM(popq %%r13)
        ALO_ASM(popq %%r14)
        ALO_ASM(popq %%r15)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)
        
        ALO_ASM(iretq)

    ALO_ASM(.global alo_exception_handler_page_fault)
    ALO_ASM(alo_exception_handler_page_fault:)
        ALO_ASM(pushq 32(%%rsp))

        ALO_ASM(pushq 24(%%rsp))

        ALO_ASM(pushq %%r15)
        ALO_ASM(pushq %%r14)
        ALO_ASM(pushq %%r13)
        ALO_ASM(pushq %%r12)
        ALO_ASM(pushq %%r11)
        ALO_ASM(pushq %%r10)
        ALO_ASM(pushq %%r9)
        ALO_ASM(pushq %%r8)

        ALO_ASM(pushq 120(%%rsp))
        ALO_ASM(pushq %%rbp)

        ALO_ASM(pushq %%rdi)
        ALO_ASM(pushq %%rsi)

        ALO_ASM(pushq %%rdx)
        ALO_ASM(pushq %%rcx)
        ALO_ASM(pushq %%rbx)
        ALO_ASM(pushq %%rax)

        ALO_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_PAGE_FAULT])
        
        ALO_ASM(movq %%rsp, %%rdi)
        ALO_ASM(cld)
        ALO_ASM(callq alo_exception_handler_common)
        
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%rax)
        ALO_ASM(popq %%rbx)
        ALO_ASM(popq %%rcx)
        ALO_ASM(popq %%rdx)

        ALO_ASM(popq %%rsi)
        ALO_ASM(popq %%rdi)

        ALO_ASM(popq %%rbp)
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%r8)
        ALO_ASM(popq %%r9)
        ALO_ASM(popq %%r10)
        ALO_ASM(popq %%r11)
        ALO_ASM(popq %%r12)
        ALO_ASM(popq %%r13)
        ALO_ASM(popq %%r14)
        ALO_ASM(popq %%r15)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)
        
        ALO_ASM(iretq)

    ALO_ASM(.global alo_exception_handler_reserved0)
    ALO_ASM(alo_exception_handler_reserved0:)
        ALO_ASM(pushq 0)

        ALO_ASM(pushq 32(%%rsp))

        ALO_ASM(pushq 24(%%rsp))

        ALO_ASM(pushq %%r15)
        ALO_ASM(pushq %%r14)
        ALO_ASM(pushq %%r13)
        ALO_ASM(pushq %%r12)
        ALO_ASM(pushq %%r11)
        ALO_ASM(pushq %%r10)
        ALO_ASM(pushq %%r9)
        ALO_ASM(pushq %%r8)

        ALO_ASM(pushq 120(%%rsp))
        ALO_ASM(pushq %%rbp)

        ALO_ASM(pushq %%rdi)
        ALO_ASM(pushq %%rsi)

        ALO_ASM(pushq %%rdx)
        ALO_ASM(pushq %%rcx)
        ALO_ASM(pushq %%rbx)
        ALO_ASM(pushq %%rax)

        ALO_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED0])
        
        ALO_ASM(movq %%rsp, %%rdi)
        ALO_ASM(cld)
        ALO_ASM(callq alo_exception_handler_common)
        
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%rax)
        ALO_ASM(popq %%rbx)
        ALO_ASM(popq %%rcx)
        ALO_ASM(popq %%rdx)

        ALO_ASM(popq %%rsi)
        ALO_ASM(popq %%rdi)

        ALO_ASM(popq %%rbp)
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%r8)
        ALO_ASM(popq %%r9)
        ALO_ASM(popq %%r10)
        ALO_ASM(popq %%r11)
        ALO_ASM(popq %%r12)
        ALO_ASM(popq %%r13)
        ALO_ASM(popq %%r14)
        ALO_ASM(popq %%r15)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)
        
        ALO_ASM(iretq)

    ALO_ASM(.global alo_exception_handler_x87_floating_point)
    ALO_ASM(alo_exception_handler_x87_floating_point:)
        ALO_ASM(pushq 0)

        ALO_ASM(pushq 32(%%rsp))

        ALO_ASM(pushq 24(%%rsp))

        ALO_ASM(pushq %%r15)
        ALO_ASM(pushq %%r14)
        ALO_ASM(pushq %%r13)
        ALO_ASM(pushq %%r12)
        ALO_ASM(pushq %%r11)
        ALO_ASM(pushq %%r10)
        ALO_ASM(pushq %%r9)
        ALO_ASM(pushq %%r8)

        ALO_ASM(pushq 120(%%rsp))
        ALO_ASM(pushq %%rbp)

        ALO_ASM(pushq %%rdi)
        ALO_ASM(pushq %%rsi)

        ALO_ASM(pushq %%rdx)
        ALO_ASM(pushq %%rcx)
        ALO_ASM(pushq %%rbx)
        ALO_ASM(pushq %%rax)

        ALO_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_X87_FLOATING_POINT])
        
        ALO_ASM(movq %%rsp, %%rdi)
        ALO_ASM(cld)
        ALO_ASM(callq alo_exception_handler_common)
        
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%rax)
        ALO_ASM(popq %%rbx)
        ALO_ASM(popq %%rcx)
        ALO_ASM(popq %%rdx)

        ALO_ASM(popq %%rsi)
        ALO_ASM(popq %%rdi)

        ALO_ASM(popq %%rbp)
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%r8)
        ALO_ASM(popq %%r9)
        ALO_ASM(popq %%r10)
        ALO_ASM(popq %%r11)
        ALO_ASM(popq %%r12)
        ALO_ASM(popq %%r13)
        ALO_ASM(popq %%r14)
        ALO_ASM(popq %%r15)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)
        
        ALO_ASM(iretq)

    ALO_ASM(.global alo_exception_handler_alignment_check)
    ALO_ASM(alo_exception_handler_alignment_check:)
        ALO_ASM(pushq 32(%%rsp))

        ALO_ASM(pushq 24(%%rsp))

        ALO_ASM(pushq %%r15)
        ALO_ASM(pushq %%r14)
        ALO_ASM(pushq %%r13)
        ALO_ASM(pushq %%r12)
        ALO_ASM(pushq %%r11)
        ALO_ASM(pushq %%r10)
        ALO_ASM(pushq %%r9)
        ALO_ASM(pushq %%r8)

        ALO_ASM(pushq 120(%%rsp))
        ALO_ASM(pushq %%rbp)

        ALO_ASM(pushq %%rdi)
        ALO_ASM(pushq %%rsi)

        ALO_ASM(pushq %%rdx)
        ALO_ASM(pushq %%rcx)
        ALO_ASM(pushq %%rbx)
        ALO_ASM(pushq %%rax)

        ALO_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_ALIGNMENT_CHECK])
        
        ALO_ASM(movq %%rsp, %%rdi)
        ALO_ASM(cld)
        ALO_ASM(callq alo_exception_handler_common)
        
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%rax)
        ALO_ASM(popq %%rbx)
        ALO_ASM(popq %%rcx)
        ALO_ASM(popq %%rdx)

        ALO_ASM(popq %%rsi)
        ALO_ASM(popq %%rdi)

        ALO_ASM(popq %%rbp)
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%r8)
        ALO_ASM(popq %%r9)
        ALO_ASM(popq %%r10)
        ALO_ASM(popq %%r11)
        ALO_ASM(popq %%r12)
        ALO_ASM(popq %%r13)
        ALO_ASM(popq %%r14)
        ALO_ASM(popq %%r15)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)
        
        ALO_ASM(iretq)

    ALO_ASM(.global alo_exception_handler_machine_check)
    ALO_ASM(alo_exception_handler_machine_check:)
        ALO_ASM(pushq 0)

        ALO_ASM(pushq 32(%%rsp))

        ALO_ASM(pushq 24(%%rsp))

        ALO_ASM(pushq %%r15)
        ALO_ASM(pushq %%r14)
        ALO_ASM(pushq %%r13)
        ALO_ASM(pushq %%r12)
        ALO_ASM(pushq %%r11)
        ALO_ASM(pushq %%r10)
        ALO_ASM(pushq %%r9)
        ALO_ASM(pushq %%r8)

        ALO_ASM(pushq 120(%%rsp))
        ALO_ASM(pushq %%rbp)

        ALO_ASM(pushq %%rdi)
        ALO_ASM(pushq %%rsi)

        ALO_ASM(pushq %%rdx)
        ALO_ASM(pushq %%rcx)
        ALO_ASM(pushq %%rbx)
        ALO_ASM(pushq %%rax)

        ALO_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_MACHINE_CHECK])
        
        ALO_ASM(movq %%rsp, %%rdi)
        ALO_ASM(cld)
        ALO_ASM(callq alo_exception_handler_common)
        
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%rax)
        ALO_ASM(popq %%rbx)
        ALO_ASM(popq %%rcx)
        ALO_ASM(popq %%rdx)

        ALO_ASM(popq %%rsi)
        ALO_ASM(popq %%rdi)

        ALO_ASM(popq %%rbp)
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%r8)
        ALO_ASM(popq %%r9)
        ALO_ASM(popq %%r10)
        ALO_ASM(popq %%r11)
        ALO_ASM(popq %%r12)
        ALO_ASM(popq %%r13)
        ALO_ASM(popq %%r14)
        ALO_ASM(popq %%r15)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)
        
        ALO_ASM(iretq)

    ALO_ASM(.global alo_exception_handler_simd_floating_point)
    ALO_ASM(alo_exception_handler_simd_floating_point:)
        ALO_ASM(pushq 0)

        ALO_ASM(pushq 32(%%rsp))

        ALO_ASM(pushq 24(%%rsp))

        ALO_ASM(pushq %%r15)
        ALO_ASM(pushq %%r14)
        ALO_ASM(pushq %%r13)
        ALO_ASM(pushq %%r12)
        ALO_ASM(pushq %%r11)
        ALO_ASM(pushq %%r10)
        ALO_ASM(pushq %%r9)
        ALO_ASM(pushq %%r8)

        ALO_ASM(pushq 120(%%rsp))
        ALO_ASM(pushq %%rbp)

        ALO_ASM(pushq %%rdi)
        ALO_ASM(pushq %%rsi)

        ALO_ASM(pushq %%rdx)
        ALO_ASM(pushq %%rcx)
        ALO_ASM(pushq %%rbx)
        ALO_ASM(pushq %%rax)

        ALO_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_SIMD_FLOATING_POINT])
        
        ALO_ASM(movq %%rsp, %%rdi)
        ALO_ASM(cld)
        ALO_ASM(callq alo_exception_handler_common)
        
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%rax)
        ALO_ASM(popq %%rbx)
        ALO_ASM(popq %%rcx)
        ALO_ASM(popq %%rdx)

        ALO_ASM(popq %%rsi)
        ALO_ASM(popq %%rdi)

        ALO_ASM(popq %%rbp)
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%r8)
        ALO_ASM(popq %%r9)
        ALO_ASM(popq %%r10)
        ALO_ASM(popq %%r11)
        ALO_ASM(popq %%r12)
        ALO_ASM(popq %%r13)
        ALO_ASM(popq %%r14)
        ALO_ASM(popq %%r15)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)
        
        ALO_ASM(iretq)

    ALO_ASM(.global alo_exception_handler_virtualization)
    ALO_ASM(alo_exception_handler_virtualization:)
        ALO_ASM(pushq 0)

        ALO_ASM(pushq 32(%%rsp))

        ALO_ASM(pushq 24(%%rsp))

        ALO_ASM(pushq %%r15)
        ALO_ASM(pushq %%r14)
        ALO_ASM(pushq %%r13)
        ALO_ASM(pushq %%r12)
        ALO_ASM(pushq %%r11)
        ALO_ASM(pushq %%r10)
        ALO_ASM(pushq %%r9)
        ALO_ASM(pushq %%r8)

        ALO_ASM(pushq 120(%%rsp))
        ALO_ASM(pushq %%rbp)

        ALO_ASM(pushq %%rdi)
        ALO_ASM(pushq %%rsi)

        ALO_ASM(pushq %%rdx)
        ALO_ASM(pushq %%rcx)
        ALO_ASM(pushq %%rbx)
        ALO_ASM(pushq %%rax)

        ALO_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_VIRTUALIZATION])
        
        ALO_ASM(movq %%rsp, %%rdi)
        ALO_ASM(cld)
        ALO_ASM(callq alo_exception_handler_common)
        
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%rax)
        ALO_ASM(popq %%rbx)
        ALO_ASM(popq %%rcx)
        ALO_ASM(popq %%rdx)

        ALO_ASM(popq %%rsi)
        ALO_ASM(popq %%rdi)

        ALO_ASM(popq %%rbp)
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%r8)
        ALO_ASM(popq %%r9)
        ALO_ASM(popq %%r10)
        ALO_ASM(popq %%r11)
        ALO_ASM(popq %%r12)
        ALO_ASM(popq %%r13)
        ALO_ASM(popq %%r14)
        ALO_ASM(popq %%r15)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)
        
        ALO_ASM(iretq)

    ALO_ASM(.global alo_exception_handler_control_protection)
    ALO_ASM(alo_exception_handler_control_protection:)
        ALO_ASM(pushq 32(%%rsp))

        ALO_ASM(pushq 24(%%rsp))

        ALO_ASM(pushq %%r15)
        ALO_ASM(pushq %%r14)
        ALO_ASM(pushq %%r13)
        ALO_ASM(pushq %%r12)
        ALO_ASM(pushq %%r11)
        ALO_ASM(pushq %%r10)
        ALO_ASM(pushq %%r9)
        ALO_ASM(pushq %%r8)

        ALO_ASM(pushq 120(%%rsp))
        ALO_ASM(pushq %%rbp)

        ALO_ASM(pushq %%rdi)
        ALO_ASM(pushq %%rsi)

        ALO_ASM(pushq %%rdx)
        ALO_ASM(pushq %%rcx)
        ALO_ASM(pushq %%rbx)
        ALO_ASM(pushq %%rax)

        ALO_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_CONTROL_PROTECTION])
        
        ALO_ASM(movq %%rsp, %%rdi)
        ALO_ASM(cld)
        ALO_ASM(callq alo_exception_handler_common)
        
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%rax)
        ALO_ASM(popq %%rbx)
        ALO_ASM(popq %%rcx)
        ALO_ASM(popq %%rdx)

        ALO_ASM(popq %%rsi)
        ALO_ASM(popq %%rdi)

        ALO_ASM(popq %%rbp)
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%r8)
        ALO_ASM(popq %%r9)
        ALO_ASM(popq %%r10)
        ALO_ASM(popq %%r11)
        ALO_ASM(popq %%r12)
        ALO_ASM(popq %%r13)
        ALO_ASM(popq %%r14)
        ALO_ASM(popq %%r15)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)
        
        ALO_ASM(iretq)

    ALO_ASM(.global alo_exception_handler_reserved1)
    ALO_ASM(alo_exception_handler_reserved1:)
        ALO_ASM(pushq 0)

        ALO_ASM(pushq 32(%%rsp))

        ALO_ASM(pushq 24(%%rsp))

        ALO_ASM(pushq %%r15)
        ALO_ASM(pushq %%r14)
        ALO_ASM(pushq %%r13)
        ALO_ASM(pushq %%r12)
        ALO_ASM(pushq %%r11)
        ALO_ASM(pushq %%r10)
        ALO_ASM(pushq %%r9)
        ALO_ASM(pushq %%r8)

        ALO_ASM(pushq 120(%%rsp))
        ALO_ASM(pushq %%rbp)

        ALO_ASM(pushq %%rdi)
        ALO_ASM(pushq %%rsi)

        ALO_ASM(pushq %%rdx)
        ALO_ASM(pushq %%rcx)
        ALO_ASM(pushq %%rbx)
        ALO_ASM(pushq %%rax)

        ALO_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED1])
        
        ALO_ASM(movq %%rsp, %%rdi)
        ALO_ASM(cld)
        ALO_ASM(callq alo_exception_handler_common)
        
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%rax)
        ALO_ASM(popq %%rbx)
        ALO_ASM(popq %%rcx)
        ALO_ASM(popq %%rdx)

        ALO_ASM(popq %%rsi)
        ALO_ASM(popq %%rdi)

        ALO_ASM(popq %%rbp)
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%r8)
        ALO_ASM(popq %%r9)
        ALO_ASM(popq %%r10)
        ALO_ASM(popq %%r11)
        ALO_ASM(popq %%r12)
        ALO_ASM(popq %%r13)
        ALO_ASM(popq %%r14)
        ALO_ASM(popq %%r15)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)
        
        ALO_ASM(iretq)

    ALO_ASM(.global alo_exception_handler_reserved2)
    ALO_ASM(alo_exception_handler_reserved2:)
        ALO_ASM(pushq 0)

        ALO_ASM(pushq 32(%%rsp))

        ALO_ASM(pushq 24(%%rsp))

        ALO_ASM(pushq %%r15)
        ALO_ASM(pushq %%r14)
        ALO_ASM(pushq %%r13)
        ALO_ASM(pushq %%r12)
        ALO_ASM(pushq %%r11)
        ALO_ASM(pushq %%r10)
        ALO_ASM(pushq %%r9)
        ALO_ASM(pushq %%r8)

        ALO_ASM(pushq 120(%%rsp))
        ALO_ASM(pushq %%rbp)

        ALO_ASM(pushq %%rdi)
        ALO_ASM(pushq %%rsi)

        ALO_ASM(pushq %%rdx)
        ALO_ASM(pushq %%rcx)
        ALO_ASM(pushq %%rbx)
        ALO_ASM(pushq %%rax)

        ALO_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED2])
        
        ALO_ASM(movq %%rsp, %%rdi)
        ALO_ASM(cld)
        ALO_ASM(callq alo_exception_handler_common)
        
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%rax)
        ALO_ASM(popq %%rbx)
        ALO_ASM(popq %%rcx)
        ALO_ASM(popq %%rdx)

        ALO_ASM(popq %%rsi)
        ALO_ASM(popq %%rdi)

        ALO_ASM(popq %%rbp)
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%r8)
        ALO_ASM(popq %%r9)
        ALO_ASM(popq %%r10)
        ALO_ASM(popq %%r11)
        ALO_ASM(popq %%r12)
        ALO_ASM(popq %%r13)
        ALO_ASM(popq %%r14)
        ALO_ASM(popq %%r15)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)
        
        ALO_ASM(iretq)

    ALO_ASM(.global alo_exception_handler_reserved3)
    ALO_ASM(alo_exception_handler_reserved3:)
        ALO_ASM(pushq 0)

        ALO_ASM(pushq 32(%%rsp))

        ALO_ASM(pushq 24(%%rsp))

        ALO_ASM(pushq %%r15)
        ALO_ASM(pushq %%r14)
        ALO_ASM(pushq %%r13)
        ALO_ASM(pushq %%r12)
        ALO_ASM(pushq %%r11)
        ALO_ASM(pushq %%r10)
        ALO_ASM(pushq %%r9)
        ALO_ASM(pushq %%r8)

        ALO_ASM(pushq 120(%%rsp))
        ALO_ASM(pushq %%rbp)

        ALO_ASM(pushq %%rdi)
        ALO_ASM(pushq %%rsi)

        ALO_ASM(pushq %%rdx)
        ALO_ASM(pushq %%rcx)
        ALO_ASM(pushq %%rbx)
        ALO_ASM(pushq %%rax)

        ALO_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED3])
        
        ALO_ASM(movq %%rsp, %%rdi)
        ALO_ASM(cld)
        ALO_ASM(callq alo_exception_handler_common)
        
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%rax)
        ALO_ASM(popq %%rbx)
        ALO_ASM(popq %%rcx)
        ALO_ASM(popq %%rdx)

        ALO_ASM(popq %%rsi)
        ALO_ASM(popq %%rdi)

        ALO_ASM(popq %%rbp)
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%r8)
        ALO_ASM(popq %%r9)
        ALO_ASM(popq %%r10)
        ALO_ASM(popq %%r11)
        ALO_ASM(popq %%r12)
        ALO_ASM(popq %%r13)
        ALO_ASM(popq %%r14)
        ALO_ASM(popq %%r15)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)
        
        ALO_ASM(iretq)

    ALO_ASM(.global alo_exception_handler_reserved4)
    ALO_ASM(alo_exception_handler_reserved4:)
        ALO_ASM(pushq 0)

        ALO_ASM(pushq 32(%%rsp))

        ALO_ASM(pushq 24(%%rsp))

        ALO_ASM(pushq %%r15)
        ALO_ASM(pushq %%r14)
        ALO_ASM(pushq %%r13)
        ALO_ASM(pushq %%r12)
        ALO_ASM(pushq %%r11)
        ALO_ASM(pushq %%r10)
        ALO_ASM(pushq %%r9)
        ALO_ASM(pushq %%r8)

        ALO_ASM(pushq 120(%%rsp))
        ALO_ASM(pushq %%rbp)

        ALO_ASM(pushq %%rdi)
        ALO_ASM(pushq %%rsi)

        ALO_ASM(pushq %%rdx)
        ALO_ASM(pushq %%rcx)
        ALO_ASM(pushq %%rbx)
        ALO_ASM(pushq %%rax)

        ALO_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED4])
        
        ALO_ASM(movq %%rsp, %%rdi)
        ALO_ASM(cld)
        ALO_ASM(callq alo_exception_handler_common)
        
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%rax)
        ALO_ASM(popq %%rbx)
        ALO_ASM(popq %%rcx)
        ALO_ASM(popq %%rdx)

        ALO_ASM(popq %%rsi)
        ALO_ASM(popq %%rdi)

        ALO_ASM(popq %%rbp)
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%r8)
        ALO_ASM(popq %%r9)
        ALO_ASM(popq %%r10)
        ALO_ASM(popq %%r11)
        ALO_ASM(popq %%r12)
        ALO_ASM(popq %%r13)
        ALO_ASM(popq %%r14)
        ALO_ASM(popq %%r15)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)
        
        ALO_ASM(iretq)

    ALO_ASM(.global alo_exception_handler_reserved5)
    ALO_ASM(alo_exception_handler_reserved5:)
        ALO_ASM(pushq 0)

        ALO_ASM(pushq 32(%%rsp))

        ALO_ASM(pushq 24(%%rsp))

        ALO_ASM(pushq %%r15)
        ALO_ASM(pushq %%r14)
        ALO_ASM(pushq %%r13)
        ALO_ASM(pushq %%r12)
        ALO_ASM(pushq %%r11)
        ALO_ASM(pushq %%r10)
        ALO_ASM(pushq %%r9)
        ALO_ASM(pushq %%r8)

        ALO_ASM(pushq 120(%%rsp))
        ALO_ASM(pushq %%rbp)

        ALO_ASM(pushq %%rdi)
        ALO_ASM(pushq %%rsi)

        ALO_ASM(pushq %%rdx)
        ALO_ASM(pushq %%rcx)
        ALO_ASM(pushq %%rbx)
        ALO_ASM(pushq %%rax)

        ALO_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED5])
        
        ALO_ASM(movq %%rsp, %%rdi)
        ALO_ASM(cld)
        ALO_ASM(callq alo_exception_handler_common)
        
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%rax)
        ALO_ASM(popq %%rbx)
        ALO_ASM(popq %%rcx)
        ALO_ASM(popq %%rdx)

        ALO_ASM(popq %%rsi)
        ALO_ASM(popq %%rdi)

        ALO_ASM(popq %%rbp)
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%r8)
        ALO_ASM(popq %%r9)
        ALO_ASM(popq %%r10)
        ALO_ASM(popq %%r11)
        ALO_ASM(popq %%r12)
        ALO_ASM(popq %%r13)
        ALO_ASM(popq %%r14)
        ALO_ASM(popq %%r15)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)
        
        ALO_ASM(iretq)

    ALO_ASM(.global alo_exception_handler_reserved6)
    ALO_ASM(alo_exception_handler_reserved6:)
        ALO_ASM(pushq 0)

        ALO_ASM(pushq 32(%%rsp))

        ALO_ASM(pushq 24(%%rsp))

        ALO_ASM(pushq %%r15)
        ALO_ASM(pushq %%r14)
        ALO_ASM(pushq %%r13)
        ALO_ASM(pushq %%r12)
        ALO_ASM(pushq %%r11)
        ALO_ASM(pushq %%r10)
        ALO_ASM(pushq %%r9)
        ALO_ASM(pushq %%r8)

        ALO_ASM(pushq 120(%%rsp))
        ALO_ASM(pushq %%rbp)

        ALO_ASM(pushq %%rdi)
        ALO_ASM(pushq %%rsi)

        ALO_ASM(pushq %%rdx)
        ALO_ASM(pushq %%rcx)
        ALO_ASM(pushq %%rbx)
        ALO_ASM(pushq %%rax)

        ALO_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED6])
        
        ALO_ASM(movq %%rsp, %%rdi)
        ALO_ASM(cld)
        ALO_ASM(callq alo_exception_handler_common)
        
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%rax)
        ALO_ASM(popq %%rbx)
        ALO_ASM(popq %%rcx)
        ALO_ASM(popq %%rdx)

        ALO_ASM(popq %%rsi)
        ALO_ASM(popq %%rdi)

        ALO_ASM(popq %%rbp)
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%r8)
        ALO_ASM(popq %%r9)
        ALO_ASM(popq %%r10)
        ALO_ASM(popq %%r11)
        ALO_ASM(popq %%r12)
        ALO_ASM(popq %%r13)
        ALO_ASM(popq %%r14)
        ALO_ASM(popq %%r15)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)
        
        ALO_ASM(iretq)

    ALO_ASM(.global alo_exception_handler_hypervisor_injection)
    ALO_ASM(alo_exception_handler_hypervisor_injection:)
        ALO_ASM(pushq 0)

        ALO_ASM(pushq 32(%%rsp))

        ALO_ASM(pushq 24(%%rsp))

        ALO_ASM(pushq %%r15)
        ALO_ASM(pushq %%r14)
        ALO_ASM(pushq %%r13)
        ALO_ASM(pushq %%r12)
        ALO_ASM(pushq %%r11)
        ALO_ASM(pushq %%r10)
        ALO_ASM(pushq %%r9)
        ALO_ASM(pushq %%r8)

        ALO_ASM(pushq 120(%%rsp))
        ALO_ASM(pushq %%rbp)

        ALO_ASM(pushq %%rdi)
        ALO_ASM(pushq %%rsi)

        ALO_ASM(pushq %%rdx)
        ALO_ASM(pushq %%rcx)
        ALO_ASM(pushq %%rbx)
        ALO_ASM(pushq %%rax)

        ALO_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_HYPERVISOR_INJECTION])
        
        ALO_ASM(movq %%rsp, %%rdi)
        ALO_ASM(cld)
        ALO_ASM(callq alo_exception_handler_common)
        
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%rax)
        ALO_ASM(popq %%rbx)
        ALO_ASM(popq %%rcx)
        ALO_ASM(popq %%rdx)

        ALO_ASM(popq %%rsi)
        ALO_ASM(popq %%rdi)

        ALO_ASM(popq %%rbp)
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%r8)
        ALO_ASM(popq %%r9)
        ALO_ASM(popq %%r10)
        ALO_ASM(popq %%r11)
        ALO_ASM(popq %%r12)
        ALO_ASM(popq %%r13)
        ALO_ASM(popq %%r14)
        ALO_ASM(popq %%r15)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)
        
        ALO_ASM(iretq)

    ALO_ASM(.global alo_exception_handler_vmm_communication)
    ALO_ASM(alo_exception_handler_vmm_communication:)
        ALO_ASM(pushq 32(%%rsp))

        ALO_ASM(pushq 24(%%rsp))

        ALO_ASM(pushq %%r15)
        ALO_ASM(pushq %%r14)
        ALO_ASM(pushq %%r13)
        ALO_ASM(pushq %%r12)
        ALO_ASM(pushq %%r11)
        ALO_ASM(pushq %%r10)
        ALO_ASM(pushq %%r9)
        ALO_ASM(pushq %%r8)

        ALO_ASM(pushq 120(%%rsp))
        ALO_ASM(pushq %%rbp)

        ALO_ASM(pushq %%rdi)
        ALO_ASM(pushq %%rsi)

        ALO_ASM(pushq %%rdx)
        ALO_ASM(pushq %%rcx)
        ALO_ASM(pushq %%rbx)
        ALO_ASM(pushq %%rax)

        ALO_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_VMM_COMMUNICATION])
        
        ALO_ASM(movq %%rsp, %%rdi)
        ALO_ASM(cld)
        ALO_ASM(callq alo_exception_handler_common)
        
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%rax)
        ALO_ASM(popq %%rbx)
        ALO_ASM(popq %%rcx)
        ALO_ASM(popq %%rdx)

        ALO_ASM(popq %%rsi)
        ALO_ASM(popq %%rdi)

        ALO_ASM(popq %%rbp)
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%r8)
        ALO_ASM(popq %%r9)
        ALO_ASM(popq %%r10)
        ALO_ASM(popq %%r11)
        ALO_ASM(popq %%r12)
        ALO_ASM(popq %%r13)
        ALO_ASM(popq %%r14)
        ALO_ASM(popq %%r15)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)
        
        ALO_ASM(iretq)

    ALO_ASM(.global alo_exception_handler_security)
    ALO_ASM(alo_exception_handler_security:)
        ALO_ASM(pushq 32(%%rsp))

        ALO_ASM(pushq 24(%%rsp))

        ALO_ASM(pushq %%r15)
        ALO_ASM(pushq %%r14)
        ALO_ASM(pushq %%r13)
        ALO_ASM(pushq %%r12)
        ALO_ASM(pushq %%r11)
        ALO_ASM(pushq %%r10)
        ALO_ASM(pushq %%r9)
        ALO_ASM(pushq %%r8)

        ALO_ASM(pushq 120(%%rsp))
        ALO_ASM(pushq %%rbp)

        ALO_ASM(pushq %%rdi)
        ALO_ASM(pushq %%rsi)

        ALO_ASM(pushq %%rdx)
        ALO_ASM(pushq %%rcx)
        ALO_ASM(pushq %%rbx)
        ALO_ASM(pushq %%rax)

        ALO_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_SECURITY])
        
        ALO_ASM(movq %%rsp, %%rdi)
        ALO_ASM(cld)
        ALO_ASM(callq alo_exception_handler_common)
        
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%rax)
        ALO_ASM(popq %%rbx)
        ALO_ASM(popq %%rcx)
        ALO_ASM(popq %%rdx)

        ALO_ASM(popq %%rsi)
        ALO_ASM(popq %%rdi)

        ALO_ASM(popq %%rbp)
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%r8)
        ALO_ASM(popq %%r9)
        ALO_ASM(popq %%r10)
        ALO_ASM(popq %%r11)
        ALO_ASM(popq %%r12)
        ALO_ASM(popq %%r13)
        ALO_ASM(popq %%r14)
        ALO_ASM(popq %%r15)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)
        
        ALO_ASM(iretq)

    ALO_ASM(.global alo_exception_handler_reserved7)
    ALO_ASM(alo_exception_handler_reserved7:)
        ALO_ASM(pushq 0)

        ALO_ASM(pushq 32(%%rsp))

        ALO_ASM(pushq 24(%%rsp))

        ALO_ASM(pushq %%r15)
        ALO_ASM(pushq %%r14)
        ALO_ASM(pushq %%r13)
        ALO_ASM(pushq %%r12)
        ALO_ASM(pushq %%r11)
        ALO_ASM(pushq %%r10)
        ALO_ASM(pushq %%r9)
        ALO_ASM(pushq %%r8)

        ALO_ASM(pushq 120(%%rsp))
        ALO_ASM(pushq %%rbp)

        ALO_ASM(pushq %%rdi)
        ALO_ASM(pushq %%rsi)

        ALO_ASM(pushq %%rdx)
        ALO_ASM(pushq %%rcx)
        ALO_ASM(pushq %%rbx)
        ALO_ASM(pushq %%rax)

        ALO_ASM(pushq %[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED7])
        
        ALO_ASM(movq %%rsp, %%rdi)
        ALO_ASM(cld)
        ALO_ASM(callq alo_exception_handler_common)
        
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%rax)
        ALO_ASM(popq %%rbx)
        ALO_ASM(popq %%rcx)
        ALO_ASM(popq %%rdx)

        ALO_ASM(popq %%rsi)
        ALO_ASM(popq %%rdi)

        ALO_ASM(popq %%rbp)
        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(popq %%r8)
        ALO_ASM(popq %%r9)
        ALO_ASM(popq %%r10)
        ALO_ASM(popq %%r11)
        ALO_ASM(popq %%r12)
        ALO_ASM(popq %%r13)
        ALO_ASM(popq %%r14)
        ALO_ASM(popq %%r15)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)

        ALO_ASM(subq 8, %%rsp)
        
        ALO_ASM(iretq),

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
