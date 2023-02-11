// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2023 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include <tanaibpb.h>
#include <tanaitable.h>

#include <gencommon.h>
#include <genfilesystem.h>

static gen_error_t* gen_main(void) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) gen_main, GEN_FILE_NAME);
    if(error) return error;

    tanai_fat_type_t type = TANAI_TYPE_FAT12;

    tanai_bpb_t bpb = {0};
    error = tanai_bpb_create(type, 1, 1, 1, 0, TANAI_BPB_LABEL_NONAME, &bpb);
    if(error) return error;

    error = gen_filesystem_path_create_file("tanai.img", sizeof("tanai.img"), sizeof("tanai.img") - 1);
    if(error) return error;

    gen_filesystem_handle_t handle = {0};
    error = gen_filesystem_handle_open("tanai.img", sizeof("tanai.img"), sizeof("tanai.img") - 1, &handle);
    if(error) return error;

    error = gen_filesystem_handle_file_write(&handle, 0, (void*) &bpb, sizeof(bpb));
    if(error) return error;

    gen_uint8_t fat[512] = {0};
    error = tanai_fat_init(type, &bpb, (void*) fat);

    error = gen_filesystem_handle_file_write(&handle, sizeof(bpb), fat, sizeof(fat));
    if(error) return error;

    gen_uint8_t data[512] = {0};
    error = gen_filesystem_handle_file_write(&handle, sizeof(bpb) + sizeof(fat), data, sizeof(data));
    if(error) return error;

    error = gen_filesystem_handle_close(&handle);
    if(error) return error;

    return GEN_NULL;
}

int main(void) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) main, GEN_FILE_NAME);
    if(error) gen_error_abort_with_error(error, "tanai-writer");

    error = gen_main();
    if(error) gen_error_abort_with_error(error, "tanai-writer");
}
