// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include "include/idt.h"
#include "include/tss.h"

#include <gencommon.h>
#include <genlog.h>

GEN_THREAD_LOCAL static alo_exception_frame_t alo_idt_internal_exception_frame;

ALO_INTERRUPT_HANDLER_CALLABLE_ATTRIBUTES extern void alo_idt_internal_temp_test_thisng_delete_me(void);
GEN_NORETURN ALO_INTERRUPT_HANDLER_CALLABLE_ATTRIBUTES GEN_USED void alo_idt_internal_temp_test_thisng_delete_me(void) {
   (void) gen_log_formatted(GEN_LOG_LEVEL_DEBUG, "alonira-interrupt", "Exception: `%t`", alo_idt_internal_exception_frame.TESTING_NAME);
   gen_error_abort();
}

// TODO: rip, cs, rflags, rsp, ss need to be saved separately/differently
#define ALO_IDT_INTERNAL_EXCEPTION_BODY_NO_ERROR_CODE(exception_vector, name) \
    GEN_ASM_BLOCK( \
        GEN_ASM(movl /* NOTE: Here we assume that enums are ints - if something weird happens in future that's probably why */ %[exception_vector], %[vector]) \
        GEN_ASM(movl $0, %[error_code]) \
        GEN_ASM(movq %[NAME], %[TESTING_NAME]) \
        GEN_ASM(.extern alo_idt_internal_temp_test_thisng_delete_me) \
        GEN_ASM(callq alo_idt_internal_temp_test_thisng_delete_me), \
    : \
        [vector] "=m" (alo_idt_internal_exception_frame.vector), \
        [error_code] "=m" (alo_idt_internal_exception_frame.error_code), \
        [TESTING_NAME] "=m" (alo_idt_internal_exception_frame.TESTING_NAME) \
    : \
        [exception_vector] "n" (exception_vector), \
        [NAME] "p" (name) \
    :)

