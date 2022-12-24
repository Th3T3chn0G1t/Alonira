// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+genstone@pm.me>

#ifndef GEN_BACKENDS_H
#define GEN_BACKENDS_H

// Since we obviously don't have dynamic symbol resolution in the kernel, we need to include all backends headers here.

#define GEN_BACKENDS_CALL(function_top_level) gen_backends_alonira_##function_top_level

#endif
