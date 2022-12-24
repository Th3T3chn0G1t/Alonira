ALONIRA_QEMU_FLAGS = -cpu qemu64,vendor=GenuineIntel
ALONIRA_OUT = $(ALONIRA_DIR)/alonira.iso

ifeq ($(BOOT_PROTOCOL),ULTRA)
$(ALONIRA_OUT): $(HYPER_OUT) $(HYPER_INSTALL) $(ALO_KERNEL) $(wildcard $(ALONIRA_DIR)/boot/*)
	@$(ECHO) "$(ACTION_PREFIX)"
	$(XORRISO) -as mkisofs -b $(notdir $(HYPER_OUT)) -no-emul-boot -boot-load-size 4 -boot-info-table --protective-msdos-label $(ALONIRA_DIR)/boot -o $@
	$(HYPER_INSTALL) $@
	@$(ECHO) "$(ACTION_SUFFIX)"
endif

.PHONY: run
run: $(ALONIRA_OUT)
	@$(ECHO) "$(ACTION_PREFIX)$(QEMU_X86_64) -cdrom $(ALONIRA_OUT) $(ALONIRA_QEMU_FLAGS) $(EXTRA_QEMU_FLAGS)$(ACTION_SUFFIX)"
	@$(QEMU_X86_64) -cdrom $(ALONIRA_OUT) $(ALONIRA_QEMU_FLAGS) $(EXTRA_QEMU_FLAGS)

.PHONY: alonira
alonira: $(ALONIRA_OUT)

.PHONY: test_alonira
test_alonira:

.PHONY: clean_alonira
clean_alonira:
