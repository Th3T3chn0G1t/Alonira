// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#ifndef ALO_KERNEL_INTERRUPTS_H
#define ALO_KERNEL_INTERRUPTS_H

#include "cpu.h"

#include <gencommon.h>

#define ALO_INTERRUPT_HANDLER_CALLABLE_ATTRIBUTES __attribute__((no_caller_saved_registers))

typedef enum {
    ALO_INTERRUPT_VECTOR_EXCEPTION_DIVIDE_BY_ZERO,
    ALO_INTERRUPT_VECTOR_EXCEPTION_DEBUG_TRAP,
    ALO_INTERRUPT_VECTOR_EXCEPTION_NMI,
    ALO_INTERRUPT_VECTOR_EXCEPTION_BREAKPOINT,
    ALO_INTERRUPT_VECTOR_EXCEPTION_OVERFLOW,
    ALO_INTERRUPT_VECTOR_EXCEPTION_BOUND_RANGE_EXCEEDED,
    ALO_INTERRUPT_VECTOR_EXCEPTION_INVALID_OPCODE,
    ALO_INTERRUPT_VECTOR_EXCEPTION_DEVICE_NOT_AVILABLE,
    ALO_INTERRUPT_VECTOR_EXCEPTION_DOUBLE_FAULT,
    ALO_INTERRUPT_VECTOR_EXCEPTION_COPROCESSOR_SEGMENT_OVERRUN,
    ALO_INTERRUPT_VECTOR_EXCEPTION_INVALID_TSS,
    ALO_INTERRUPT_VECTOR_EXCEPTION_SEGMENT_NOT_PRESENT,
    ALO_INTERRUPT_VECTOR_EXCEPTION_STACK_SEGMENT_FAULT,
    ALO_INTERRUPT_VECTOR_EXCEPTION_GENERAL_PROTECTION_FAULT,
    ALO_INTERRUPT_VECTOR_EXCEPTION_PAGE_FAULT,
    ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED0,
    ALO_INTERRUPT_VECTOR_EXCEPTION_X87_FLOATING_POINT,
    ALO_INTERRUPT_VECTOR_EXCEPTION_ALIGNMENT_CHECK,
    ALO_INTERRUPT_VECTOR_EXCEPTION_MACHINE_CHECK,
    ALO_INTERRUPT_VECTOR_EXCEPTION_SIMD_FLOATING_POINT,
    ALO_INTERRUPT_VECTOR_EXCEPTION_VIRTUALIZATION,
    ALO_INTERRUPT_VECTOR_EXCEPTION_CONTROL_PROTECTION,
    ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED1,
    ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED2,
    ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED3,
    ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED4,
    ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED5,
    ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED6,
    ALO_INTERRUPT_VECTOR_EXCEPTION_HYPERVISOR_INJECTION,
    ALO_INTERRUPT_VECTOR_EXCEPTION_VMM_COMMUNICATION,
    ALO_INTERRUPT_VECTOR_EXCEPTION_SECURITY,
    ALO_INTERRUPT_VECTOR_EXCEPTION_RESERVED7,

    ALO_INTERRUPT_VECTOR_IRQ0,
    ALO_INTERRUPT_VECTOR_IRQ1,
    ALO_INTERRUPT_VECTOR_IRQ2,
    ALO_INTERRUPT_VECTOR_IRQ3,
    ALO_INTERRUPT_VECTOR_IRQ4,
    ALO_INTERRUPT_VECTOR_IRQ5,
    ALO_INTERRUPT_VECTOR_IRQ6,
    ALO_INTERRUPT_VECTOR_IRQ7,
    ALO_INTERRUPT_VECTOR_IRQ8,
    ALO_INTERRUPT_VECTOR_IRQ9,
    ALO_INTERRUPT_VECTOR_IRQ10,
    ALO_INTERRUPT_VECTOR_IRQ11,
    ALO_INTERRUPT_VECTOR_IRQ12,
    ALO_INTERRUPT_VECTOR_IRQ13,
    ALO_INTERRUPT_VECTOR_IRQ14,
    ALO_INTERRUPT_VECTOR_IRQ15,
    ALO_INTERRUPT_VECTOR_IRQ16,
    ALO_INTERRUPT_VECTOR_IRQ17,
    ALO_INTERRUPT_VECTOR_IRQ18,
    ALO_INTERRUPT_VECTOR_IRQ19,
    ALO_INTERRUPT_VECTOR_IRQ20,
    ALO_INTERRUPT_VECTOR_IRQ21,
    ALO_INTERRUPT_VECTOR_IRQ22,
    ALO_INTERRUPT_VECTOR_IRQ23,
    ALO_INTERRUPT_VECTOR_IRQ24,
    ALO_INTERRUPT_VECTOR_IRQ25,
    ALO_INTERRUPT_VECTOR_IRQ26,
    ALO_INTERRUPT_VECTOR_IRQ27,
    ALO_INTERRUPT_VECTOR_IRQ28,
    ALO_INTERRUPT_VECTOR_IRQ29,
    ALO_INTERRUPT_VECTOR_IRQ30,
    ALO_INTERRUPT_VECTOR_IRQ31,
    ALO_INTERRUPT_VECTOR_IRQ32,
    ALO_INTERRUPT_VECTOR_IRQ33,
    ALO_INTERRUPT_VECTOR_IRQ34,
    ALO_INTERRUPT_VECTOR_IRQ35,
    ALO_INTERRUPT_VECTOR_IRQ36,
    ALO_INTERRUPT_VECTOR_IRQ37,
    ALO_INTERRUPT_VECTOR_IRQ38,
    ALO_INTERRUPT_VECTOR_IRQ39,
    ALO_INTERRUPT_VECTOR_IRQ40,
    ALO_INTERRUPT_VECTOR_IRQ41,
    ALO_INTERRUPT_VECTOR_IRQ42,
    ALO_INTERRUPT_VECTOR_IRQ43,
    ALO_INTERRUPT_VECTOR_IRQ44,
    ALO_INTERRUPT_VECTOR_IRQ45,
    ALO_INTERRUPT_VECTOR_IRQ46,
    ALO_INTERRUPT_VECTOR_IRQ47,
    ALO_INTERRUPT_VECTOR_IRQ48,
    ALO_INTERRUPT_VECTOR_IRQ49,
    ALO_INTERRUPT_VECTOR_IRQ50,
    ALO_INTERRUPT_VECTOR_IRQ51,
    ALO_INTERRUPT_VECTOR_IRQ52,
    ALO_INTERRUPT_VECTOR_IRQ53,
    ALO_INTERRUPT_VECTOR_IRQ54,
    ALO_INTERRUPT_VECTOR_IRQ55,
    ALO_INTERRUPT_VECTOR_IRQ56,
    ALO_INTERRUPT_VECTOR_IRQ57,
    ALO_INTERRUPT_VECTOR_IRQ58,
    ALO_INTERRUPT_VECTOR_IRQ59,
    ALO_INTERRUPT_VECTOR_IRQ60,
    ALO_INTERRUPT_VECTOR_IRQ61,
    ALO_INTERRUPT_VECTOR_IRQ62,
    ALO_INTERRUPT_VECTOR_IRQ63,
    ALO_INTERRUPT_VECTOR_IRQ64,
    ALO_INTERRUPT_VECTOR_IRQ65,
    ALO_INTERRUPT_VECTOR_IRQ66,
    ALO_INTERRUPT_VECTOR_IRQ67,
    ALO_INTERRUPT_VECTOR_IRQ68,
    ALO_INTERRUPT_VECTOR_IRQ69,
    ALO_INTERRUPT_VECTOR_IRQ70,
    ALO_INTERRUPT_VECTOR_IRQ71,
    ALO_INTERRUPT_VECTOR_IRQ72,
    ALO_INTERRUPT_VECTOR_IRQ73,
    ALO_INTERRUPT_VECTOR_IRQ74,
    ALO_INTERRUPT_VECTOR_IRQ75,
    ALO_INTERRUPT_VECTOR_IRQ76,
    ALO_INTERRUPT_VECTOR_IRQ77,
    ALO_INTERRUPT_VECTOR_IRQ78,
    ALO_INTERRUPT_VECTOR_IRQ79,
    ALO_INTERRUPT_VECTOR_IRQ80,
    ALO_INTERRUPT_VECTOR_IRQ81,
    ALO_INTERRUPT_VECTOR_IRQ82,
    ALO_INTERRUPT_VECTOR_IRQ83,
    ALO_INTERRUPT_VECTOR_IRQ84,
    ALO_INTERRUPT_VECTOR_IRQ85,
    ALO_INTERRUPT_VECTOR_IRQ86,
    ALO_INTERRUPT_VECTOR_IRQ87,
    ALO_INTERRUPT_VECTOR_IRQ88,
    ALO_INTERRUPT_VECTOR_IRQ89,
    ALO_INTERRUPT_VECTOR_IRQ90,
    ALO_INTERRUPT_VECTOR_IRQ91,
    ALO_INTERRUPT_VECTOR_IRQ92,
    ALO_INTERRUPT_VECTOR_IRQ93,
    ALO_INTERRUPT_VECTOR_IRQ94,
    ALO_INTERRUPT_VECTOR_IRQ95,
    ALO_INTERRUPT_VECTOR_IRQ96,
    ALO_INTERRUPT_VECTOR_IRQ97,
    ALO_INTERRUPT_VECTOR_IRQ98,
    ALO_INTERRUPT_VECTOR_IRQ99,
    ALO_INTERRUPT_VECTOR_IRQ100,
    ALO_INTERRUPT_VECTOR_IRQ101,
    ALO_INTERRUPT_VECTOR_IRQ102,
    ALO_INTERRUPT_VECTOR_IRQ103,
    ALO_INTERRUPT_VECTOR_IRQ104,
    ALO_INTERRUPT_VECTOR_IRQ105,
    ALO_INTERRUPT_VECTOR_IRQ106,
    ALO_INTERRUPT_VECTOR_IRQ107,
    ALO_INTERRUPT_VECTOR_IRQ108,
    ALO_INTERRUPT_VECTOR_IRQ109,
    ALO_INTERRUPT_VECTOR_IRQ110,
    ALO_INTERRUPT_VECTOR_IRQ111,
    ALO_INTERRUPT_VECTOR_IRQ112,
    ALO_INTERRUPT_VECTOR_IRQ113,
    ALO_INTERRUPT_VECTOR_IRQ114,
    ALO_INTERRUPT_VECTOR_IRQ115,
    ALO_INTERRUPT_VECTOR_IRQ116,
    ALO_INTERRUPT_VECTOR_IRQ117,
    ALO_INTERRUPT_VECTOR_IRQ118,
    ALO_INTERRUPT_VECTOR_IRQ119,
    ALO_INTERRUPT_VECTOR_IRQ120,
    ALO_INTERRUPT_VECTOR_IRQ121,
    ALO_INTERRUPT_VECTOR_IRQ122,
    ALO_INTERRUPT_VECTOR_IRQ123,
    ALO_INTERRUPT_VECTOR_IRQ124,
    ALO_INTERRUPT_VECTOR_IRQ125,
    ALO_INTERRUPT_VECTOR_IRQ126,
    ALO_INTERRUPT_VECTOR_IRQ127,
    ALO_INTERRUPT_VECTOR_IRQ128,
    ALO_INTERRUPT_VECTOR_IRQ129,
    ALO_INTERRUPT_VECTOR_IRQ130,
    ALO_INTERRUPT_VECTOR_IRQ131,
    ALO_INTERRUPT_VECTOR_IRQ132,
    ALO_INTERRUPT_VECTOR_IRQ133,
    ALO_INTERRUPT_VECTOR_IRQ134,
    ALO_INTERRUPT_VECTOR_IRQ135,
    ALO_INTERRUPT_VECTOR_IRQ136,
    ALO_INTERRUPT_VECTOR_IRQ137,
    ALO_INTERRUPT_VECTOR_IRQ138,
    ALO_INTERRUPT_VECTOR_IRQ139,
    ALO_INTERRUPT_VECTOR_IRQ140,
    ALO_INTERRUPT_VECTOR_IRQ141,
    ALO_INTERRUPT_VECTOR_IRQ142,
    ALO_INTERRUPT_VECTOR_IRQ143,
    ALO_INTERRUPT_VECTOR_IRQ144,
    ALO_INTERRUPT_VECTOR_IRQ145,
    ALO_INTERRUPT_VECTOR_IRQ146,
    ALO_INTERRUPT_VECTOR_IRQ147,
    ALO_INTERRUPT_VECTOR_IRQ148,
    ALO_INTERRUPT_VECTOR_IRQ149,
    ALO_INTERRUPT_VECTOR_IRQ150,
    ALO_INTERRUPT_VECTOR_IRQ151,
    ALO_INTERRUPT_VECTOR_IRQ152,
    ALO_INTERRUPT_VECTOR_IRQ153,
    ALO_INTERRUPT_VECTOR_IRQ154,
    ALO_INTERRUPT_VECTOR_IRQ155,
    ALO_INTERRUPT_VECTOR_IRQ156,
    ALO_INTERRUPT_VECTOR_IRQ157,
    ALO_INTERRUPT_VECTOR_IRQ158,
    ALO_INTERRUPT_VECTOR_IRQ159,
    ALO_INTERRUPT_VECTOR_IRQ160,
    ALO_INTERRUPT_VECTOR_IRQ161,
    ALO_INTERRUPT_VECTOR_IRQ162,
    ALO_INTERRUPT_VECTOR_IRQ163,
    ALO_INTERRUPT_VECTOR_IRQ164,
    ALO_INTERRUPT_VECTOR_IRQ165,
    ALO_INTERRUPT_VECTOR_IRQ166,
    ALO_INTERRUPT_VECTOR_IRQ167,
    ALO_INTERRUPT_VECTOR_IRQ168,
    ALO_INTERRUPT_VECTOR_IRQ169,
    ALO_INTERRUPT_VECTOR_IRQ170,
    ALO_INTERRUPT_VECTOR_IRQ171,
    ALO_INTERRUPT_VECTOR_IRQ172,
    ALO_INTERRUPT_VECTOR_IRQ173,
    ALO_INTERRUPT_VECTOR_IRQ174,
    ALO_INTERRUPT_VECTOR_IRQ175,
    ALO_INTERRUPT_VECTOR_IRQ176,
    ALO_INTERRUPT_VECTOR_IRQ177,
    ALO_INTERRUPT_VECTOR_IRQ178,
    ALO_INTERRUPT_VECTOR_IRQ179,
    ALO_INTERRUPT_VECTOR_IRQ180,
    ALO_INTERRUPT_VECTOR_IRQ181,
    ALO_INTERRUPT_VECTOR_IRQ182,
    ALO_INTERRUPT_VECTOR_IRQ183,
    ALO_INTERRUPT_VECTOR_IRQ184,
    ALO_INTERRUPT_VECTOR_IRQ185,
    ALO_INTERRUPT_VECTOR_IRQ186,
    ALO_INTERRUPT_VECTOR_IRQ187,
    ALO_INTERRUPT_VECTOR_IRQ188,
    ALO_INTERRUPT_VECTOR_IRQ189,
    ALO_INTERRUPT_VECTOR_IRQ190,
    ALO_INTERRUPT_VECTOR_IRQ191,
    ALO_INTERRUPT_VECTOR_IRQ192,
    ALO_INTERRUPT_VECTOR_IRQ193,
    ALO_INTERRUPT_VECTOR_IRQ194,
    ALO_INTERRUPT_VECTOR_IRQ195,
    ALO_INTERRUPT_VECTOR_IRQ196,
    ALO_INTERRUPT_VECTOR_IRQ197,
    ALO_INTERRUPT_VECTOR_IRQ198,
    ALO_INTERRUPT_VECTOR_IRQ199,
    ALO_INTERRUPT_VECTOR_IRQ200,
    ALO_INTERRUPT_VECTOR_IRQ201,
    ALO_INTERRUPT_VECTOR_IRQ202,
    ALO_INTERRUPT_VECTOR_IRQ203,
    ALO_INTERRUPT_VECTOR_IRQ204,
    ALO_INTERRUPT_VECTOR_IRQ205,
    ALO_INTERRUPT_VECTOR_IRQ206,
    ALO_INTERRUPT_VECTOR_IRQ207,
    ALO_INTERRUPT_VECTOR_IRQ208,
    ALO_INTERRUPT_VECTOR_IRQ209,
    ALO_INTERRUPT_VECTOR_IRQ210,
    ALO_INTERRUPT_VECTOR_IRQ211,
    ALO_INTERRUPT_VECTOR_IRQ212,
    ALO_INTERRUPT_VECTOR_IRQ213,
    ALO_INTERRUPT_VECTOR_IRQ214,
    ALO_INTERRUPT_VECTOR_IRQ215,
    ALO_INTERRUPT_VECTOR_IRQ216,
    ALO_INTERRUPT_VECTOR_IRQ217,
    ALO_INTERRUPT_VECTOR_IRQ218,
    ALO_INTERRUPT_VECTOR_IRQ219,
    ALO_INTERRUPT_VECTOR_IRQ220,
    ALO_INTERRUPT_VECTOR_IRQ221,
    ALO_INTERRUPT_VECTOR_IRQ222,
    ALO_INTERRUPT_VECTOR_IRQ223,

    ALO_INTERRUPT_VECTOR_COUNT
} alo_interrupt_vector_t;

