// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include "include/idt.h"
#include "include/tss.h"

#include <gencommon.h>
#include <genlog.h>

static const char* alo_interrupts_internal_exception_names[] = {
    [ALO_INTERRUPT_VECTOR_EXCEPTION_DIVIDE_BY_ZERO              ] = "divide by zero"              ,
    [ALO_INTERRUPT_VECTOR_EXCEPTION_DEBUG_TRAP                  ] = "debug trap"                  ,
    [ALO_INTERRUPT_VECTOR_EXCEPTION_NMI                         ] = "nmi"                         ,
    [ALO_INTERRUPT_VECTOR_EXCEPTION_BREAKPOINT                  ] = "breakpoint"                  ,
    [ALO_INTERRUPT_VECTOR_EXCEPTION_OVERFLOW                    ] = "overflow"                    ,
    [ALO_INTERRUPT_VECTOR_EXCEPTION_BOUND_RANGE_EXCEEDED        ] = "bound range exceeded"        ,
    [ALO_INTERRUPT_VECTOR_EXCEPTION_INVALID_OPCODE              ] = "invalid opcode"              ,
    [ALO_INTERRUPT_VECTOR_EXCEPTION_DEVICE_NOT_AVILABLE         ] = "device not avilable"         ,
    [ALO_INTERRUPT_VECTOR_EXCEPTION_DOUBLE_FAULT                ] = "double fault"                ,
    [ALO_INTERRUPT_VECTOR_EXCEPTION_COPROCESSOR_SEGMENT_OVERRUN ] = "coprocessor segment overrun" ,
    [ALO_INTERRUPT_VECTOR_EXCEPTION_INVALID_TSS                 ] = "invalid tss"                 ,
    [ALO_INTERRUPT_VECTOR_EXCEPTION_SEGMENT_NOT_PRESENT         ] = "segment not present"         ,
    [ALO_INTERRUPT_VECTOR_EXCEPTION_STACK_SEGMENT_FAULT         ] = "stack segment fault"         ,
    [ALO_INTERRUPT_VECTOR_EXCEPTION_GENERAL_PROTECTION_FAULT    ] = "general protection fault"    ,
    [ALO_INTERRUPT_VECTOR_EXCEPTION_PAGE_FAULT                  ] = "page fault"                  ,
    [ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED0                   ] = "reserved0"                   ,
    [ALO_INTERRUPT_VECTOR_EXCEPTION_X87_FLOATING_POINT          ] = "x87 floating point"          ,
    [ALO_INTERRUPT_VECTOR_EXCEPTION_ALIGNMENT_CHECK             ] = "alignment check"             ,
    [ALO_INTERRUPT_VECTOR_EXCEPTION_MACHINE_CHECK               ] = "machine check"               ,
    [ALO_INTERRUPT_VECTOR_EXCEPTION_SIMD_FLOATING_POINT         ] = "simd floating point"         ,
    [ALO_INTERRUPT_VECTOR_EXCEPTION_VIRTUALIZATION              ] = "virtualization"              ,
    [ALO_INTERRUPT_VECTOR_EXCEPTION_CONTROL_PROTECTION          ] = "control protection"          ,
    [ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED1                   ] = "reserved1"                   ,
    [ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED2                   ] = "reserved2"                   ,
    [ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED3                   ] = "reserved3"                   ,
    [ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED4                   ] = "reserved4"                   ,
    [ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED5                   ] = "reserved5"                   ,
    [ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED6                   ] = "reserved6"                   ,
    [ALO_INTERRUPT_VECTOR_EXCEPTION_HYPERVISOR_INJECTION        ] = "hypervisor injection"        ,
    [ALO_INTERRUPT_VECTOR_EXCEPTION_VMM_COMMUNICATION           ] = "vmm communication"           ,
    [ALO_INTERRUPT_VECTOR_EXCEPTION_SECURITY                    ] = "security"                    ,
    [ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED7                   ] = "reserved7"
};

// NOTE: Please never ever modify this from the exception stub.
GEN_THREAD_LOCAL static alo_exception_frame_t alo_interrupts_internal_exception_frame;

