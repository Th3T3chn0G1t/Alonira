GENSTONE_DIR = alonira/vendor/Genstone
ALONIRA_DIR = .

PLATFORM_DIR = $(ALONIRA_DIR)/build
PLATFORM = alonira

include $(ALONIRA_DIR)/build/config.mk
include $(GENSTONE_DIR)/build/common.mk

GENSTONE_DIAGNOSTIC_CFLAGS += -Wno-reserved-identifier -Wno-gnu-empty-struct
GENSTONE_DIAGNOSTIC_CFLAGS += -Wno-gnu-binary-literal -Wno-c++-compat
GENSTONE_DIAGNOSTIC_CFLAGS += -Wno-gnu-pointer-arith -Wno-cast-align
# TODO: Remove once clang fixes this
GENSTONE_DIAGNOSTIC_CFLAGS += -Wno-dollar-in-identifier-extension

GLOBAL_LFLAGS := $(filter-out -flto,$(GLOBAL_LFLAGS))
GLOBAL_LFLAGS := $(filter-out -fsanitize=undefined,$(GLOBAL_LFLAGS))

MODULES = $(GENSTONE_DIR)/genstone/gencore.mk \
			$(GENSTONE_DIR)/genstone/genbackends.mk

ifeq ($(BOOT_PROTOCOL),ULTRA)
	MODULES += $(ALONIRA_DIR)/alonira/hyper.mk
endif

MODULES += $(ALONIRA_DIR)/alonira/alokernel.mk \
			$(ALONIRA_DIR)/alonira/alonira.mk \

TARGETS = $(notdir $(subst .mk,,$(MODULES)))
CLEAN_TARGETS = $(addprefix clean_,$(TARGETS)) clean_common
TEST_TARGETS = $(addprefix test_,$(TARGETS))

include $(MODULES)

.PHONY: all
.DEFAULT_GOAL := all
all: $(TARGETS)

.PHONY: clean
clean: $(CLEAN_TARGETS)

.PHONY: test
test: all $(TEST_TARGETS)

$(ALONIRA_DIR)/lib:
	-$(MKDIR) $@