typedef enum {
    ALO_INTERRUPTS_SEGMENT_ERROR_TABLE_GDT = 0b00,
    ALO_INTERRUPTS_SEGMENT_ERROR_TABLE_IDT = 0b01,
    ALO_INTERRUPTS_SEGMENT_ERROR_TABLE_LDT = 0b10,
    ALO_INTERRUPTS_SEGMENT_ERROR_TABLE_IDT2 = 0b11
} alo_interrupts_segment_error_table_selector_t;

typedef struct GEN_PACKED {
    gen_bool_t external : 1;
    alo_interrupts_segment_error_table_selector_t table_selector : 2;
    gen_uint16_t index : 13;
    gen_uint16_t pad0;
} alo_interrupts_segment_error_t;

typedef struct GEN_PACKED {
    gen_bool_t present : 1; // true: Page-protection violation; false: Non-present page
    gen_bool_t write : 1; // true: Write; false: Read
    gen_bool_t user : 1; // true: CPL == 3;
    gen_bool_t reserved_write : 1; // true: Page directory sets reserved bit;
    gen_bool_t instruction_fetch : 1; // true: Fault caused by instruction fetch;
    // TODO: "The PKRU register (for user-mode accesses) or PKRS MSR (for supervisor-mode accesses) specifies the protection key rights."
    gen_bool_t protection_key : 1; // true: Fault caused by protection-key violation;
    gen_bool_t shadow_stack : 1; // true: Fault caused by shadow stack access;
    gen_uint8_t reserved0;
    // TODO: SGX seems to be deprecated
    gen_bool_t sgx_violation : 1; // true: Fault caused by SGX violation;
    gen_uint16_t reserved1;
} alo_interrupts_page_error_t;

