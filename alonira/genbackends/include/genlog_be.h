// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+genstone@pm.me>

#ifndef GEN_LOG_BE_H
#define GEN_LOG_BE_H

extern gen_error_t* gen_backends_alonira_log(const gen_log_level_t severity, const char* const restrict context, const char* const restrict string);

#endif
