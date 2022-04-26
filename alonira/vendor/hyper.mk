HYPER_STAGE1_ASM_SOURCE = alonira/vendor/hyper/bios/hyper_boot_record.asm
HYPER_STAGE1_OUT = $(HYPER_STAGE1_ASM_SOURCE:.asm=.bin)

$(HYPER_STAGE1_OUT): $(HYPER_STAGE1_ASM_SOURCE)


HYPER_STAGE2_ASM_FLAGS = -felf32
HYPER_STAGE2_C_FLAGS = --target=i686-none-eabi -fno-stack-protector $(FREESTANDING_C_FLAGS) -Wno-ignored-attributes
HYPER_STAGE2_C_FLAGS += -Wno-reserved-identifier -Ialonira/vendor/hyper/loader -Ialonira/vendor/hyper/loader/bios -Ialonira/vendor/hyper/loader/common -Ialonira/vendor/hyper/loader/elf -Ialonira/vendor/hyper/loader/filesystem -Ialonira/vendor/hyper/loader/protocols -Ialonira/vendor/hyper/loader/filesystem/fat -Ialonira/vendor/hyper/loader/filesystem/iso9660
HYPER_STAGE2_L_FLAGS = --target=i686-none-eabi -Talonira/vendor/hyper/loader/bios/linker.ld -fno-stack-protector

HYPER_STAGE2_ASM_SOURCES = $(wildcard alonira/vendor/hyper/loader/bios/*.asm)
HYPER_STAGE2_C_SOURCES = $(wildcard alonira/vendor/hyper/loader/*.c) $(wildcard alonira/vendor/hyper/loader/common/*.c) $(wildcard alonira/vendor/hyper/loader/elf/*.c) $(wildcard alonira/vendor/hyper/loader/filesystem/*.c) $(wildcard alonira/vendor/hyper/loader/filesystem/fat/*.c) $(wildcard alonira/vendor/hyper/loader/filesystem/iso9660/*.c) $(wildcard alonira/vendor/hyper/loader/protocols/*.c) $(wildcard alonira/vendor/hyper/loader/bios/*.c)
HYPER_STAGE2_OBJECTS = $(HYPER_STAGE2_ASM_SOURCES:.asm=$(OBJECT_SUFFIX)) $(HYPER_STAGE2_C_SOURCES:.c=$(OBJECT_SUFFIX))
HYPER_STAGE2_ELF = hyper_stage2$(ELF_SUFFIX)
HYPER_STAGE2_OUT = hyper_stage2$(BIN_SUFFIX)

# This is super hacky
$(HYPER_STAGE2_OUT): GLOBAL_C_FLAGS := $(filter-out -fsanitize=undefined,$(GLOBAL_C_FLAGS))
$(HYPER_STAGE2_OUT): CLANG_FORMAT = DISABLED
$(HYPER_STAGE2_OUT): ASMFLAGS = $(HYPER_STAGE2_ASM_FLAGS)
$(HYPER_STAGE2_OUT): CFLAGS = $(HYPER_STAGE2_C_FLAGS)
$(HYPER_STAGE2_OUT): LFLAGS = $(HYPER_STAGE2_L_FLAGS) -L/usr/local/llvm/lib/clang/14.0.0/lib/linux/ -lclang_rt.builtins-i386

$(HYPER_STAGE2_ELF): $(HYPER_STAGE2_OBJECTS)


HYPER_INSTALL_C_SOURCES = $(wildcard alonira/vendor/hyper/installer/*.c)
HYPER_INSTALL_OBJECTS = $(HYPER_INSTALL_C_SOURCES:.c=$(OBJECT_SUFFIX))
HYPER_INSTALL = hyper_install.out

# We need usermode tools \[0]/
$(HYPER_INSTALL): GLOBAL_C_FLAGS =
$(HYPER_INSTALL): GLOBAL_L_FLAGS =
$(HYPER_INSTALL): $(HYPER_INSTALL_OBJECTS) | $(HYPER_STAGE1_OUT) $(HYPER_STAGE2_OUT)

hyper: $(HYPER_STAGE1_OUT) $(HYPER_STAGE2_OUT) $(HYPER_INSTALL)

clean_hyper:
	@$(ECHO) "$(ACTION_PREFIX)"
	-rm $(HYPER_STAGE2_OBJECTS)
	-rm $(HYPER_INSTALL_OBJECTS)

	-rm $(HYPER_STAGE1_OUT)
	-rm $(HYPER_STAGE2_OUT)
	-rm $(HYPER_INSTALL)
	@$(ECHO) "$(ACTION_SUFFIX)"
