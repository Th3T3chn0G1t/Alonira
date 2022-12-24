GIT ?= git
CMAKE ?= cmake

GENSTONE_DIR = alonira/vendor/Genstone
CIONOM_DIR = alonira/vendor/Cionom
ALONIRA_DIR = .

include $(GENSTONE_DIR)/build/common.mk
include $(ALONIRA_DIR)/build/kernel.mk

MODULES = $(GENSTONE_DIR)/genstone/gentests.mk $(GENSTONE_DIR)/genstone/gencore.mk $(GENSTONE_DIR)/genstone/genbackends.mk
MODULES += $(CIONOM_DIR)/implementation/cionom.mk
MODULES += $(ALONIRA_DIR)/alonira/kernel_gencore.mk $(ALONIRA_DIR)/alonira/hyper.mk $(ALONIRA_DIR)/alonira/alokernel.mk $(ALONIRA_DIR)/alonira/alonira.mk $(ALONIRA_DIR)/alonira/genbackends_alonira.mk

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
	@$(ECHO) "$(ACTION_PREFIX)$(MKDIR) $@$(ACTION_SUFFIX)"
	-@$(MKDIR) $@
