include $(ALONIRA_DIR)/alonira/vendor/hyper.mk

MODULE_NAMES += hyper

ALO_KERNEL_SOURCES = $(wildcard $(ALONIRA_DIR)/alonira/alokernel/*.c) $(wildcard $(ALONIRA_DIR)/alonira/alokernel/override/*.c)
ALO_KERNEL_OBJECTS = $(ALO_KERNEL_SOURCES:.c=$(TARGET_C64_OBJECT_SUFFIX))

ALO_KERNEL_OUT = $(ALONIRA_DIR)/boot/alonira$(TARGET_STATIC_OBJECT_SUFFIX)

ALO_KERNEL_CFLAGS = $(GEN_CORE_DIAGNOSTIC_CFLAGS) -Wno-reserved-identifier -Wno-language-extension-token
ALO_KERNEL_CFLAGS += -Wno-gnu-zero-variadic-macro-arguments -Wno-dollar-in-identifier-extension
ALO_KERNEL_CFLAGS += -Wno-gnu-binary-literal -Wno-missing-prototypes
ALO_KERNEL_CFLAGS += -DALO_BOOT_PROTOCOL_ULTRA=0 -DALO_BOOT_PROTOCOL=ALO_BOOT_PROTOCOL_$(BOOT_PROTOCOL) $(ALO_COMMON_CFLAGS)
ALO_KERNEL_LFLAGS = -Talonira/alokernel/kernel-generic.ld $(ALO_COMMON_LFLAGS)

ifeq ($(BOOT_PROTOCOL),ULTRA)
	ALO_KERNEL_CFLAGS += $(ULTRA_CFLAGS)
endif

$(ALO_KERNEL_OUT): TARGET_CFLAGS = $(ALO_KERNEL_CFLAGS)
$(ALO_KERNEL_OUT): TARGET_ASMFLAGS = -Wall
$(ALO_KERNEL_OUT): TARGET_LFLAGS = $(ALO_KERNEL_LFLAGS)
$(ALO_KERNEL_OUT): TARGET_LIBDIRS = $(ALO_COMMON_LIBDIRS)
$(ALO_KERNEL_OUT): $(ALO_KERNEL_OBJECTS) $(HYPER_OUT) $(ALO_COMMON_OUT) | $(ALONIRA_DIR)/boot

.PHONY: alokernel
alokernel: $(ALO_KERNEL_OUT)

.PHONY: test_alokernel
test_alokernel:

.PHONY: clean_alokernel
clean_alokernel:
	@$(ECHO) "$(ACTION_PREFIX)"
	-$(RM) $(ALO_KERNEL_OBJECTS)
	-$(RM) $(ALO_KERNEL_OUT)
	@$(ECHO) "$(ACTION_SUFFIX)"
