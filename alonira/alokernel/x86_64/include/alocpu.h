// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#ifndef ALO_KERNEL_CPU_H
#define ALO_KERNEL_CPU_H

#include <gencommon.h>

typedef gen_uint64_t alo_register_t;

typedef enum {
    ALO_CPU_PRIVILEGE_RING0,
    ALO_CPU_PRIVILEGE_RING1,
    ALO_CPU_PRIVILEGE_RING2,
    ALO_CPU_PRIVILEGE_RING3
} alo_cpu_privilege_t;

typedef enum {
    ALO_SEGMENT_TABLE_GDT,
    ALO_SEGMENT_TABLE_LDT
} alo_segment_table_selector_t;

typedef union GEN_PACKED {
    struct GEN_PACKED {
        alo_cpu_privilege_t privilege : 2;
        alo_segment_table_selector_t table : 1;
        gen_uint16_t index : 13;
    };
    gen_uint16_t selector;
} alo_segment_selector_t;

typedef struct GEN_PACKED {
    gen_bool_t carry : 1;
    gen_bool_t reserved0 : 1;
    gen_bool_t parity : 1;
    gen_bool_t reserved1 : 1;
    gen_bool_t adjust : 1;
    gen_bool_t reserved2 : 1;
    gen_bool_t zero : 1;
    gen_bool_t sign : 1;
    gen_bool_t trap : 1;
    gen_bool_t interrupt : 1;
    gen_bool_t direction : 1;
    gen_bool_t overflow : 1;
    alo_cpu_privilege_t privilege : 2;
    gen_bool_t nested_task : 1;
    gen_bool_t reserved3 : 1;
    gen_bool_t resume : 1;
    gen_bool_t v8086 : 1;
    gen_bool_t alignment_check : 1;
    gen_bool_t vinterrupt : 1;
    gen_bool_t vinterrupt_pending : 1;
    gen_bool_t cpuid_usable : 1;

    gen_uint64_t reserved4 : 42;
} alo_flags_t;
    
typedef struct {
    union GEN_PACKED {
        alo_register_t registers[18];
        struct GEN_PACKED {
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

static GEN_FORCE_INLINE void alo_port_out_byte(const gen_uint16_t port, const gen_uint8_t value) {
    GEN_ASM_BLOCK(GEN_ASM(outb %[value], %[port]), :: [value]"a"(value), [port]"Nd"(port) :);
}

static GEN_FORCE_INLINE void alo_port_out_word(const gen_uint16_t port, const gen_uint16_t value) {
    GEN_ASM_BLOCK(GEN_ASM(outw %[value], %[port]), :: [value]"a"(value), [port]"Nd"(port) :);
}

static GEN_FORCE_INLINE gen_uint8_t alo_port_in_byte(const gen_uint16_t port) {
    gen_uint8_t out_value = 0;
    GEN_ASM_BLOCK(GEN_ASM(inb %[port], %[out_value]), : [out_value]"=a"(out_value) : [port]"Nd"(port) :);
    return out_value;
}

#endif