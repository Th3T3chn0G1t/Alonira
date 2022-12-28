HYPER_CMAKE_CACHE = $(ALONIRA_DIR)/alonira/vendor/Hyper/build
HYPER_INSTALL = $(ALONIRA_DIR)/alonira/vendor/Hyper/installer/hyper_install
HYPER_BUILD_OUT = $(ALONIRA_DIR)/alonira/vendor/Hyper/build/loader/hyper_iso_boot
HYPER_OUT = $(ALONIRA_DIR)/boot/boot/hyper/hyper_iso_boot

ULTRA_CFLAGS = -I$(ALONIRA_DIR)/alonira/vendor/Hyper/loader/boot_protocol/ultra_protocol

$(HYPER_CMAKE_CACHE):
	@$(ECHO) "$(ACTION_PREFIX)"
	$(CMAKE) -G "Ninja" -DHYPER_TOOLCHAIN=clang -DCMAKE_C_COMPILER=clang -B$@ $(dir $@)
	@$(ECHO) "$(ACTION_SUFFIX)"

$(HYPER_BUILD_OUT) $(HYPER_INSTALL): $(HYPER_CMAKE_CACHE)
	@$(ECHO) "$(ACTION_PREFIX)"
	$(CMAKE) --build $<
	@$(ECHO) "$(ACTION_SUFFIX)"

$(HYPER_OUT): $(HYPER_BUILD_OUT)
	@$(ECHO) "$(ACTION_PREFIX)$(CP) $< $@$(ACTION_SUFFIX)"
	@$(CP) $< $@

.PHONY: hyper
hyper: $(HYPER_INSTALL) $(HYPER_OUT)

.PHONY: test_hyper
test_hyper:

.PHONY: clean_hyper
clean_hyper:
	@$(ECHO) "$(ACTION_PREFIX)"
	-$(CMAKE) --build $(HYPER_CMAKE_CACHE) -- clean
	-$(RM) $(HYPER_CMAKE_CACHE)
	-$(RM) $(HYPER_INSTALL)
	-$(RM) $(HYPER_OUT)
	@$(ECHO) "$(ACTION_SUFFIX)"

