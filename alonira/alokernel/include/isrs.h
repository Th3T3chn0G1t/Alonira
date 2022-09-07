// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#ifndef ALO_KERNEL_ISRS_H
#define ALO_KERNEL_ISRS_H

#include "kdiagnostic.h"
#include "cpu.h"
#include "idt.h"

/*
typedef struct ALO_PACKED {
    alo_register_t rip;

    uint64_t pad0 : 48;
    alo_segment_selector_t code_segment_selector;

    alo_flags_t rflags;

    alo_register_t rsp;

    uint64_t pad1 : 48;
    alo_segment_selector_t stack_segment_selector;
} alo_internal_isr_frame_t;

#define ALO_INTERNAL_ISR __used __interrupt static void

__callee_preserve static void alo_internal_handle_isr_common(GEN_UNUSED alo_registers_t* registers, GEN_UNUSED alo_idt_isr_t isr) {

}

#define ALO_INTERNAL_ISR_STORE_REGISTERS(registers, frame) \
    do { \
        ALO_ASM_BLOCK( \
            ALO_ASM(mov 8*0(%[registers]), rax) \
            ALO_ASM(mov 8*1(%[registers]), rbx) \
            ALO_ASM(mov 8*2(%[registers]), rcx) \
            ALO_ASM(mov 8*3(%[registers]), rdx) \
            ALO_ASM(mov 8*4(%[registers]), rsi) \
            ALO_ASM(mov 8*5(%[registers]), rdi) \
            ALO_ASM(mov 8*8(%[registers]), r8) \
            ALO_ASM(mov 8*9(%[registers]), r9) \
            ALO_ASM(mov 8*10(%[registers]), r10) \
            ALO_ASM(mov 8*11(%[registers]), r11) \
            ALO_ASM(mov 8*12(%[registers]), r12) \
            ALO_ASM(mov 8*13(%[registers]), r13) \
            ALO_ASM(mov 8*14(%[registers]), r14) \
            ALO_ASM(mov 8*15(%[registers]), r15) \
            ALO_ASM(mov 8*16(%[registers]), rip), \
        :: [registers]"p"(registers)); \
        registers.rbp = __builtin_frame_address(1); \
        registers.rsp = frame->rsp; \
        registers.rflags = frame->rflags; \
    } while(0)

#define ALO_INTERNAL_ISR_DEFINE(index) \
    ALO_INTERNAL_ISR alo_internal_##index##_isr(alo_internal_isr_frame_t* frame) { \
        alo_registers_t registers; \
        ALO_INTERNAL_ISR_STORE_REGISTERS(registers, frame); \
        alo_internal_handle_isr_common(&registers, index); \
    }

#define ALO_INTERNAL_EXCEPTION_ISR_SIGNATURE(index) alo_internal_##index##_isr(alo_internal_isr_frame_t* frame, uint64_t error_code)

ALO_INTERNAL_ISR ALO_INTERNAL_EXCEPTION_ISR_SIGNATURE(ALO_IDT_ENTRY_EXCEPTION_DIVIDE_BY_ZERO) {
    panic_with_registers(ALO_, "Recieved exception ISR", registers);
}

ALO_INTERNAL_ISR ALO_INTERNAL_EXCEPTION_ISR_SIGNATURE(ALO_IDT_ENTRY_EXCEPTION_DEBUG_TRAP) {
    panic_with_registers(ALO_, "Recieved exception ISR", registers);
}

ALO_INTERNAL_ISR ALO_INTERNAL_EXCEPTION_ISR_SIGNATURE(ALO_IDT_ENTRY_EXCEPTION_NMI) {
    panic_with_registers(ALO_, "Recieved exception ISR", registers);
}

ALO_INTERNAL_ISR ALO_INTERNAL_EXCEPTION_ISR_SIGNATURE(ALO_IDT_ENTRY_EXCEPTION_BREAKPOINT) {
    panic_with_registers(ALO_, "Recieved exception ISR", registers);
}

ALO_INTERNAL_ISR ALO_INTERNAL_EXCEPTION_ISR_SIGNATURE(ALO_IDT_ENTRY_EXCEPTION_OVERFLOW) {
    panic_with_registers(ALO_, "Recieved exception ISR", registers);
}

ALO_INTERNAL_ISR ALO_INTERNAL_EXCEPTION_ISR_SIGNATURE(ALO_IDT_ENTRY_EXCEPTION_BOUND_RANGE_EXCEEDED) {
    panic_with_registers(ALO_, "Recieved exception ISR", registers);
}

ALO_INTERNAL_ISR ALO_INTERNAL_EXCEPTION_ISR_SIGNATURE(ALO_IDT_ENTRY_EXCEPTION_INVALID_OPCODE) {
    panic_with_registers(ALO_, "Recieved exception ISR", registers);
}

ALO_INTERNAL_ISR ALO_INTERNAL_EXCEPTION_ISR_SIGNATURE(ALO_IDT_ENTRY_EXCEPTION_DEVICE_NOT_AVILABLE) {
    panic_with_registers(ALO_, "Recieved exception ISR", registers);
}

ALO_INTERNAL_ISR ALO_INTERNAL_EXCEPTION_ISR_SIGNATURE(ALO_IDT_ENTRY_EXCEPTION_DOUBLE_FAULT) {
    panic_with_registers(ALO_, "Recieved exception ISR", registers);
}

ALO_INTERNAL_ISR ALO_INTERNAL_EXCEPTION_ISR_SIGNATURE(ALO_IDT_ENTRY_EXCEPTION_COPROCESSOR_SEGMENT_OVERRUN) {
    panic_with_registers(ALO_, "Recieved exception ISR", registers);
}

ALO_INTERNAL_ISR ALO_INTERNAL_EXCEPTION_ISR_SIGNATURE(ALO_IDT_ENTRY_EXCEPTION_INVALID_TSS) {
    panic_with_registers(ALO_, "Recieved exception ISR", registers);
}

ALO_INTERNAL_ISR ALO_INTERNAL_EXCEPTION_ISR_SIGNATURE(ALO_IDT_ENTRY_EXCEPTION_SEGMENT_NOT_PRESENT) {
    panic_with_registers(ALO_, "Recieved exception ISR", registers);
}

ALO_INTERNAL_ISR ALO_INTERNAL_EXCEPTION_ISR_SIGNATURE(ALO_IDT_ENTRY_EXCEPTION_STACK_SEGMENT_FAULT) {
    panic_with_registers(ALO_, "Recieved exception ISR", registers);
}

ALO_INTERNAL_ISR ALO_INTERNAL_EXCEPTION_ISR_SIGNATURE(ALO_IDT_ENTRY_EXCEPTION_GENERAL_PROTECTION_FAULT) {
    panic_with_registers(ALO_, "Recieved exception ISR", registers);
}

ALO_INTERNAL_ISR ALO_INTERNAL_EXCEPTION_ISR_SIGNATURE(ALO_IDT_ENTRY_EXCEPTION_PAGE_FAULT) {
    panic_with_registers(ALO_, "Recieved exception ISR", registers);
}

ALO_INTERNAL_ISR ALO_INTERNAL_EXCEPTION_ISR_SIGNATURE(ALO_IDT_ENTRY_EXCEPTION_X87_FLOATING_POINT) {
    panic_with_registers(ALO_, "Recieved exception ISR", registers);
}

ALO_INTERNAL_ISR ALO_INTERNAL_EXCEPTION_ISR_SIGNATURE(ALO_IDT_ENTRY_EXCEPTION_ALIGNMENT_CHECK) {
    panic_with_registers(ALO_, "Recieved exception ISR", registers);
}

ALO_INTERNAL_ISR ALO_INTERNAL_EXCEPTION_ISR_SIGNATURE(ALO_IDT_ENTRY_EXCEPTION_MACHINE_CHECK) {
    panic_with_registers(ALO_, "Recieved exception ISR", registers);
}

ALO_INTERNAL_ISR ALO_INTERNAL_EXCEPTION_ISR_SIGNATURE(ALO_IDT_ENTRY_EXCEPTION_SIMD_FLOATING_POINT) {
    panic_with_registers(ALO_, "Recieved exception ISR", registers);
}

ALO_INTERNAL_ISR ALO_INTERNAL_EXCEPTION_ISR_SIGNATURE(ALO_IDT_ENTRY_EXCEPTION_VIRTUALIZATION) {
    panic_with_registers(ALO_, "Recieved exception ISR", registers);
}

ALO_INTERNAL_ISR ALO_INTERNAL_EXCEPTION_ISR_SIGNATURE(ALO_IDT_ENTRY_EXCEPTION_CONTROL_PROTECTION) {
    panic_with_registers(ALO_, "Recieved exception ISR", registers);
}

ALO_INTERNAL_ISR ALO_INTERNAL_EXCEPTION_ISR_SIGNATURE(ALO_IDT_ENTRY_EXCEPTION_HYPERVISOR_INJECTION) {
    panic_with_registers(ALO_, "Recieved exception ISR", registers);
}

ALO_INTERNAL_ISR ALO_INTERNAL_EXCEPTION_ISR_SIGNATURE(ALO_IDT_ENTRY_EXCEPTION_VMM_COMMUNICATION) {
    panic_with_registers(ALO_, "Recieved exception ISR", registers);
}

ALO_INTERNAL_ISR ALO_INTERNAL_EXCEPTION_ISR_SIGNATURE(ALO_IDT_ENTRY_EXCEPTION_SECURITY) {
    panic_with_registers(ALO_, "Recieved exception ISR", registers);
}
*/


#endif
