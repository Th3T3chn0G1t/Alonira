ALONIRA_QEMU_FLAGS = -monitor stdio $(ADDITIONAL_QEMU_FLAGS)
ALONIRA_OUT = alonira.iso

alonira: $(ALONIRA_OUT)

run: $(ALONIRA_OUT)
	@$(ECHO) "$(ACTION_PREFIX)qemu-system-x86_64 -cdrom $(ALONIRA_OUT) $(ALONIRA_QEMU_FLAGS)$(ACTION_SUFFIX)"
	@qemu-system-x86_64 -cdrom $(ALONIRA_OUT) $(ALONIRA_QEMU_FLAGS)

$(ALONIRA_OUT): $(HYPER_OUT) $(HYPER_INSTALL) $(ALOKERN_OUT)
	@$(ECHO) "$(ACTION_PREFIX)"
	$(XORRISO) -as mkisofs -b $(notdir $(HYPER_OUT)) -no-emul-boot -boot-load-size 4 -boot-info-table --protective-msdos-label boot -o $@
	$(HYPER_INSTALL) alonira.iso
	@$(ECHO) "$(ACTION_SUFFIX)"

clean_alonira:
	@$(ECHO) "$(ACTION_PREFIX)"
	-rm $(ALONIRA_OUT)
	@$(ECHO) "$(ACTION_SUFFIX)"
