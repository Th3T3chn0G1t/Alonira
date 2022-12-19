HYPER_CMAKE_CACHE = $(ALONIRA_DIR)/alonira/vendor/Hyper/build
HYPER_INSTALL = $(ALONIRA_DIR)/alonira/vendor/Hyper/installer/hyper_install

ULTRA_CFLAGS = -I$(ALONIRA_DIR)/alonira/vendor/Hyper/loader/boot_protocol/ultra_protocol

$(HYPER_CMAKE_CACHE): $(ALONIRA_DIR)/alonira/vendor/Hyper
	@$(ECHO) "$(ACTION_PREFIX)"
	$(CMAKE) -G "Ninja" -DHYPER_TOOLCHAIN=clang -DCMAKE_C_COMPILER=clang -B$@
	@$(ECHO) "$(ACTION_SUFFIX)"

$(HYPER_INSTALL): $(HYPER_CMAKE_CACHE)
	@$(ECHO) "$(ACTION_PREFIX)"
	$(CMAKE) --build $<
	@$(ECHO) "$(ACTION_SUFFIX)"

.PHONY: hyper
hyper: $(HYPER_INSTALL)

.PHONY: test_hyper
test_hyper:

.PHONY: clean_hyper
clean_hyper:
	@$(ECHO) "$(ACTION_PREFIX)"
	-$(CMAKE) --build $(HYPER_CMAKE_CACHE) -- clean
	-$(RM) $(HYPER_CMAKE_CACHE)
	@$(ECHO) "$(ACTION_SUFFIX)"

