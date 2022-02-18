// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 TTG <prs.ttg+alonira@pm.me>

#include <alocom.h>
ALO_DIAGNOSTIC_REGION_BEGIN
ALO_DIAGNOSTIC_IGNORE_ALL
#include <stivale2.h>
ALO_DIAGNOSTIC_REGION_END

static unsigned char stack[8192];

typedef void (*stivale2_terminal_write_function_t)(const char*, unsigned long);
static struct stivale2_header_tag_terminal terminal_header_tag = {
    .tag = { .identifier = STIVALE2_HEADER_TAG_TERMINAL_ID, .next = 0 },
    .flags = 0
};
 
static struct stivale2_header_tag_framebuffer framebuffer_header_tag = {
    .tag = { .identifier = STIVALE2_HEADER_TAG_FRAMEBUFFER_ID, .next = (unsigned long) &terminal_header_tag },
    .framebuffer_width = 0,
    .framebuffer_height = 0,
    .framebuffer_bpp = 0
};
 
ALO_DIAGNOSTIC_REGION_BEGIN
#pragma clang diagnostic ignored "-Wgnu-binary-literal"
__attribute__((section(".stivale2hdr"), used))
static struct stivale2_header stivale_hdr = {
    .entry_point = 0,
    .stack = (unsigned long) stack + sizeof(stack),
    .flags = 0b00011110,
    .tags = (unsigned long) &framebuffer_header_tag
};
 
#pragma clang diagnostic ignored "-Wmissing-prototypes"
__unused void* stivale2_get_tag(const struct stivale2_struct* const restrict stivale2_struct, unsigned long id) {
    struct stivale2_tag* current_tag = (void*) stivale2_struct->tags;
    while(true) {
        if(current_tag->identifier == id) return current_tag;
        if(!(current_tag = (void*) current_tag->next)) return NULL;
    }
}

#pragma clang diagnostic ignored "-Wlanguage-extension-token"
noreturn static void hang(void) {
    while(true) asm ("hlt");
}

#pragma clang diagnostic ignored "-Wreserved-identifier"
noreturn __unused void _start(__unused const struct stivale2_struct* const restrict bootdata) {
    const struct stivale2_struct_tag_terminal* const terminal = stivale2_get_tag(bootdata, STIVALE2_STRUCT_TAG_TERMINAL_ID);
 
    if(!terminal) hang();
 
    stivale2_terminal_write_function_t terminal_write = (stivale2_terminal_write_function_t) terminal->term_write;
 
    terminal_write("Hello, world!", 13);

    hang();
}
ALO_DIAGNOSTIC_REGION_END
