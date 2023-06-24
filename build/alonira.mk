PLATFORM_SOURCEDIRS = alonira

LIB_PREFIX = lib
STATIC_LIB_SUFFIX = .a
OBJECT_SUFFIX = .o

ELF_SUFFIX = .elf

STATIC_LIB_TOOL = $(AR) rcs $@ $(filter %$(OBJECT_SUFFIX),$^)
ELF_TOOL = $(LLD) $(GLOBAL_LFLAGS) $(LFLAGS) $(addprefix -L,$(LIBDIRS)) \
			-o $@ $(filter %$(OBJECT_SUFFIX),$^)

GLOBAL_CFLAGS += -fno-pic -static -mcmodel=kernel -ffreestanding -fno-builtin \
					-fno-pic -mno-red-zone -mno-stack-arg-probe \
					-fno-strict-aliasing -fno-threadsafe-statics

GLOBAL_CFLAGS += -DGEN_THREAD_LOCAL=

ifeq ($(KERNEL_TARGET),x86_64)
	GLOBAL_CFLAGS += --target=x86_64-unknown-elf -mno-80387 -mno-mmx \
						-mno-3dnow -mno-sse -mno-sse2 -mgeneral-regs-only
	GLOBAL_LFLAGS += -static

	FDSFKJ = 432432

	BOOT_PROTOCOL = ULTRA
endif

%$(ELF_SUFFIX):
	$(ELF_TOOL)