GEN_NAKED static void alo_idt_internal_exception_handler_divide_by_zero              (void) { ALO_IDT_INTERNAL_EXCEPTION_BODY_NO_ERROR_CODE(ALO_INTERRUPT_VECTOR_EXCEPTION_DIVIDE_BY_ZERO              , "divide_by_zero              "); }
GEN_NAKED static void alo_idt_internal_exception_handler_debug_trap                  (void) { ALO_IDT_INTERNAL_EXCEPTION_BODY_NO_ERROR_CODE(ALO_INTERRUPT_VECTOR_EXCEPTION_DEBUG_TRAP                  , "debug_trap                  "); }
GEN_NAKED static void alo_idt_internal_exception_handler_nmi                         (void) { ALO_IDT_INTERNAL_EXCEPTION_BODY_NO_ERROR_CODE(ALO_INTERRUPT_VECTOR_EXCEPTION_NMI                         , "nmi                         "); }
GEN_NAKED static void alo_idt_internal_exception_handler_breakpoint                  (void) { ALO_IDT_INTERNAL_EXCEPTION_BODY_NO_ERROR_CODE(ALO_INTERRUPT_VECTOR_EXCEPTION_BREAKPOINT                  , "breakpoint                  "); }
GEN_NAKED static void alo_idt_internal_exception_handler_overflow                    (void) { ALO_IDT_INTERNAL_EXCEPTION_BODY_NO_ERROR_CODE(ALO_INTERRUPT_VECTOR_EXCEPTION_OVERFLOW                    , "overflow                    "); }
GEN_NAKED static void alo_idt_internal_exception_handler_bound_range_exceeded        (void) { ALO_IDT_INTERNAL_EXCEPTION_BODY_NO_ERROR_CODE(ALO_INTERRUPT_VECTOR_EXCEPTION_BOUND_RANGE_EXCEEDED        , "bound_range_exceeded        "); }
GEN_NAKED static void alo_idt_internal_exception_handler_invalid_opcode              (void) { ALO_IDT_INTERNAL_EXCEPTION_BODY_NO_ERROR_CODE(ALO_INTERRUPT_VECTOR_EXCEPTION_INVALID_OPCODE              , "invalid_opcode              "); }
GEN_NAKED static void alo_idt_internal_exception_handler_device_not_avilable         (void) { ALO_IDT_INTERNAL_EXCEPTION_BODY_NO_ERROR_CODE(ALO_INTERRUPT_VECTOR_EXCEPTION_DEVICE_NOT_AVILABLE         , "device_not_avilable         "); }
GEN_NAKED static void alo_idt_internal_exception_handler_double_fault                (void) { ALO_IDT_INTERNAL_EXCEPTION_BODY_NO_ERROR_CODE(ALO_INTERRUPT_VECTOR_EXCEPTION_DOUBLE_FAULT                , "double_fault                "); }
GEN_NAKED static void alo_idt_internal_exception_handler_coprocessor_segment_overrun (void) { ALO_IDT_INTERNAL_EXCEPTION_BODY_NO_ERROR_CODE(ALO_INTERRUPT_VECTOR_EXCEPTION_COPROCESSOR_SEGMENT_OVERRUN , "coprocessor_segment_overrun "); }
GEN_NAKED static void alo_idt_internal_exception_handler_invalid_tss                 (void) { ALO_IDT_INTERNAL_EXCEPTION_BODY_NO_ERROR_CODE(ALO_INTERRUPT_VECTOR_EXCEPTION_INVALID_TSS                 , "invalid_tss                 "); }
GEN_NAKED static void alo_idt_internal_exception_handler_segment_not_present         (void) { ALO_IDT_INTERNAL_EXCEPTION_BODY_NO_ERROR_CODE(ALO_INTERRUPT_VECTOR_EXCEPTION_SEGMENT_NOT_PRESENT         , "segment_not_present         "); }
GEN_NAKED static void alo_idt_internal_exception_handler_stack_segment_fault         (void) { ALO_IDT_INTERNAL_EXCEPTION_BODY_NO_ERROR_CODE(ALO_INTERRUPT_VECTOR_EXCEPTION_STACK_SEGMENT_FAULT         , "stack_segment_fault         "); }
GEN_NAKED static void alo_idt_internal_exception_handler_general_protection_fault    (void) { ALO_IDT_INTERNAL_EXCEPTION_BODY_NO_ERROR_CODE(ALO_INTERRUPT_VECTOR_EXCEPTION_GENERAL_PROTECTION_FAULT    , "general_protection_fault    "); }
GEN_NAKED static void alo_idt_internal_exception_handler_page_fault                  (void) { ALO_IDT_INTERNAL_EXCEPTION_BODY_NO_ERROR_CODE(ALO_INTERRUPT_VECTOR_EXCEPTION_PAGE_FAULT                  , "page_fault                  "); }
GEN_NAKED static void alo_idt_internal_exception_handler_reserved0                   (void) { ALO_IDT_INTERNAL_EXCEPTION_BODY_NO_ERROR_CODE(ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED0                   , "reserved0                   "); }
GEN_NAKED static void alo_idt_internal_exception_handler_x87_floating_point          (void) { ALO_IDT_INTERNAL_EXCEPTION_BODY_NO_ERROR_CODE(ALO_INTERRUPT_VECTOR_EXCEPTION_X87_FLOATING_POINT          , "x87_floating_point          "); }
GEN_NAKED static void alo_idt_internal_exception_handler_alignment_check             (void) { ALO_IDT_INTERNAL_EXCEPTION_BODY_NO_ERROR_CODE(ALO_INTERRUPT_VECTOR_EXCEPTION_ALIGNMENT_CHECK             , "alignment_check             "); }
GEN_NAKED static void alo_idt_internal_exception_handler_machine_check               (void) { ALO_IDT_INTERNAL_EXCEPTION_BODY_NO_ERROR_CODE(ALO_INTERRUPT_VECTOR_EXCEPTION_MACHINE_CHECK               , "machine_check               "); }
GEN_NAKED static void alo_idt_internal_exception_handler_simd_floating_point         (void) { ALO_IDT_INTERNAL_EXCEPTION_BODY_NO_ERROR_CODE(ALO_INTERRUPT_VECTOR_EXCEPTION_SIMD_FLOATING_POINT         , "simd_floating_point         "); }
GEN_NAKED static void alo_idt_internal_exception_handler_virtualization              (void) { ALO_IDT_INTERNAL_EXCEPTION_BODY_NO_ERROR_CODE(ALO_INTERRUPT_VECTOR_EXCEPTION_VIRTUALIZATION              , "virtualization              "); }
GEN_NAKED static void alo_idt_internal_exception_handler_control_protection          (void) { ALO_IDT_INTERNAL_EXCEPTION_BODY_NO_ERROR_CODE(ALO_INTERRUPT_VECTOR_EXCEPTION_CONTROL_PROTECTION          , "control_protection          "); }
GEN_NAKED static void alo_idt_internal_exception_handler_reserved1                   (void) { ALO_IDT_INTERNAL_EXCEPTION_BODY_NO_ERROR_CODE(ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED1                   , "reserved1                   "); }
GEN_NAKED static void alo_idt_internal_exception_handler_reserved2                   (void) { ALO_IDT_INTERNAL_EXCEPTION_BODY_NO_ERROR_CODE(ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED2                   , "reserved2                   "); }
GEN_NAKED static void alo_idt_internal_exception_handler_reserved3                   (void) { ALO_IDT_INTERNAL_EXCEPTION_BODY_NO_ERROR_CODE(ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED3                   , "reserved3                   "); }
GEN_NAKED static void alo_idt_internal_exception_handler_reserved4                   (void) { ALO_IDT_INTERNAL_EXCEPTION_BODY_NO_ERROR_CODE(ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED4                   , "reserved4                   "); }
GEN_NAKED static void alo_idt_internal_exception_handler_reserved5                   (void) { ALO_IDT_INTERNAL_EXCEPTION_BODY_NO_ERROR_CODE(ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED5                   , "reserved5                   "); }
GEN_NAKED static void alo_idt_internal_exception_handler_reserved6                   (void) { ALO_IDT_INTERNAL_EXCEPTION_BODY_NO_ERROR_CODE(ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED6                   , "reserved6                   "); }
GEN_NAKED static void alo_idt_internal_exception_handler_hypervisor_injection        (void) { ALO_IDT_INTERNAL_EXCEPTION_BODY_NO_ERROR_CODE(ALO_INTERRUPT_VECTOR_EXCEPTION_HYPERVISOR_INJECTION        , "hypervisor_injection        "); }
GEN_NAKED static void alo_idt_internal_exception_handler_vmm_communication           (void) { ALO_IDT_INTERNAL_EXCEPTION_BODY_NO_ERROR_CODE(ALO_INTERRUPT_VECTOR_EXCEPTION_VMM_COMMUNICATION           , "vmm_communication           "); }
GEN_NAKED static void alo_idt_internal_exception_handler_security                    (void) { ALO_IDT_INTERNAL_EXCEPTION_BODY_NO_ERROR_CODE(ALO_INTERRUPT_VECTOR_EXCEPTION_SECURITY                    , "security                    "); }
GEN_NAKED static void alo_idt_internal_exception_handler_reserved7                   (void) { ALO_IDT_INTERNAL_EXCEPTION_BODY_NO_ERROR_CODE(ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED7                   , "reserved7                   "); }

