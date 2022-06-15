HYPER_STAGE1_ASM_FLAGS = -DHYPER_ISO_BOOT_RECORD
HYPER_STAGE1_ASM_SOURCE = alonira/vendor/alonira-hyper/bios/hyper_boot_record.asm
HYPER_STAGE1_OUT = $(HYPER_STAGE1_ASM_SOURCE:.asm=.bin)

$(HYPER_STAGE1_OUT): ASMFLAGS = $(HYPER_STAGE1_ASM_FLAGS)
$(HYPER_STAGE1_OUT): $(HYPER_STAGE1_ASM_SOURCE)


HYPER_STAGE2_ASM_FLAGS = -felf32
HYPER_STAGE2_C_FLAGS = -march=i686 -m32 --target=i686-none-unknown-elf -fno-stack-protector $(FREESTANDING_C_FLAGS)
HYPER_STAGE2_C_FLAGS += -Wno-ignored-attributes -Wno-unknown-warning-option -Wno-reserved-identifier
HYPER_STAGE2_C_FLAGS += -Ialonira/vendor/alonira-hyper/loader -Ialonira/vendor/alonira-hyper/loader/bios -Ialonira/vendor/alonira-hyper/loader/common -Ialonira/vendor/alonira-hyper/loader/elf -Ialonira/vendor/alonira-hyper/loader/filesystem -Ialonira/vendor/alonira-hyper/loader/protocols -Ialonira/vendor/alonira-hyper/loader/filesystem/fat -Ialonira/vendor/alonira-hyper/loader/filesystem/iso9660
HYPER_STAGE2_L_FLAGS = -march=i686 -m32 --target=i686-none-unknown-elf -Talonira/vendor/alonira-hyper/loader/bios/linker.ld $(FREESTANDING_L_FLAGS)

HYPER_STAGE2_ASM_SOURCES = $(wildcard alonira/vendor/alonira-hyper/loader/bios/*.asm)
HYPER_STAGE2_C_SOURCES = $(wildcard alonira/vendor/alonira-hyper/loader/*.c) $(wildcard alonira/vendor/alonira-hyper/loader/common/*.c) $(wildcard alonira/vendor/alonira-hyper/loader/elf/*.c) $(wildcard alonira/vendor/alonira-hyper/loader/filesystem/*.c) $(wildcard alonira/vendor/alonira-hyper/loader/filesystem/fat/*.c) $(wildcard alonira/vendor/alonira-hyper/loader/filesystem/iso9660/*.c) $(wildcard alonira/vendor/alonira-hyper/loader/protocols/*.c) $(wildcard alonira/vendor/alonira-hyper/loader/bios/*.c)
HYPER_STAGE2_OBJECTS = $(HYPER_STAGE2_ASM_SOURCES:.asm=.asm$(OBJECT_SUFFIX)) $(HYPER_STAGE2_C_SOURCES:.c=.c$(OBJECT_SUFFIX))
HYPER_STAGE2_ELF = hyper_stage2$(ELF_SUFFIX)
HYPER_STAGE2_OUT = hyper_stage2$(BIN_SUFFIX)

$(HYPER_STAGE2_OUT): LFLAGS = $(HYPER_STAGE2_L_FLAGS)
$(HYPER_STAGE2_OUT): $(HYPER_STAGE2_ELF)

$(HYPER_STAGE2_ELF): CLANG_FORMAT = DISABLED
$(HYPER_STAGE2_ELF): ASMFLAGS = $(HYPER_STAGE2_ASM_FLAGS)
$(HYPER_STAGE2_ELF): CFLAGS = $(HYPER_STAGE2_C_FLAGS)
$(HYPER_STAGE2_ELF): LFLAGS = $(HYPER_STAGE2_L_FLAGS)
$(HYPER_STAGE2_ELF): $(HYPER_STAGE2_OBJECTS)

HYPER_OUT = boot/hyper.bin

$(HYPER_OUT): $(HYPER_STAGE1_OUT) $(HYPER_STAGE2_OUT)
	cat $^ > $@


HYPER_INSTALL_C_SOURCES = $(wildcard alonira/vendor/alonira-hyper/installer/*.c)
HYPER_INSTALL_LOADERDATA_SOURCES = tmp/loaderdata_mbr.c tmp/loaderdata_iso_mbr.c tmp/loaderdata_stage2.c
HYPER_INSTALL_OBJECTS = $(HYPER_INSTALL_C_SOURCES:.c=.c$(OBJECT_SUFFIX)) $(HYPER_INSTALL_LOADERDATA_SOURCES:.c=.c$(OBJECT_SUFFIX))
HYPER_INSTALL = ./hyper_install$(EXECUTABLE_SUFFIX)

tmp/loaderdata_%.c: $(HYPER_STAGE1_OUT) $(HYPER_STAGE2_OUT) | tmp
	$(PYTHON3) alonira/vendor/alonira-hyper/installer/dump_as_array.py $(HYPER_STAGE1_OUT) $@ $*

$(HYPER_INSTALL_OBJECTS): $(HYPER_INSTALL_C_SOURCES) $(HYPER_INSTALL_LOADERDATA_SOURCES)

$(HYPER_INSTALL): CLANG_FORMAT = DISABLED
$(HYPER_INSTALL): $(HYPER_INSTALL_OBJECTS)


ULTRA_C_FLAGS = -Ialonira/vendor/alonira-hyper/loader/protocols/ultra_protocol


hyper: $(HYPER_OUT) $(HYPER_INSTALL)

clean_hyper:
	@$(ECHO) "$(ACTION_PREFIX)"
	-rm $(HYPER_STAGE2_OBJECTS)
	-rm $(HYPER_INSTALL_OBJECTS)
	-rm $(HYPER_STAGE1_OUT)
	-rm $(HYPER_STAGE2_OUT)
	-rm $(HYPER_OUT)
	-rm $(HYPER_INSTALL)
	@$(ECHO) "$(ACTION_SUFFIX)"
