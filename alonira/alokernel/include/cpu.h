// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#ifndef ALO_KERNEL_CPU_H
#define ALO_KERNEL_CPU_H

#include <gencommon.h>
#include <alocommon.h>

typedef uint64_t alo_register_t;

typedef enum {
    ALO_CPU_PRIVILIGE_RING0 = 0,
    ALO_CPU_PRIVILIGE_RING1,
    ALO_CPU_PRIVILIGE_RING2,
    ALO_CPU_PRIVILIGE_RING3
} alo_cpu_privilige_t;

typedef enum {
    ALO_SEGMENT_TABLE_GDT = 0,
    ALO_SEGMENT_TABLE_LDT
} alo_segment_table_selector_t;

typedef struct ALO_PACKED {
    alo_cpu_privilige_t privilige : 2;
    alo_segment_table_selector_t table : 1;
    uint16_t index : 13;
} alo_segment_selector_t;

typedef struct ALO_PACKED {
    bool carry : 1;
    bool reserved0 : 1;
    bool parity : 1;
    bool reserved1 : 1;
    bool adjust : 1;
    bool reserved2 : 1;
    bool zero : 1;
    bool sign : 1;
    bool trap : 1;
    bool interrupt : 1;
    bool direction : 1;
    bool overflow : 1;
    alo_cpu_privilige_t privilige : 2;
    bool nested_task : 1;
    bool reserved3 : 1;
    bool resume : 1;
    bool v8086 : 1;
    bool alignment_check : 1;
    bool vinterrupt : 1;
    bool vinterrupt_pending : 1;
    bool cpuid_usable : 1;

    uint64_t reserved4 : 42;
} alo_flags_t;

#define ALO_STORE_REGISTERS(registers) \
    do { \
        ALO_ASM_BLOCK( \
            ALO_ASM(.__addr:) \
            ALO_ASM(pushfq) \
            ALO_ASM(popq 8*17(%[registers])) \
            ALO_ASM(mov %%rax, 8*0(%[registers])) \
            ALO_ASM(mov %%rbx, 8*1(%[registers])) \
            ALO_ASM(mov %%rcx, 8*2(%[registers])) \
            ALO_ASM(mov %%rdx, 8*3(%[registers])) \
            ALO_ASM(mov %%rsi, 8*4(%[registers])) \
            ALO_ASM(mov %%rdi, 8*5(%[registers])) \
            ALO_ASM(mov %%rbp, 8*6(%[registers])) \
            ALO_ASM(mov %%rsp, 8*7(%[registers])) \
            ALO_ASM(mov %%r8, 8*8(%[registers])) \
            ALO_ASM(mov %%r9, 8*9(%[registers])) \
            ALO_ASM(mov %%r10, 8*10(%[registers])) \
            ALO_ASM(mov %%r11, 8*11(%[registers])) \
            ALO_ASM(mov %%r12, 8*12(%[registers])) \
            ALO_ASM(mov %%r13, 8*13(%[registers])) \
            ALO_ASM(mov %%r14, 8*14(%[registers])) \
            ALO_ASM(mov %%r15, 8*15(%[registers])) \
            ALO_ASM(leaq .__addr(%%rip), %%rax) \
            ALO_ASM(mov %%rax, 8*16(%[registers])) \
        :: [registers]"r"(&registers) : "rax"); \
    } while(0)
    
typedef struct {
    union {
        alo_register_t registers[18];
        struct {
            alo_register_t rax;
            alo_register_t rbx;
            alo_register_t rcx;
            alo_register_t rdx;

            alo_register_t rsi;
            alo_register_t rdi;

            alo_register_t rbp;
            alo_register_t rsp;

            alo_register_t r8;
            alo_register_t r9;
            alo_register_t r10;
            alo_register_t r11;
            alo_register_t r12;
            alo_register_t r13;
            alo_register_t r14;
            alo_register_t r15;

            alo_register_t rip;

            union {
                alo_flags_t rflags;
                alo_register_t rfl;
            };
        };
    };
} alo_registers_t;

#endif