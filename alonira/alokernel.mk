KERNEL_CFLAGS += -DGEN_THREAD_LOCAL=""

ALO_KERNEL_CFLAGS += -I$(ALONIRA_DIR)/alonira/alokernel/include -I$(ALONIRA_DIR)/alonira/alokernel/$(KERNEL_TARGET)/include -I$(ALONIRA_DIR)/alonira/alokernel/$(KERNEL_TARGET)/include/exposed

ALO_TODO_COUNT := $(shell $(CAT) $(shell $(FIND) $(ALONIRA_DIR) $(FIND_FNAME)  "*.c") $(shell $(FIND) $(ALONIRA_DIR) $(FIND_FNAME) "*.h") | $(GREP) "TODO:" | $(LINECOUNT) | $(MKNUMERIC))

ALO_KERNEL_CFLAGS += -DALO_TODO_COUNT=$(ALO_TODO_COUNT)
ALO_KERNEL_CFLAGS += -Wno-reserved-identifier # We're a kernel - I think we can safely say we're allowed use reserved identifiers ;^)
ALO_KERNEL_CFLAGS += -Wno-gnu-binary-literal -Wno-c++-compat -Wno-gnu-empty-struct

ALO_KERNEL_CFLAGS += -Wno-dollar-in-identifier-extension # TODO: Remove once clang fixes this

ifeq ($(BOOT_PROTOCOL),ULTRA)
	ALO_KERNEL_CFLAGS += $(ULTRA_CFLAGS)
endif

ALO_KERNEL_SOURCES = $(wildcard $(ALONIRA_DIR)/alonira/alokernel/*.c) $(wildcard $(ALONIRA_DIR)/alonira/alokernel/$(KERNEL_TARGET)/*.c) $(wildcard $(ALONIRA_DIR)/alonira/alokernel/instrumentation/*.c)
ALO_KERNEL_OBJECTS = $(ALO_KERNEL_SOURCES:.c=$(KERNEL_OBJECT_SUFFIX))

ALO_KERNEL = $(ALONIRA_DIR)/boot/boot/alonira$(KERNEL_ELF_SUFFIX)

ALO_KERNEL_SANITIZERS = undefined

$(ALO_KERNEL): CFLAGS = $(KERNEL_GEN_CORE_CFLAGS) $(KERNEL_TANAI_CFLAGS) $(GENSTONE_DIAGNOSTIC_CFLAGS) $(ALO_KERNEL_CFLAGS)
$(ALO_KERNEL): LFLAGS = $(KERNEL_GEN_CORE_LIB) $(KERNEL_TANAI_LIB) -T$(ALONIRA_DIR)/alonira/alokernel/scripts/kernel-$(KERNEL_TARGET).ld $(GEN_BACKENDS_ALONIRA_LIB)
$(ALO_KERNEL): SANITIZERS = $(ALO_KERNEL_SANITIZERS)
$(ALO_KERNEL): LIBDIRS = $(KERNEL_GEN_CORE_LIBDIRS) $(KERNEL_TANAI_LIBDIRS)
$(ALO_KERNEL): $(ALO_KERNEL_OBJECTS) $(KERNEL_GEN_CORE_LIB) $(KERNEL_TANAI_LIB)

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
