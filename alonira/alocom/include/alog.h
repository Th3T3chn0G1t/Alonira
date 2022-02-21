// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 TTG <prs.ttg+alonira@pm.me>

#ifndef ALO_LOG_H
#define ALO_LOG_H

#include "alocom.h"

typedef enum {
    TRACE,
    PERFORMANCE,
    NOTE,
    INFO,
    WARNING,
    ERROR,
    FATAL
} alo_log_level_t;

void alog(const alo_log_level_t level, const char* const restrict string);

#endif
