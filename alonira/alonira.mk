ALONIRA_QEMU_FLAGS = -monitor stdio

ifeq ($(BOOT_PROTOCOL),STIVALE)

ALONIRA_OUT = alonira.iso

alonira: $(ALONIRA_OUT)

run: $(ALONIRA_OUT)
	@$(ECHO) "$(ACTION_PREFIX)qemu-system-x86_64 -cdrom $(ALONIRA_OUT) $(ALONIRA_QEMU_FLAGS)$(ACTION_SUFFIX)"
	@qemu-system-x86_64 -cdrom $(ALONIRA_OUT) $(ALONIRA_QEMU_FLAGS)


$(ALONIRA_OUT): $(LIMINE_INSTALL) $(ALOKERN_OUT) boot/limine.cfg
	@$(ECHO) "$(ACTION_PREFIX)"
	$(XORRISO) -as mkisofs -b limine-cd.bin -no-emul-boot -boot-load-size 4 -boot-info-table --protective-msdos-label boot -o alonira.iso
	$(LIMINE_INSTALL) alonira.iso
	@$(ECHO) "$(ACTION_SUFFIX)"

clean_alonira:
	@$(ECHO) "$(ACTION_PREFIX)"
	-rm $(ALONIRA_OUT)
	@$(ECHO) "$(ACTION_SUFFIX)"

else

ALONIRA_OUT = alonira.img

alonira: $(ALONIRA_OUT)

run: all
	@$(ECHO) "$(ACTION_PREFIX)qemu-system-x86_64 -hda $(ALONIRA_OUT) $(ALONIRA_QEMU_FLAGS)$(ACTION_SUFFIX)"
	@qemu-system-x86_64 -hda $(ALONIRA_OUT) $(ALONIRA_QEMU_FLAGS)

$(ALONIRA_OUT): $(HYPER_INSTALL) $(ALOKERN_OUT) boot/hyper.cfg
	@$(ECHO) "$(ACTION_PREFIX)"
	-rm $(ALONIRA_OUT)
	dd if=/dev/zero bs=1M count=0 seek=128 of=$(ALONIRA_OUT)
	parted -s $(ALONIRA_OUT) mklabel msdos
	parted -s $(ALONIRA_OUT) mkpart primary 1 100%
	-mkdir mnt
	sudo $(SHELL) -c 'DEV=$$(losetup -L -P --show -f $(ALONIRA_OUT)); mkfs.vfat -F 32 $$DEV"p1"; mount $$DEV"p1" --target mnt; cp boot/* mnt; umount $$DEV"p1"; losetup --detach $$DEV'
	-rm -rf mnt
	$(HYPER_INSTALL) $(ALONIRA_OUT)
	@$(ECHO) "$(ACTION_SUFFIX)"

clean_alonira:
	@$(ECHO) "$(ACTION_PREFIX)"
	-rm $(ALONIRA_OUT)
	@$(ECHO) "$(ACTION_SUFFIX)"

endif