typedef struct {
    alo_interrupt_vector_t vector;
    alo_registers_t registers;
    struct GEN_PACKED {
        union GEN_PACKED {
            gen_uint32_t error_code;

            gen_uint32_t double_fault; // Always 0
            alo_interrupts_segment_error_t invalid_tss; // `ss` selector
            alo_interrupts_segment_error_t segment_not_present; // Segment selector
            alo_interrupts_segment_error_t stack_segment_fault; // `ss` selector
            alo_interrupts_segment_error_t general_protection_fault; // Segment selector else 0
            alo_interrupts_page_error_t page_fault;
            gen_uint32_t alignment_check; // Always 0
            // TODO: See table at bottom of this file.
            gen_uint32_t vmm_communication; // `VM_EXIT` code
            gen_uint32_t security; // Always 1
        };
        gen_uint32_t pad0;
    } error_code;
    struct GEN_PACKED {
        alo_segment_selector_t ss;
        gen_uint64_t pad1 : 48;
    } ss;
    struct GEN_PACKED {
        alo_segment_selector_t cs;
        gen_uint64_t pad1 : 48;
    } cs;
} alo_exception_frame_t;


#define ALO_INTERRUPTS_NO_ERROR_CODE movl $0, %[error_code]
#define ALO_INTERRUPTS_ERROR_CODE popq %[error_code]

