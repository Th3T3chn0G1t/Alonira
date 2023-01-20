// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#ifndef ALO_KERNEL_PAGING_H
#define ALO_KERNEL_PAGING_H

#include <gencommon.h>

#include <aloarchpagetables.h>

#include "alophysicalmemory.h"

extern gen_error_t* alo_arch_page_map(alo_physical_allocator_t* const restrict allocator, alo_page_table_entry_t* restrict * const restrict top_level, const gen_uintptr_t physical, const gen_uintptr_t virtual);
extern gen_error_t* alo_arch_page_map_range(alo_physical_allocator_t* const restrict allocator, alo_page_table_entry_t* restrict * const restrict top_level, const gen_uintptr_t physical, const gen_uintptr_t virtual, const gen_size_t count);
extern gen_error_t* alo_arch_translate_address(alo_page_table_entry_t* restrict * const restrict top_level, const gen_uintptr_t virtual, gen_uintptr_t* const restrict out_physical);

extern gen_error_t* alo_arch_page_flush(const alo_page_table_entry_t* const restrict top_level);

#endif
