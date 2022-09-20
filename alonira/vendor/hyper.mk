HYPER_STAGE1_ASM_FLAGS = -DHYPER_ISO_BOOT_RECORD
HYPER_STAGE1_ASM_SOURCE = $(ALONIRA_DIR)/alonira/vendor/Hyper/bios/hyper_boot_record.asm
HYPER_STAGE1_OUT = $(HYPER_STAGE1_ASM_SOURCE:.asm=$(TARGET_RAW_SUFFIX))

$(HYPER_STAGE1_OUT): TARGET_RAW_ASMFLAGS = $(HYPER_STAGE1_ASM_FLAGS)
$(HYPER_STAGE1_OUT): $(HYPER_STAGE1_ASM_SOURCE)


HYPER_STAGE2_CFLAGS = -fno-stack-protector
HYPER_STAGE2_CFLAGS += -I$(ALONIRA_DIR)/alonira/vendor/Hyper/loader/include -I$(ALONIRA_DIR)/alonira/vendor/Hyper/loader/bios
HYPER_STAGE2_CFLAGS += -I$(ALONIRA_DIR)/alonira/vendor/Hyper/loader/common -I$(ALONIRA_DIR)/alonira/vendor/Hyper/loader/elf
HYPER_STAGE2_CFLAGS += -I$(ALONIRA_DIR)/alonira/vendor/Hyper/loader/filesystem -I$(ALONIRA_DIR)/alonira/vendor/Hyper/loader/boot_protocol
HYPER_STAGE2_CFLAGS += -I$(ALONIRA_DIR)/alonira/vendor/Hyper/loader/filesystem/fat -I$(ALONIRA_DIR)/alonira/vendor/Hyper/loader/filesystem/iso9660
HYPER_STAGE2_LFLAGS = -T$(ALONIRA_DIR)/alonira/vendor/Hyper/loader/bios/linker.ld

HYPER_STAGE2_ASM_SOURCES = $(wildcard alonira/vendor/Hyper/loader/bios/*.asm)
HYPER_STAGE2_C_SOURCES = $(wildcard alonira/vendor/Hyper/loader/*.c) $(wildcard alonira/vendor/Hyper/loader/common/*.c)
HYPER_STAGE2_C_SOURCES += $(wildcard alonira/vendor/Hyper/loader/elf/*.c) $(wildcard alonira/vendor/Hyper/loader/filesystem/*.c)
HYPER_STAGE2_C_SOURCES += $(wildcard alonira/vendor/Hyper/loader/filesystem/fat/*.c) $(wildcard alonira/vendor/Hyper/loader/filesystem/iso9660/*.c)
HYPER_STAGE2_C_SOURCES += $(wildcard alonira/vendor/Hyper/loader/boot_protocol/*.c) $(wildcard alonira/vendor/Hyper/loader/bios/*.c)
HYPER_STAGE2_OBJECTS = $(HYPER_STAGE2_ASM_SOURCES:.asm=$(TARGET_ASM32_OBJECT_SUFFIX)) $(HYPER_STAGE2_C_SOURCES:.c=$(TARGET_C32_OBJECT_SUFFIX))
HYPER_STAGE2_ELF = $(ALONIRA_DIR)/hyper_stage2$(TARGET_STATIC_OBJECT_SUFFIX)
HYPER_STAGE2_OUT = $(ALONIRA_DIR)/hyper_stage2$(TARGET_RAW_SUFFIX)

$(HYPER_STAGE2_ELF): TARGET_CFLAGS = $(HYPER_STAGE2_CFLAGS)
$(HYPER_STAGE2_ELF): TARGET_ASMFLAGS =
$(HYPER_STAGE2_ELF): TARGET_LFLAGS = $(HYPER_STAGE2_LFLAGS)
$(HYPER_STAGE2_ELF): $(HYPER_STAGE2_OBJECTS)

$(HYPER_STAGE2_OUT): $(HYPER_STAGE2_ELF)

HYPER_OUT = $(ALONIRA_DIR)/boot/hyper.bin

$(HYPER_OUT): $(HYPER_STAGE1_OUT) $(HYPER_STAGE2_OUT) | $(ALONIRA_DIR)/boot
	@$(ECHO) "$(ACTION_PREFIX)$(CAT) $^ > $@$(ACTION_SUFFIX)"
	@$(CAT) $^ > $@


HYPER_INSTALL_C_SOURCES = $(wildcard $(ALONIRA_DIR)/alonira/vendor/Hyper/installer/*.c)
HYPER_INSTALL_LOADERDATA_SOURCES = loaderdata_mbr.c loaderdata_iso_mbr.c loaderdata_stage2.c
HYPER_INSTALL_LOADERDATA_SOURCES := $(addprefix $(ALONIRA_DIR)/tmp/,$(HYPER_INSTALL_LOADERDATA_SOURCES))
HYPER_INSTALL_OBJECTS = $(HYPER_INSTALL_C_SOURCES:.c=$(HOST_OBJECT_SUFFIX)) $(HYPER_INSTALL_LOADERDATA_SOURCES:.c=$(HOST_OBJECT_SUFFIX))
HYPER_INSTALL = $(ALONIRA_DIR)/hyper_install$(HOST_EXECUTABLE_SUFFIX)

$(ALONIRA_DIR)/tmp/loaderdata_%.c: $(HYPER_STAGE1_OUT) $(HYPER_STAGE2_OUT) | $(ALONIRA_DIR)/tmp
	@$(ECHO) "$(ACTION_PREFIX)$(PYTHON3) $(ALONIRA_DIR)/alonira/vendor/Hyper/installer/dump_as_array.py $(HYPER_STAGE1_OUT) $@ $*$(ACTION_SUFFIX)"
	@$(PYTHON3) $(ALONIRA_DIR)/alonira/vendor/Hyper/installer/dump_as_array.py $(HYPER_STAGE1_OUT) $@ $*

$(HYPER_INSTALL): HOST_CFLAGS = -Wno-undef-prefix -Wno-nullability-completeness
$(HYPER_INSTALL): $(HYPER_INSTALL_OBJECTS)

ULTRA_CFLAGS = -I$(ALONIRA_DIR)/alonira/vendor/Hyper/loader/boot_protocol/ultra_protocol

# TODO: Investigate random `rm tmp/loaderdata_stage2.c tmp/loaderdata_mbr.c tmp/loaderdata_iso_mbr.c`

.PHONY: hyper
hyper: $(HYPER_OUT) $(HYPER_INSTALL)

.PHONY: test_hyper
test_hyper:

.PHONY: clean_hyper
clean_hyper:
	@$(ECHO) "$(ACTION_PREFIX)"
	-$(RM) $(HYPER_STAGE2_OBJECTS)
	-$(RM) $(HYPER_INSTALL_OBJECTS)
	-$(RM) $(HYPER_STAGE1_OUT)
	-$(RM) $(HYPER_STAGE2_OUT)
	-$(RM) $(HYPER_OUT)
	-$(RM) $(HYPER_INSTALL)
	@$(ECHO) "$(ACTION_SUFFIX)"
