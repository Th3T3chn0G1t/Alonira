// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 TTG <prs.ttg+alonira@pm.me>

#include "include/alomemory.h"

alo_error_t alo_memory_set(void* const restrict address, const unsigned long length, const unsigned char value) {
	ALO_FRAME_BEGIN(alo_memory_set);

	ALO_NULL_CHECK(address);

	for(unsigned char* d = address; (unsigned long) (d - (unsigned char*) address) < length; ++d) {
		*d = value;
	}

	ALO_ALL_OK;
}
