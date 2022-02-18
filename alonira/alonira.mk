ALONIRA_OUT = alonira.iso

alonira: $(ALONIRA_OUT)

$(ALONIRA_OUT): $(LIMINE_INSTALL) $(ALOKERN_OUT) boot/limine.cfg
	@$(ECHO) "$(ACTION_PREFIX)"
	$(XORRISO) -as mkisofs -b limine-cd.bin -no-emul-boot -boot-load-size 4 -boot-info-table --protective-msdos-label boot -o alonira.iso
	$(LIMINE_INSTALL) alonira.iso
	@$(ECHO) "$(ACTION_SUFFIX)"

clean_alonira:
	@$(ECHO) "$(ACTION_PREFIX)"
	-rm $(ALONIRA_OUT)
	@$(ECHO) "$(ACTION_SUFFIX)"