ALO_INTERRUPT_HANDLER_CALLABLE_ATTRIBUTES extern void alo_interrupts_internal_exception_stub(void);
ALO_INTERRUPT_HANDLER_CALLABLE_ATTRIBUTES GEN_USED void alo_interrupts_internal_exception_stub(void) {
    // TODO: Abort with error on error.
    (void) gen_log_formatted(GEN_LOG_LEVEL_DEBUG, "alonira-interrupt", "Exception: `%t` @ %p", alo_interrupts_internal_exception_names[alo_interrupts_internal_exception_frame.vector], alo_interrupts_internal_exception_frame.registers.rip);
    (void) gen_log_formatted(GEN_LOG_LEVEL_DEBUG, "alonira-interrupt", "ss: %p cs: %p", (alo_register_t) alo_interrupts_internal_exception_frame.ss.ss.selector, (alo_register_t) alo_interrupts_internal_exception_frame.cs.cs.selector);
    (void) gen_log_formatted(GEN_LOG_LEVEL_DEBUG, "alonira-interrupt", "rax: %p rbx: %p rcx: %p rdx: %p rsi: %p rdi: %p rbp: %p rsp: %p r8: %p r9: %p r10: %p r11: %p r12: %p r13: %p r14: %p r15: %p rfl: %p", alo_interrupts_internal_exception_frame.registers.rax, alo_interrupts_internal_exception_frame.registers.rbx, alo_interrupts_internal_exception_frame.registers.rcx, alo_interrupts_internal_exception_frame.registers.rdx, alo_interrupts_internal_exception_frame.registers.rsi, alo_interrupts_internal_exception_frame.registers.rdi, alo_interrupts_internal_exception_frame.registers.rbp, alo_interrupts_internal_exception_frame.registers.rsp, alo_interrupts_internal_exception_frame.registers.r8, alo_interrupts_internal_exception_frame.registers.r9, alo_interrupts_internal_exception_frame.registers.r10, alo_interrupts_internal_exception_frame.registers.r11, alo_interrupts_internal_exception_frame.registers.r12, alo_interrupts_internal_exception_frame.registers.r13, alo_interrupts_internal_exception_frame.registers.r14, alo_interrupts_internal_exception_frame.registers.r15, alo_interrupts_internal_exception_frame.registers.rfl);
    // TODO: Can probably format this better
    (void) gen_log_formatted(GEN_LOG_LEVEL_DEBUG, "alonira-interrupt", "carry: %uz parity: %uz adjust: %uz zero: %uz sign: %uz trap: %uz interrupt: %uz direction: %uz overflow: %uz privilege: %uz nested task: %uz resume: %uz v8086: %uz alignment check: %uz vinterrupt: %uz vinterrupt pending: %uz cpuid usable: %uz", (alo_register_t) alo_interrupts_internal_exception_frame.registers.rflags.carry, (alo_register_t) alo_interrupts_internal_exception_frame.registers.rflags.parity, (alo_register_t) alo_interrupts_internal_exception_frame.registers.rflags.adjust, (alo_register_t) alo_interrupts_internal_exception_frame.registers.rflags.zero, (alo_register_t) alo_interrupts_internal_exception_frame.registers.rflags.sign, (alo_register_t) alo_interrupts_internal_exception_frame.registers.rflags.trap, (alo_register_t) alo_interrupts_internal_exception_frame.registers.rflags.interrupt, (alo_register_t) alo_interrupts_internal_exception_frame.registers.rflags.direction, (alo_register_t) alo_interrupts_internal_exception_frame.registers.rflags.overflow, (alo_register_t) alo_interrupts_internal_exception_frame.registers.rflags.privilege, (alo_register_t) alo_interrupts_internal_exception_frame.registers.rflags.nested_task, (alo_register_t) alo_interrupts_internal_exception_frame.registers.rflags.resume, (alo_register_t) alo_interrupts_internal_exception_frame.registers.rflags.v8086, (alo_register_t) alo_interrupts_internal_exception_frame.registers.rflags.alignment_check, (alo_register_t) alo_interrupts_internal_exception_frame.registers.rflags.vinterrupt, (alo_register_t) alo_interrupts_internal_exception_frame.registers.rflags.vinterrupt_pending, (alo_register_t) alo_interrupts_internal_exception_frame.registers.rflags.cpuid_usable);
}

