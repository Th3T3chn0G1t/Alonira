HYPER_DIR = $(ALONIRA_DIR)/alonira/vendor/Hyper

HYPER_CMAKE_CACHE = $(HYPER_DIR)/build
HYPER_BUILD_OUT = $(HYPER_DIR)/build/loader/hyper_iso_boot
HYPER_OUT = $(ALONIRA_DIR)/boot/boot/hyper/hyper_iso_boot

# Needs to be relative to Hyper root
HYPER_TOOLCHAIN_FILE = ../../hyper-toolchain.cmake

# TODO: Make Hyper respect debug/release config
HYPER_CMAKEFLAGS = -G "Unix Makefiles" \
						-DHYPER_TOOLCHAIN=clang -DHYPER_E9_LOG=ON \
						-DCMAKE_C_COMPILER=$(CLANG) \
						-DCMAKE_ASM_NASM_COMPILER=$(NASM) \
						-DCMAKE_C_FLAGS=-flto=thin \
						-DHYPER_TOOLCHAIN_FILE=$(HYPER_TOOLCHAIN_FILE)

ifeq ($(MODE),DEBUG)
	HYPER_CMAKEFLAGS += -DCMAKE_BUILD_TYPE=Debug
endif

ifeq ($(MODE),RELEASE)
	HYPER_CMAKEFLAGS += -DCMAKE_BUILD_TYPE=Release
endif

ULTRA_CFLAGS = -I$(HYPER_DIR)/loader/boot_protocol/ultra_protocol

$(HYPER_CMAKE_CACHE):
	-$(MKDIR) $@
	$(CMAKE) $(HYPER_CMAKEFLAGS) -B$@ $(dir $@)

$(HYPER_BUILD_OUT): $(HYPER_CMAKE_CACHE)
	$(MAKE) -C $< VERBOSE=1

$(HYPER_OUT): $(HYPER_BUILD_OUT)
	$(CP) $< $@

.PHONY: hyper
hyper: $(HYPER_OUT)

.PHONY: test_hyper
test_hyper:

.PHONY: clean_hyper
clean_hyper:
	-$(CMAKE) --build $(HYPER_CMAKE_CACHE) -- clean
	$(RMDIR) $(HYPER_CMAKE_CACHE)
	$(RM) $(HYPER_OUT)

