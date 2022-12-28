// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#ifndef ALO_KERNEL_IDT_H
#define ALO_KERNEL_IDT_H

#include "cpu.h"
#include "gdt.h"
#include "interrupts.h"

#include <gencommon.h>


typedef enum {
    ALO_IDT_GATE_TYPE_INTERRUPT = 0xE,
    ALO_IDT_GATE_TYPE_TRAP = 0xF
} alo_idt_gate_type_t;

#define ALO_IDT_MAKE_ENTRY(offset, ist, gate_type, privilege) ((alo_idt_entry_t) {(offset) & 0xFFFF, alo_gdt_selectors[ALO_GDT_INDEX_CODE], (ist), 0, (gate_type), gen_false, (privilege), gen_true, (offset) >> 16, 0})

typedef struct GEN_PACKED {
    gen_uint16_t offset_low;
    
    alo_segment_selector_t segment_selector;
    
    gen_uint8_t ist : 3;
    gen_uint8_t reserved0 : 5;
    
    alo_idt_gate_type_t gate_type : 4;
    gen_bool_t reserved1 : 1;
    alo_cpu_privilege_t privilege : 2;
    gen_bool_t present : 1;

    gen_uint64_t offset_high : 48;

    gen_uint32_t reserved2;
} alo_idt_entry_t;

typedef struct GEN_PACKED {
    gen_uint16_t size;
    alo_idt_entry_t* offset;
} alo_idt_pointer_t;

extern alo_idt_entry_t alo_idt[ALO_INTERRUPT_VECTOR_COUNT];
extern alo_idt_pointer_t alo_idtr;

extern gen_error_t* alo_idt_install(void);

#endif
