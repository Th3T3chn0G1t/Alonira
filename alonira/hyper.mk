HYPER_CMAKE_CACHE = $(ALONIRA_DIR)/alonira/vendor/Hyper/build
HYPER_BUILD_OUT = $(ALONIRA_DIR)/alonira/vendor/Hyper/build/loader/hyper_iso_boot
HYPER_OUT = $(ALONIRA_DIR)/boot/boot/hyper/hyper_iso_boot

ULTRA_CFLAGS = -I$(ALONIRA_DIR)/alonira/vendor/Hyper/loader/boot_protocol/ultra_protocol

$(HYPER_CMAKE_CACHE):
	@$(ECHO) "$(ACTION_PREFIX)"
	-$(MKDIR) $@
	$(CMAKE) -G "Unix Makefiles" -DHYPER_TOOLCHAIN=clang -DHYPER_E9_LOG=ON -DCMAKE_C_COMPILER=$(CLANG) -DCMAKE_ASM_NASM_COMPILER=$(NASM) -B$@ $(dir $@)
	@$(ECHO) "$(ACTION_SUFFIX)"

$(HYPER_BUILD_OUT): $(HYPER_CMAKE_CACHE)
	@$(ECHO) "$(ACTION_PREFIX)"
	$(MAKE) -C $<
	@$(ECHO) "$(ACTION_SUFFIX)"

$(HYPER_OUT): $(HYPER_BUILD_OUT)
	@$(ECHO) "$(ACTION_PREFIX)$(CP) $< $@$(ACTION_SUFFIX)"
	@$(CP) $< $@

.PHONY: hyper
hyper: $(HYPER_OUT)

.PHONY: test_hyper
test_hyper:

.PHONY: clean_hyper
clean_hyper:
	@$(ECHO) "$(ACTION_PREFIX)"
	-$(CMAKE) --build $(HYPER_CMAKE_CACHE) -- clean
	-$(RMDIR) $(HYPER_CMAKE_CACHE)
	-$(RM) $(HYPER_OUT)
	@$(ECHO) "$(ACTION_SUFFIX)"

