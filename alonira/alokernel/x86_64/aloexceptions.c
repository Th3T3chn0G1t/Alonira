// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include <gencommon.h>
#include <genlog.h>

#include "include/aloidt.h"
#include "include/alotss.h"

static const char* alo_interrupts_internal_exception_names[] = {
    [ALO_INTERRUPT_VECTOR_EXCEPTION_DIVIDE_BY_ZERO              ] = "divide by zero"              ,
    [ALO_INTERRUPT_VECTOR_EXCEPTION_DEBUG_TRAP                  ] = "debug trap"                  ,
    [ALO_INTERRUPT_VECTOR_EXCEPTION_NMI                         ] = "nmi"                         ,
    [ALO_INTERRUPT_VECTOR_EXCEPTION_BREAKPOINT                  ] = "breakpoint"                  ,
    [ALO_INTERRUPT_VECTOR_EXCEPTION_OVERFLOW                    ] = "overflow"                    ,
    [ALO_INTERRUPT_VECTOR_EXCEPTION_BOUND_RANGE_EXCEEDED        ] = "bound range exceeded"        ,
    [ALO_INTERRUPT_VECTOR_EXCEPTION_INVALID_OPCODE              ] = "invalid opcode"              ,
    [ALO_INTERRUPT_VECTOR_EXCEPTION_DEVICE_NOT_AVAILABLE        ] = "device not available"        ,
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

// NOTE: Please never modify this from the exception stub.
GEN_THREAD_LOCAL static alo_exception_frame_t alo_interrupts_internal_exception_frame;

GEN_NORETURN ALO_INTERRUPT_HANDLER_CALLABLE_ATTRIBUTES extern void alo_interrupts_internal_exception_stub(void);
GEN_NORETURN ALO_INTERRUPT_HANDLER_CALLABLE_ATTRIBUTES GEN_USED void alo_interrupts_internal_exception_stub(void) {
    gen_tooling_push(GEN_FUNCTION_NAME, GEN_FILE_NAME);
    GEN_TOOLING_AUTO gen_error_t* error;

    // TODO: Print errors nicely with error_code union membs
    error = gen_log(GEN_LOG_LEVEL_DEBUG, "alonira-interrupts", "Exception: `%t` @ %p", alo_interrupts_internal_exception_names[alo_interrupts_internal_exception_frame.vector], alo_interrupts_internal_exception_frame.registers.rip);
    if(error) gen_error_abort();

    error = gen_log(GEN_LOG_LEVEL_DEBUG, "alonira-interrupts", "ss: %p cs: %p", (alo_register_t) alo_interrupts_internal_exception_frame.ss.ss.selector, (alo_register_t) alo_interrupts_internal_exception_frame.cs.cs.selector);
    if(error) gen_error_abort();

    error = gen_log(GEN_LOG_LEVEL_DEBUG, "alonira-interrupts", "rax: %p rbx: %p rcx: %p rdx: %p rsi: %p rdi: %p rbp: %p rsp: %p r8: %p r9: %p r10: %p r11: %p r12: %p r13: %p r14: %p r15: %p rfl: %p", alo_interrupts_internal_exception_frame.registers.rax, alo_interrupts_internal_exception_frame.registers.rbx, alo_interrupts_internal_exception_frame.registers.rcx, alo_interrupts_internal_exception_frame.registers.rdx, alo_interrupts_internal_exception_frame.registers.rsi, alo_interrupts_internal_exception_frame.registers.rdi, alo_interrupts_internal_exception_frame.registers.rbp, alo_interrupts_internal_exception_frame.registers.rsp, alo_interrupts_internal_exception_frame.registers.r8, alo_interrupts_internal_exception_frame.registers.r9, alo_interrupts_internal_exception_frame.registers.r10, alo_interrupts_internal_exception_frame.registers.r11, alo_interrupts_internal_exception_frame.registers.r12, alo_interrupts_internal_exception_frame.registers.r13, alo_interrupts_internal_exception_frame.registers.r14, alo_interrupts_internal_exception_frame.registers.r15, alo_interrupts_internal_exception_frame.registers.rfl);
    if(error) gen_error_abort();

    error = gen_log(GEN_LOG_LEVEL_DEBUG, "alonira-interrupts", "carry: %uz parity: %uz adjust: %uz zero: %uz sign: %uz trap: %uz interrupt: %uz direction: %uz overflow: %uz privilege: %uz nested task: %uz resume: %uz v8086: %uz alignment check: %uz vinterrupt: %uz vinterrupt pending: %uz cpuid usable: %uz", (alo_register_t) alo_interrupts_internal_exception_frame.registers.rflags.carry, (alo_register_t) alo_interrupts_internal_exception_frame.registers.rflags.parity, (alo_register_t) alo_interrupts_internal_exception_frame.registers.rflags.adjust, (alo_register_t) alo_interrupts_internal_exception_frame.registers.rflags.zero, (alo_register_t) alo_interrupts_internal_exception_frame.registers.rflags.sign, (alo_register_t) alo_interrupts_internal_exception_frame.registers.rflags.trap, (alo_register_t) alo_interrupts_internal_exception_frame.registers.rflags.interrupt, (alo_register_t) alo_interrupts_internal_exception_frame.registers.rflags.direction, (alo_register_t) alo_interrupts_internal_exception_frame.registers.rflags.overflow, (alo_register_t) alo_interrupts_internal_exception_frame.registers.rflags.privilege, (alo_register_t) alo_interrupts_internal_exception_frame.registers.rflags.nested_task, (alo_register_t) alo_interrupts_internal_exception_frame.registers.rflags.resume, (alo_register_t) alo_interrupts_internal_exception_frame.registers.rflags.v8086, (alo_register_t) alo_interrupts_internal_exception_frame.registers.rflags.alignment_check, (alo_register_t) alo_interrupts_internal_exception_frame.registers.rflags.vinterrupt, (alo_register_t) alo_interrupts_internal_exception_frame.registers.rflags.vinterrupt_pending, (alo_register_t) alo_interrupts_internal_exception_frame.registers.rflags.cpuid_usable);
    if(error) gen_error_abort();

    // TODO: Make proper error
    error = gen_error_attach_backtrace(GEN_ERROR_UNKNOWN, GEN_LINE_STRING, "Exception");
    gen_log(GEN_LOG_LEVEL_FATAL, "alonira-interrupts", "%e", error);
    gen_error_abort();
}

GEN_NAKED static void alo_interrupts_internal_exception_handler_divide_by_zero              (void) { ALO_INTERRUPTS_ISR_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_DIVIDE_BY_ZERO              , alo_interrupts_internal_exception_frame, alo_interrupts_internal_exception_stub, ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_debug_trap                  (void) { ALO_INTERRUPTS_ISR_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_DEBUG_TRAP                  , alo_interrupts_internal_exception_frame, alo_interrupts_internal_exception_stub, ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_nmi                         (void) { ALO_INTERRUPTS_ISR_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_NMI                         , alo_interrupts_internal_exception_frame, alo_interrupts_internal_exception_stub, ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_breakpoint                  (void) { ALO_INTERRUPTS_ISR_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_BREAKPOINT                  , alo_interrupts_internal_exception_frame, alo_interrupts_internal_exception_stub, ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_overflow                    (void) { ALO_INTERRUPTS_ISR_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_OVERFLOW                    , alo_interrupts_internal_exception_frame, alo_interrupts_internal_exception_stub, ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_bound_range_exceeded        (void) { ALO_INTERRUPTS_ISR_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_BOUND_RANGE_EXCEEDED        , alo_interrupts_internal_exception_frame, alo_interrupts_internal_exception_stub, ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_invalid_opcode              (void) { ALO_INTERRUPTS_ISR_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_INVALID_OPCODE              , alo_interrupts_internal_exception_frame, alo_interrupts_internal_exception_stub, ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_device_not_available        (void) { ALO_INTERRUPTS_ISR_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_DEVICE_NOT_AVAILABLE        , alo_interrupts_internal_exception_frame, alo_interrupts_internal_exception_stub, ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_double_fault                (void) { ALO_INTERRUPTS_ISR_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_DOUBLE_FAULT                , alo_interrupts_internal_exception_frame, alo_interrupts_internal_exception_stub, ALO_INTERRUPTS_ERROR_CODE   ); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_coprocessor_segment_overrun (void) { ALO_INTERRUPTS_ISR_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_COPROCESSOR_SEGMENT_OVERRUN , alo_interrupts_internal_exception_frame, alo_interrupts_internal_exception_stub, ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_invalid_tss                 (void) { ALO_INTERRUPTS_ISR_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_INVALID_TSS                 , alo_interrupts_internal_exception_frame, alo_interrupts_internal_exception_stub, ALO_INTERRUPTS_ERROR_CODE   ); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_segment_not_present         (void) { ALO_INTERRUPTS_ISR_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_SEGMENT_NOT_PRESENT         , alo_interrupts_internal_exception_frame, alo_interrupts_internal_exception_stub, ALO_INTERRUPTS_ERROR_CODE   ); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_stack_segment_fault         (void) { ALO_INTERRUPTS_ISR_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_STACK_SEGMENT_FAULT         , alo_interrupts_internal_exception_frame, alo_interrupts_internal_exception_stub, ALO_INTERRUPTS_ERROR_CODE   ); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_general_protection_fault    (void) { ALO_INTERRUPTS_ISR_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_GENERAL_PROTECTION_FAULT    , alo_interrupts_internal_exception_frame, alo_interrupts_internal_exception_stub, ALO_INTERRUPTS_ERROR_CODE   ); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_page_fault                  (void) { ALO_INTERRUPTS_ISR_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_PAGE_FAULT                  , alo_interrupts_internal_exception_frame, alo_interrupts_internal_exception_stub, ALO_INTERRUPTS_ERROR_CODE   ); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_reserved0                   (void) { ALO_INTERRUPTS_ISR_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED0                   , alo_interrupts_internal_exception_frame, alo_interrupts_internal_exception_stub, ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_x87_floating_point          (void) { ALO_INTERRUPTS_ISR_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_X87_FLOATING_POINT          , alo_interrupts_internal_exception_frame, alo_interrupts_internal_exception_stub, ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_alignment_check             (void) { ALO_INTERRUPTS_ISR_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_ALIGNMENT_CHECK             , alo_interrupts_internal_exception_frame, alo_interrupts_internal_exception_stub, ALO_INTERRUPTS_ERROR_CODE   ); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_machine_check               (void) { ALO_INTERRUPTS_ISR_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_MACHINE_CHECK               , alo_interrupts_internal_exception_frame, alo_interrupts_internal_exception_stub, ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_simd_floating_point         (void) { ALO_INTERRUPTS_ISR_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_SIMD_FLOATING_POINT         , alo_interrupts_internal_exception_frame, alo_interrupts_internal_exception_stub, ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_virtualization              (void) { ALO_INTERRUPTS_ISR_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_VIRTUALIZATION              , alo_interrupts_internal_exception_frame, alo_interrupts_internal_exception_stub, ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_control_protection          (void) { ALO_INTERRUPTS_ISR_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_CONTROL_PROTECTION          , alo_interrupts_internal_exception_frame, alo_interrupts_internal_exception_stub, ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_reserved1                   (void) { ALO_INTERRUPTS_ISR_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED1                   , alo_interrupts_internal_exception_frame, alo_interrupts_internal_exception_stub, ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_reserved2                   (void) { ALO_INTERRUPTS_ISR_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED2                   , alo_interrupts_internal_exception_frame, alo_interrupts_internal_exception_stub, ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_reserved3                   (void) { ALO_INTERRUPTS_ISR_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED3                   , alo_interrupts_internal_exception_frame, alo_interrupts_internal_exception_stub, ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_reserved4                   (void) { ALO_INTERRUPTS_ISR_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED4                   , alo_interrupts_internal_exception_frame, alo_interrupts_internal_exception_stub, ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_reserved5                   (void) { ALO_INTERRUPTS_ISR_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED5                   , alo_interrupts_internal_exception_frame, alo_interrupts_internal_exception_stub, ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_reserved6                   (void) { ALO_INTERRUPTS_ISR_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED6                   , alo_interrupts_internal_exception_frame, alo_interrupts_internal_exception_stub, ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_hypervisor_injection        (void) { ALO_INTERRUPTS_ISR_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_HYPERVISOR_INJECTION        , alo_interrupts_internal_exception_frame, alo_interrupts_internal_exception_stub, ALO_INTERRUPTS_NO_ERROR_CODE); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_vmm_communication           (void) { ALO_INTERRUPTS_ISR_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_VMM_COMMUNICATION           , alo_interrupts_internal_exception_frame, alo_interrupts_internal_exception_stub, ALO_INTERRUPTS_ERROR_CODE   ); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_security                    (void) { ALO_INTERRUPTS_ISR_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_SECURITY                    , alo_interrupts_internal_exception_frame, alo_interrupts_internal_exception_stub, ALO_INTERRUPTS_ERROR_CODE   ); }
GEN_NAKED static void alo_interrupts_internal_exception_handler_reserved7                   (void) { ALO_INTERRUPTS_ISR_BODY(ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED7                   , alo_interrupts_internal_exception_frame, alo_interrupts_internal_exception_stub, ALO_INTERRUPTS_NO_ERROR_CODE); }

gen_error_t* alo_interrupts_install_exception_handlers(void) {
    gen_tooling_push(GEN_FUNCTION_NAME, GEN_FILE_NAME);
    GEN_TOOLING_AUTO gen_error_t* error;

    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_DIVIDE_BY_ZERO              ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_divide_by_zero              , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_DEBUG_TRAP                  ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_debug_trap                  , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_NMI                         ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_nmi                         , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_BREAKPOINT                  ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_breakpoint                  , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_OVERFLOW                    ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_overflow                    , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_BOUND_RANGE_EXCEEDED        ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_bound_range_exceeded        , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_INVALID_OPCODE              ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_invalid_opcode              , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_DEVICE_NOT_AVAILABLE        ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_interrupts_internal_exception_handler_device_not_available        , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
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