gen_error_t* alo_interrupts_install_exception_handlers(void) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) alo_interrupts_install_exception_handlers, GEN_FILE_NAME);
    if(error) return error;

    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_DIVIDE_BY_ZERO              ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_idt_internal_exception_handler_divide_by_zero              , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_DEBUG_TRAP                  ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_idt_internal_exception_handler_debug_trap                  , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_NMI                         ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_idt_internal_exception_handler_nmi                         , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_BREAKPOINT                  ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_idt_internal_exception_handler_breakpoint                  , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_OVERFLOW                    ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_idt_internal_exception_handler_overflow                    , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_BOUND_RANGE_EXCEEDED        ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_idt_internal_exception_handler_bound_range_exceeded        , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_INVALID_OPCODE              ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_idt_internal_exception_handler_invalid_opcode              , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_DEVICE_NOT_AVILABLE         ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_idt_internal_exception_handler_device_not_avilable         , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_DOUBLE_FAULT                ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_idt_internal_exception_handler_double_fault                , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_COPROCESSOR_SEGMENT_OVERRUN ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_idt_internal_exception_handler_coprocessor_segment_overrun , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_INVALID_TSS                 ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_idt_internal_exception_handler_invalid_tss                 , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_SEGMENT_NOT_PRESENT         ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_idt_internal_exception_handler_segment_not_present         , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_STACK_SEGMENT_FAULT         ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_idt_internal_exception_handler_stack_segment_fault         , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_GENERAL_PROTECTION_FAULT    ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_idt_internal_exception_handler_general_protection_fault    , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_PAGE_FAULT                  ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_idt_internal_exception_handler_page_fault                  , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED0                   ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_idt_internal_exception_handler_reserved0                   , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_X87_FLOATING_POINT          ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_idt_internal_exception_handler_x87_floating_point          , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_ALIGNMENT_CHECK             ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_idt_internal_exception_handler_alignment_check             , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_MACHINE_CHECK               ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_idt_internal_exception_handler_machine_check               , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_SIMD_FLOATING_POINT         ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_idt_internal_exception_handler_simd_floating_point         , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_VIRTUALIZATION              ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_idt_internal_exception_handler_virtualization              , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_CONTROL_PROTECTION          ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_idt_internal_exception_handler_control_protection          , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED1                   ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_idt_internal_exception_handler_reserved1                   , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED2                   ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_idt_internal_exception_handler_reserved2                   , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED3                   ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_idt_internal_exception_handler_reserved3                   , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED4                   ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_idt_internal_exception_handler_reserved4                   , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED5                   ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_idt_internal_exception_handler_reserved5                   , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED6                   ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_idt_internal_exception_handler_reserved6                   , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_HYPERVISOR_INJECTION        ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_idt_internal_exception_handler_hypervisor_injection        , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_VMM_COMMUNICATION           ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_idt_internal_exception_handler_vmm_communication           , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_SECURITY                    ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_idt_internal_exception_handler_security                    , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);
    alo_idt[ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED7                   ] = ALO_IDT_MAKE_ENTRY((gen_uintptr_t) alo_idt_internal_exception_handler_reserved7                   , ALO_IST_NONE, ALO_IDT_GATE_TYPE_TRAP, ALO_CPU_PRIVILEGE_RING0);

    return GEN_NULL;
}