#define ALO_INTERRUPTS_ISR_BODY(exception_vector, frame, stub, ...) \
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
        GEN_ASM(.extern stub) \
        GEN_ASM(callq stub), \
        GEN_ASM(pushq %[ss]) \
        GEN_ASM(pushq %[rsp]) \
        GEN_ASM(pushq %[rflags]) \
        GEN_ASM(pushq %[cs]) \
        GEN_ASM(pushq %[rip]) \
        GEN_ASM(iretq) \
    : \
        /* Exception Entry Frame */ \
        [error_code ] "=m" (frame.error_code       ), \
        [rip        ] "=m" (frame.registers.rip    ), \
        [cs         ] "=m" (frame.cs               ), \
        [rflags     ] "=m" (frame.registers.rflags ), \
        [rsp        ] "=m" (frame.registers.rsp    ), \
        [ss         ] "=m" (frame.ss               ), \
        /* Exception Frame */ \
        [vector] "=m" (frame.vector       ), \
        [rax   ] "=m" (frame.registers.rax), \
        [rbx   ] "=m" (frame.registers.rbx), \
        [rcx   ] "=m" (frame.registers.rcx), \
        [rdx   ] "=m" (frame.registers.rdx), \
        [rsi   ] "=m" (frame.registers.rsi), \
        [rdi   ] "=m" (frame.registers.rdi), \
        [rbp   ] "=m" (frame.registers.rbp), \
        [r8    ] "=m" (frame.registers.r8 ), \
        [r9    ] "=m" (frame.registers.r9 ), \
        [r10   ] "=m" (frame.registers.r10), \
        [r11   ] "=m" (frame.registers.r11), \
        [r12   ] "=m" (frame.registers.r12), \
        [r13   ] "=m" (frame.registers.r13), \
        [r14   ] "=m" (frame.registers.r14), \
        [r15   ] "=m" (frame.registers.r15) \
    : \
        [exception_vector] "n" (exception_vector) \
    :)