#define ALO_INTERRUPTS_NO_ERROR_CODE movl $0, %[error_code]
#define ALO_INTERRUPTS_ERROR_CODE popq %[error_code]

#define ALO_INTERRUPTS_INTERNAL_EXCEPTION_BODY(exception_vector, ...) \
    GEN_ASM_BLOCK( \
        /* Exception Entry Frame */ \
        GEN_ASM(__VA_ARGS__) \
        GEN_ASM(popq %[rip]) \
        GEN_ASM(popq %[cs]) \
        GEN_ASM(popq %[rflags]) \
        GEN_ASM(popq %[rsp]) \
        GEN_ASM(popq %[ss]) \
        /* Exception Frame */ \
        GEN_ASM(movl /* NOTE: Here we assume that enums are ints - if something weird happens in future that's probably why */ %[exception_vector], %[vector]) \
        GEN_ASM(movq %%rax, %[rax]) \
        GEN_ASM(movq %%rbx, %[rbx]) \
        GEN_ASM(movq %%rcx, %[rcx]) \
        GEN_ASM(movq %%rdx, %[rdx]) \
        GEN_ASM(movq %%rsi, %[rsi]) \
        GEN_ASM(movq %%rdi, %[rdi]) \
        GEN_ASM(movq %%rbp, %[rbp]) \
        GEN_ASM(movq %%r8 , %[r8] ) \
        GEN_ASM(movq %%r9 , %[r9] ) \
        GEN_ASM(movq %%r10, %[r10]) \
        GEN_ASM(movq %%r11, %[r11]) \
        GEN_ASM(movq %%r12, %[r12]) \
        GEN_ASM(movq %%r13, %[r13]) \
        GEN_ASM(movq %%r14, %[r14]) \
        GEN_ASM(movq %%r15, %[r15]) \
        GEN_ASM(.extern alo_interrupts_internal_exception_stub) \
        GEN_ASM(callq alo_interrupts_internal_exception_stub), \
        GEN_ASM(pushq %[ss]) \
        GEN_ASM(pushq %[rsp]) \
        GEN_ASM(pushq %[rflags]) \
        GEN_ASM(pushq %[cs]) \
        GEN_ASM(pushq %[rip]) \
        GEN_ASM(iretq) \
    : \
        /* Exception Entry Frame */ \
        [error_code ] "=m" (alo_interrupts_internal_exception_frame.error_code       ), \
        [rip        ] "=m" (alo_interrupts_internal_exception_frame.registers.rip    ), \
        [cs         ] "=m" (alo_interrupts_internal_exception_frame.cs               ), \
        [rflags     ] "=m" (alo_interrupts_internal_exception_frame.registers.rflags ), \
        [rsp        ] "=m" (alo_interrupts_internal_exception_frame.registers.rsp    ), \
        [ss         ] "=m" (alo_interrupts_internal_exception_frame.ss               ), \
        /* Exception Frame */ \
        [vector] "=m" (alo_interrupts_internal_exception_frame.vector), \
        [rax   ] "=m" (alo_interrupts_internal_exception_frame.registers.rax), \
        [rbx   ] "=m" (alo_interrupts_internal_exception_frame.registers.rbx), \
        [rcx   ] "=m" (alo_interrupts_internal_exception_frame.registers.rcx), \
        [rdx   ] "=m" (alo_interrupts_internal_exception_frame.registers.rdx), \
        [rsi   ] "=m" (alo_interrupts_internal_exception_frame.registers.rsi), \
        [rdi   ] "=m" (alo_interrupts_internal_exception_frame.registers.rdi), \
        [rbp   ] "=m" (alo_interrupts_internal_exception_frame.registers.rbp), \
        [r8    ] "=m" (alo_interrupts_internal_exception_frame.registers.r8 ), \
        [r9    ] "=m" (alo_interrupts_internal_exception_frame.registers.r9 ), \
        [r10   ] "=m" (alo_interrupts_internal_exception_frame.registers.r10), \
        [r11   ] "=m" (alo_interrupts_internal_exception_frame.registers.r11), \
        [r12   ] "=m" (alo_interrupts_internal_exception_frame.registers.r12), \
        [r13   ] "=m" (alo_interrupts_internal_exception_frame.registers.r13), \
        [r14   ] "=m" (alo_interrupts_internal_exception_frame.registers.r14), \
        [r15   ] "=m" (alo_interrupts_internal_exception_frame.registers.r15) \
    : \
        [exception_vector] "n" (exception_vector) \
    :)

