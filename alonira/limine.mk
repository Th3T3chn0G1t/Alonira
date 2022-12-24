LIMINE_CONFIGURE = $(ALONIRA_DIR)/alonira/vendor/Limine/configure
LIMINE_MAKEFILE = $(ALONIRA_DIR)/alonira/vendor/Limine/GNUmakefile

LIMINE_INSTALL = $(ALONIRA_DIR)/alonira/vendor/Limine/bin/limine-deploy
LIMINE_BUILD_OUT = $(ALONIRA_DIR)/alonira/vendor/Limine/bin/limine-cd.bin
LIMINE_OUT = $(ALONIRA_DIR)/boot/boot/limine/limine-cd.bin
LIMINE_BUILD_SYS = $(ALONIRA_DIR)/alonira/vendor/Limine/bin/limine.sys
LIMINE_SYS = $(ALONIRA_DIR)/boot/boot/limine/limine.sys

LIMINE_CFLAGS = -I$(ALONIRA_DIR)/alonira/vendor/Limine

$(LIMINE_CONFIGURE):
	@$(ECHO) "$(ACTION_PREFIX)"
	$(ALONIRA_DIR)/alonira/vendor/Limine/bootstrap
	@$(ECHO) "$(ACTION_SUFFIX)"

$(LIMINE_MAKEFILE): $(LIMINE_CONFIGURE)
	@$(ECHO) "$(ACTION_PREFIX)"
	$(CD) $(dir $<) && ./$(notdir $<) --enable-bios --enable-bios-cd CC=$(CLANG) LD=$(LLD) CROSS_TOOLCHAIN=llvm CROSS_CC=$(CLANG) CROSS_LD=$(LLD) CROSS_OBJCOPY=$(OBJCOPY) CROSS_OBJDUMP=$(OBJDUMP) CROSS_READELF=$(READELF)
	@$(ECHO) "$(ACTION_SUFFIX)"

$(LIMINE_BUILD_OUT) $(LIMINE_BUILD_SYS) $(LIMINE_INSTALL): $(LIMINE_MAKEFILE)
	@$(ECHO) "$(ACTION_PREFIX)"
	$(MAKE) -C$(dir $<)
	@$(ECHO) "$(ACTION_SUFFIX)"

$(LIMINE_OUT): $(LIMINE_BUILD_OUT)
	@$(ECHO) "$(ACTION_PREFIX)$(CP) $< $@$(ACTION_SUFFIX)"
	@$(CP) $< $@

$(LIMINE_SYS): $(LIMINE_BUILD_SYS)
	@$(ECHO) "$(ACTION_PREFIX)$(CP) $< $@$(ACTION_SUFFIX)"
	@$(CP) $< $@

.PHONY: limine
limine: $(LIMINE_INSTALL) $(LIMINE_OUT)

.PHONY: test_limine
test_limine:

.PHONY: clean_limine
clean_limine: $(LIMINE_MAKEFILE)
	@$(ECHO) "$(ACTION_PREFIX)"
	$(MAKE) -C$(dir $<) maintainer-clean
	-$(RM) $(LIMINE_OUT)
	-$(RM) $(LIMINE_SYS)
	@$(ECHO) "$(ACTION_SUFFIX)"