extern gen_error_t* alo_interrupts_install_exception_handlers(void);
extern gen_error_t* alo_interrupts_install_irq_handlers(void);

#endif

/*
0h-Fh VMEXIT_CR[0-15]_READ read of CR 0 through 15, respectively
10h-1Fh VMEXIT_CR[0-15]_WRITE write of CR 0 through 15, respectively
20h-2Fh VMEXIT_DR[0-15]_READ read of DR 0 through 15, respectively
30h-3Fh VMEXIT_DR[0-15]_WRITE write of DR 0 through 15, respectively
40h-5Fh VMEXIT_EXCP[0-31] exception vector 0-31, respectively
60h VMEXIT_INTR physical INTR (maskable interrupt)
61h VMEXIT_NMI physical NMI
62h VMEXIT_SMI physical SMI (the EXITINFO1 field provides more information)
63h VMEXIT_INIT physical INIT
64h VMEXIT_VINTR virtual INTR
65h VMEXIT_CR0_SEL_WRITE write of CR0 that changed any bits other than CR0.TS or CR0.MP
66h VMEXIT_IDTR_READ read of IDTR
67h VMEXIT_GDTR_READ read of GDTR
68h VMEXIT_LDTR_READ read of LDTR
69h VMEXIT_TR_READ read of TR
6Ah VMEXIT_IDTR_WRITE write of IDTR
6Bh VMEXIT_GDTR_WRITE write of GDTR
6Ch VMEXIT_LDTR_WRITE write of LDTR
6Dh VMEXIT_TR_WRITE write of TR
6Eh VMEXIT_RDTSC RDTSC instruction
6Fh VMEXIT_RDPMC RDPMC instruction
70h VMEXIT_PUSHF PUSHF instruction
71h VMEXIT_POPF POPF instruction
72h VMEXIT_CPUID CPUID instruction
73h VMEXIT_RSM RSM instruction
74h VMEXIT_IRET IRET instruction
75h VMEXIT_SWINT software interrupt (INTn instructions)
76h VMEXIT_INVD INVD instruction
77h VMEXIT_PAUSE PAUSE instruction
78h VMEXIT_HLT HLT instruction[AMD Public Use]
79h VMEXIT_INVLPG INVLPG instructions
7Ah VMEXIT_INVLPGA INVLPGA instruction
7Bh VMEXIT_IOIO IN or OUT accessing protected port (the EXITINFO1 field provides more information)
7Ch VMEXIT_MSR RDMSR or WRMSR access to protected MSR
7Dh VMEXIT_TASK_SWITCH task switch
7Eh VMEXIT_FERR_FREEZE FP legacy handling enabled, and processor is frozen in an x87/mmx instruction waiting for an interrupt
7Fh VMEXIT_SHUTDOWN Shutdown
80h VMEXIT_VMRUN VMRUN instruction
81h VMEXIT_VMMCALL VMMCALL instruction
82h VMEXIT_VMLOAD VMLOAD instruction
83h VMEXIT_VMSAVE VMSAVE instruction
84h VMEXIT_STGI STGI instruction
85h VMEXIT_CLGI CLGI instruction
86h VMEXIT_SKINIT SKINIT instruction
87h VMEXIT_RDTSCP RDTSCP instruction
88h VMEXIT_ICEBP ICEBP instruction
89h VMEXIT_WBINVD WBINVD or WBNOINVD instruction
8Ah VMEXIT_MONITOR MONITOR or MONITORX instruction
8Bh VMEXIT_MWAIT MWAIT or MWAITX instruction
8Ch VMEXIT_MWAIT_CONDITIONAL MWAIT or MWAITX instruction, if monitor hardware is armed.
8Eh VMEXIT_RDPRU RDPRU instruction
8Dh VMEXIT_XSETBV XSETBV instruction
8Fh VMEXIT_EFER_WRITE_TRAP Write of EFER MSR (occurs after guest instruction finishes)
90h-9Fh VMEXIT_CR[0-15]_WRITE_TRAP Write of CR0-15, respectively (occurs after guest instruction finishes)
A0h VMEXIT_INVLPGB INVLPGB instruction
A1h VMEXIT_INVLPGB_ILLEGAL Illegal INVLPGB instruction
A2h VMEXIT_INVPCID INVPCID instruction
A3h VMEXIT_MCOMMIT MCOMMIT instruction
A4h VMEXIT_TLBSYNC TLBSYNC instruction
400h VMEXIT_NPF Nested paging: host-level page fault occurred (EXITINFO1 contains fault error code; EXITINFO2 contains the guest physical address causing the fault.)
401h AVIC_INCOMPLETE_IPI AVIC—Virtual IPI delivery not completed. See "AVIC IPI Delivery Not Completed" on page 582 for EXITINFO1-2 definitions.
402h AVIC_NOACCEL AVIC—Attempted access by guest to vAPIC register not handled by AVIC hardware. See "AVIC Access to Un-accelerated vAPIC register" on page 583 for EXITINFO1-2 definitions.
403h VMEXIT_VMGEXIT VMGEXIT instruction
F000_000h Unused Reserved for Host
-1 VMEXIT_INVALID Invalid guest state in VMCB
-2 VMEXIT_BUSY BUSY bit was set in the encrypted VMSA (see "Interrupt Injection Restrictions" on page 617).
-3 VMEXIT_IDLE_REQUIRED The sibling thread is not in an idle state (see "Side-Channel Protection" on page 618)
*/
