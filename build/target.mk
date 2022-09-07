ifeq ($(ARCH), x86_64)
	TARGET_LIB_PREFIX = lib
	TARGET_STATIC_LIB_SUFFIX = .target.a
	TARGET_C_OBJECT_SUFFIX = .target.c.o
	TARGET_ASM_OBJECT_SUFFIX = .target.asm.o
	TARGET_STATIC_OBJECT_SUFFIX = .target.elf

	TARGET_GLOBAL_CFLAGS += --target=x86_64-unknown-none
	TARGET_GLOBAL_ASMFLAGS += -felf64
	TARGET_GLOBAL_LFLAGS += --target=x86_64-unknown-none

	TARGET_STATIC_LIB_TOOL = $(AR) -r -c $@ $(filter %$(TARGET_C_OBJECT_SUFFIX),$^)
	TARGET_STATIC_OBJECT_TOOL = $(LLD) -flavour ld -static $(TARGET_GLOBAL_LFLAGS) $(addprefix -L,$(TARGET_LIBDIRS)) $(TARGET_LFLAGS) -o $@ $(filter %$(TARGET_C_OBJECT_SUFFIX),$^)
endif
