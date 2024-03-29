ALONIRA_QEMU_FLAGS = -cpu qemu64,vendor=GenuineIntel
ALONIRA_OUT = $(ALONIRA_DIR)/alonira.iso

$(ALONIRA_OUT): $(ALO_KERNEL) $(wildcard $(ALONIRA_DIR)/boot/*)
ifeq ($(BOOT_PROTOCOL),ULTRA)
$(ALONIRA_OUT): BOOTLOADER_MBR = $(HYPER_OUT)
$(ALONIRA_OUT): $(HYPER_OUT) $(HYPER_INSTALL)
endif
	$(XORRISO) -as mkisofs -b $(subst $(ALONIRA_DIR)/boot,,$(BOOTLOADER_MBR)) -no-emul-boot -boot-load-size 4 -boot-info-table $(ALONIRA_DIR)/boot -o $@

.PHONY: run
run: $(ALONIRA_OUT)
	$(QEMU_X86_64) -cdrom $(ALONIRA_OUT) $(ALONIRA_QEMU_FLAGS) $(EXTRA_QEMU_FLAGS)

.PHONY: alonira
alonira: $(ALONIRA_OUT)

.PHONY: test_alonira
test_alonira:

.PHONY: clean_alonira
clean_alonira:
	$(RM) $(ALONIRA_OUT)
