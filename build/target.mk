ifeq ($(KERNEL_TARGET),X86_64)
	KERNEL_OBJECT_SUFFIX = .o.64
	KERNEL_ELF_SUFFIX = .elf.64
	KERNEL_STATIC_LIB_SUFFIX = .a.64

	KERNEL_CFLAGS += --target=x86_64-unknown-elf -mno-80387 -mno-mmx -mno-3dnow -mno-sse -mno-sse2 -mgeneral-regs-only
	KERNEL_LFLAGS += -static
endif
