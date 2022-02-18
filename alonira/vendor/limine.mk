LIMINE_OUT = boot/limine-cd.bin boot/limine.sys
LIMINE_INSTALL = alonira/vendor/limine/bin/limine-install

limine: | $(LIMINE_OUT) $(LIMINE_INSTALL)

$(LIMINE_OUT) $(LIMINE_INSTALL):
	@$(ECHO) "$(ACTION_PREFIX)"
	cd alonira/vendor/limine && ./autogen.sh
	cd alonira/vendor/limine && ./configure
	$(MAKE) -Calonira/vendor/limine
	cp alonira/vendor/limine/bin/limine-cd.bin boot
	cp alonira/vendor/limine/bin/limine.sys boot
	@$(ECHO) "$(ACTION_SUFFIX)"

clean_limine:
	@$(ECHO) "$(ACTION_PREFIX)"
	$(MAKE) -Calonira/vendor/limine clean
	-rm $(LIMINE_OUT)
	@$(ECHO) "$(ACTION_SUFFIX)"
