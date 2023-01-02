KERNEL_OBJECT_SUFFIX = .o.$(KERNEL_TARGET)
KERNEL_ELF_SUFFIX = .elf.$(KERNEL_TARGET)
KERNEL_STATIC_LIB_SUFFIX = .a.$(KERNEL_TARGET)

ifeq ($(KERNEL_TARGET),x86_64)
	KERNEL_CFLAGS += --target=x86_64-unknown-elf -mno-80387 -mno-mmx -mno-3dnow -mno-sse -mno-sse2 -mgeneral-regs-only
	KERNEL_LFLAGS += -static

	TARGET_LLD = -flavor ld

	BOOT_PROTOCOL = ULTRA
endif