GEN_NAKED static void alo_interrupts_internal_exception_handler_divide_by_zero              (void) { ALO_INTERRUPTS_INTERNAL_EXCEPTION_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_DIVIDE_BY_ZERO              , ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_debug_trap                  (void) { ALO_INTERRUPTS_INTERNAL_EXCEPTION_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_DEBUG_TRAP                  , ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_nmi                         (void) { ALO_INTERRUPTS_INTERNAL_EXCEPTION_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_NMI                         , ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_breakpoint                  (void) { ALO_INTERRUPTS_INTERNAL_EXCEPTION_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_BREAKPOINT                  , ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_overflow                    (void) { ALO_INTERRUPTS_INTERNAL_EXCEPTION_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_OVERFLOW                    , ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_bound_range_exceeded        (void) { ALO_INTERRUPTS_INTERNAL_EXCEPTION_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_BOUND_RANGE_EXCEEDED        , ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_invalid_opcode              (void) { ALO_INTERRUPTS_INTERNAL_EXCEPTION_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_INVALID_OPCODE              , ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_device_not_avilable         (void) { ALO_INTERRUPTS_INTERNAL_EXCEPTION_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_DEVICE_NOT_AVILABLE         , ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_double_fault                (void) { ALO_INTERRUPTS_INTERNAL_EXCEPTION_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_DOUBLE_FAULT                , ALO_INTERRUPTS_ERROR_CODE   ); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_coprocessor_segment_overrun (void) { ALO_INTERRUPTS_INTERNAL_EXCEPTION_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_COPROCESSOR_SEGMENT_OVERRUN , ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_invalid_tss                 (void) { ALO_INTERRUPTS_INTERNAL_EXCEPTION_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_INVALID_TSS                 , ALO_INTERRUPTS_ERROR_CODE   ); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_segment_not_present         (void) { ALO_INTERRUPTS_INTERNAL_EXCEPTION_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_SEGMENT_NOT_PRESENT         , ALO_INTERRUPTS_ERROR_CODE   ); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_stack_segment_fault         (void) { ALO_INTERRUPTS_INTERNAL_EXCEPTION_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_STACK_SEGMENT_FAULT         , ALO_INTERRUPTS_ERROR_CODE   ); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_general_protection_fault    (void) { ALO_INTERRUPTS_INTERNAL_EXCEPTION_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_GENERAL_PROTECTION_FAULT    , ALO_INTERRUPTS_ERROR_CODE   ); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_page_fault                  (void) { ALO_INTERRUPTS_INTERNAL_EXCEPTION_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_PAGE_FAULT                  , ALO_INTERRUPTS_ERROR_CODE   ); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_reserved0                   (void) { ALO_INTERRUPTS_INTERNAL_EXCEPTION_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED0                   , ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_x87_floating_point          (void) { ALO_INTERRUPTS_INTERNAL_EXCEPTION_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_X87_FLOATING_POINT          , ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_alignment_check             (void) { ALO_INTERRUPTS_INTERNAL_EXCEPTION_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_ALIGNMENT_CHECK             , ALO_INTERRUPTS_ERROR_CODE   ); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_machine_check               (void) { ALO_INTERRUPTS_INTERNAL_EXCEPTION_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_MACHINE_CHECK               , ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_simd_floating_point         (void) { ALO_INTERRUPTS_INTERNAL_EXCEPTION_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_SIMD_FLOATING_POINT         , ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_virtualization              (void) { ALO_INTERRUPTS_INTERNAL_EXCEPTION_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_VIRTUALIZATION              , ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_control_protection          (void) { ALO_INTERRUPTS_INTERNAL_EXCEPTION_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_CONTROL_PROTECTION          , ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_reserved1                   (void) { ALO_INTERRUPTS_INTERNAL_EXCEPTION_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED1                   , ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_reserved2                   (void) { ALO_INTERRUPTS_INTERNAL_EXCEPTION_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED2                   , ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_reserved3                   (void) { ALO_INTERRUPTS_INTERNAL_EXCEPTION_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED3                   , ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_reserved4                   (void) { ALO_INTERRUPTS_INTERNAL_EXCEPTION_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED4                   , ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_reserved5                   (void) { ALO_INTERRUPTS_INTERNAL_EXCEPTION_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED5                   , ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_reserved6                   (void) { ALO_INTERRUPTS_INTERNAL_EXCEPTION_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED6                   , ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_hypervisor_injection        (void) { ALO_INTERRUPTS_INTERNAL_EXCEPTION_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_HYPERVISOR_INJECTION        , ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_vmm_communication           (void) { ALO_INTERRUPTS_INTERNAL_EXCEPTION_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_VMM_COMMUNICATION           , ALO_INTERRUPTS_ERROR_CODE   ); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_security                    (void) { ALO_INTERRUPTS_INTERNAL_EXCEPTION_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_SECURITY                    , ALO_INTERRUPTS_ERROR_CODE   ); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_reserved7                   (void) { ALO_INTERRUPTS_INTERNAL_EXCEPTION_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED7                   , ALO_INTERRUPTS_NO_ERROR_CODE); }

gen_error_t* alo_interrupts_install_exception_handlers(void) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) alo_interrupts_install_exception_handlers, GEN_FILE_NAME);
    if(error) return error;

    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_DIVIDE_BY_ZERO              ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_divide_by_zero              , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_DEBUG_TRAP                  ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_debug_trap                  , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_NMI                         ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_nmi                         , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_BREAKPOINT                  ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_breakpoint                  , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_OVERFLOW                    ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_overflow                    , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_BOUND_RANGE_EXCEEDED        ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_bound_range_exceeded        , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_INVALID_OPCODE              ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_invalid_opcode              , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_DEVICE_NOT_AVILABLE         ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_device_not_avilable         , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_DOUBLE_FAULT                ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_double_fault                , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_COPROCESSOR_SEGMENT_OVERRUN ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_coprocessor_segment_overrun , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_INVALID_TSS                 ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_invalid_tss                 , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_SEGMENT_NOT_PRESENT         ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_segment_not_present         , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_STACK_SEGMENT_FAULT         ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_stack_segment_fault         , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_GENERAL_PROTECTION_FAULT    ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_general_protection_fault    , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_PAGE_FAULT                  ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_page_fault                  , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED0                   ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_reserved0                   , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_X87_FLOATING_POINT          ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_x87_floating_point          , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_ALIGNMENT_CHECK             ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_alignment_check             , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_MACHINE_CHECK               ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_machine_check               , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_SIMD_FLOATING_POINT         ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_simd_floating_point         , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_VIRTUALIZATION              ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_virtualization              , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_CONTROL_PROTECTION          ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_control_protection          , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED1                   ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_reserved1                   , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED2                   ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_reserved2                   , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED3                   ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_reserved3                   , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED4                   ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_reserved4                   , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED5                   ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_reserved5                   , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED6                   ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_reserved6                   , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_HYPERVISOR_INJECTION        ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_hypervisor_injection        , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_VMM_COMMUNICATION           ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_vmm_communication           , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_SECURITY                    ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_security                    , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED7                   ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_reserved7                   , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);

    return GEN_NULL;
}
