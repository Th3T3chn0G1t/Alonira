ALONIRA_QEMU_FLAGS =
ALONIRA_OUT = $(ALONIRA_DIR)/alonira.iso

$(ALONIRA_DIR)/boot:
	@$(ECHO) "$(ACTION_PREFIX)$(MKDIR) $@$(ACTION_SUFFIX)"
	-@$(MKDIR) $@

.PHONY: run
run: $(ALONIRA_OUT)
	@$(ECHO) "$(ACTION_PREFIX)qemu-system-x86_64 -cdrom $(ALONIRA_OUT) $(ALONIRA_QEMU_FLAGS) $(EXTRA_QEMU_FLAGS)$(ACTION_SUFFIX)"
	@$(QEMU_X86_64) -cdrom $(ALONIRA_OUT) $(ALONIRA_QEMU_FLAGS) $(EXTRA_QEMU_FLAGS)

ifeq ($(BOOT_PROTOCOL),ULTRA)
$(ALONIRA_OUT): $(HYPER_OUT) $(HYPER_INSTALL) $(ALO_KERNEL_OUT) $(ALONIRA_DIR)/boot
	@$(ECHO) "$(ACTION_PREFIX)"
	$(XORRISO) -as mkisofs -b $(notdir $(HYPER_OUT)) -no-emul-boot -boot-load-size 4 -boot-info-table --protective-msdos-label $(ALONIRA_DIR)/boot -o $@
	$(HYPER_INSTALL) $@
	@$(ECHO) "$(ACTION_SUFFIX)"
endif

.PHONY: image
image: $(ALONIRA_OUT)

.PHONY: test_image
test_image: $(ALONIRA_OUT)

.PHONY: clean_image
clean_image:
	@$(ECHO) "$(ACTION_PREFIX)"
	-$(RM) $(ALONIRA_OUT)
	-$(RMDIR) $(ALONIRA_DIR)/lib
	@$(ECHO) "$(ACTION_SUFFIX)"
