ALO_KERNEL_CFLAGS += -Wno-reserved-identifier # We're a kernel - I think we can safely say we're allowed use reserved identifiers ;^)
ALO_KERNEL_CFLAGS += -Wno-gnu-binary-literal

ALO_KERNEL_CFLAGS += -Wno-dollar-in-identifier-extension # TODO: Remove once clang fixes this

ALO_KERNEL_CFLAGS += -DALO_BOOT_PROTOCOL_ULTRA=1
ifeq ($(BOOT_PROTOCOL),ULTRA)
	ALO_KERNEL_CFLAGS += -DALO_BOOT_PROTOCOL=ALO_BOOT_PROTOCOL_ULTRA
endif

ALO_KERNEL_SOURCES = $(wildcard $(ALONIRA_DIR)/alonira/alokernel/*.c)
ALO_KERNEL_OBJECTS = $(ALO_KERNEL_SOURCES:.c=$(KERNEL_OBJECT_SUFFIX))

ALO_KERNEL = $(ALONIRA_DIR)/boot/alonira$(KERNEL_ELF_SUFFIX)

ALO_KERNEL_SANITIZERS = undefined

$(ALO_KERNEL): CFLAGS = $(GEN_CORE_CFLAGS) $(ULTRA_CFLAGS) $(GENSTONE_DIAGNOSTIC_CFLAGS) $(ALO_KERNEL_CFLAGS)
$(ALO_KERNEL): LFLAGS = $(GEN_CORE_LFLAGS) -T$(ALONIRA_DIR)/alonira/alokernel/kernel-generic.ld
$(ALO_KERNEL): SANITIZERS = $(ALO_KERNEL_SANITIZERS)
$(ALO_KERNEL): LIBDIRS = $(GEN_CORE_LIBDIRS)
$(ALO_KERNEL): $(ALO_KERNEL_OBJECTS)

.PHONY: alokernel
alokernel: $(ALO_KERNEL)

.PHONY: test_alokernel
test_alokernel:

.PHONY: clean_alokernel
clean_alokernel:
	@$(ECHO) "$(ACTION_PREFIX)"
	-$(RM) $(ALO_KERNEL_OBJECTS)
	-$(RM) $(ALO_KERNEL)
	@$(ECHO) "$(ACTION_SUFFIX)"
