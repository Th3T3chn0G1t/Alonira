// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#ifndef ALO_KERNEL_X86_64_CPU_H
#define ALO_KERNEL_X86_64_CPU_H

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

typedef union GEN_PACKED {
    struct GEN_PACKED {
        gen_bool_t protected_mode : 1;
        gen_bool_t await_coprocessor : 1;
        gen_bool_t emulate_coprocessor : 1;
        gen_bool_t task_switched : 1;
        gen_bool_t reserved0 : 1;
        gen_bool_t coprocessor_exceptions : 1;
        gen_uint16_t reserved1 : 10;
        gen_bool_t write_protect : 1;
        gen_bool_t reserved2 : 1;
        gen_bool_t alignment_check : 1;
        gen_uint16_t reserved3 : 10;
        gen_bool_t reserved4 : 1;
        gen_bool_t cache_disable : 1;
        gen_bool_t paging_enable : 1;
        gen_uint32_t reserved5;
    };
    alo_register_t cr0;
} alo_register_cr0_t;

typedef union GEN_PACKED {
    union {
        struct GEN_PACKED {
            gen_uint16_t pcid : 12;

            gen_uint64_t table_address : 40;
            gen_uint16_t reserved0 : 12;
        } pcid;
        struct GEN_PACKED {
            gen_uint8_t reserved0 : 3;
            gen_bool_t table_writethrough : 1;
            gen_bool_t table_cacheable : 1;
            gen_uint8_t reserved1 : 7;

            gen_uint64_t table_address : 40;
            gen_uint16_t reserved2 : 12;
        } no_pcid;
    };
    alo_register_t cr3;
} alo_register_cr3_t;

typedef union GEN_PACKED {
    union GEN_PACKED {
        gen_bool_t v8086_virtual_interrupts : 1;
        gen_bool_t protected_mode_virtual_interrupts : 1;
        gen_bool_t privileged_rdts : 1;
        gen_bool_t debug_extensions : 1;
        gen_bool_t page_size_extension : 1;
        gen_bool_t physical_address_extension : 1;
        gen_bool_t machine_check : 1;
        gen_bool_t page_global : 1;
        gen_bool_t performance_monitoring : 1;
        gen_bool_t legacy_sse : 1;
        gen_bool_t simd_fault : 1;
        gen_bool_t restrict_privileged_instructions : 1;
        gen_bool_t level_5_paging : 1;
        gen_uint8_t reserved0 : 3;
        gen_bool_t privileged_hidden_segments : 1;
        gen_bool_t pcid : 1;
        gen_bool_t xsave : 1;
        gen_bool_t reserved1 : 1;
        gen_bool_t restrict_privileged_execution : 1;
        gen_bool_t restrict_privileged_access : 1;
        gen_bool_t protection_keys : 1;
        gen_bool_t control_flow_enforcement : 1;
        gen_uint64_t reserved2 : 40;
    };
    alo_register_t cr4;
} alo_register_cr4_t;

#endif
