include build/config.mk
include build/common.mk

MODULES = $(wildcard alonira/vendor/*.mk) $(wildcard alonira/*.mk) $(ADDITIONAL_MODULES)

include $(MODULES)
BUILD_TARGETS += $(notdir $(subst .mk,,$(MODULES)))
CLEAN_TARGETS += $(addprefix clean_,$(notdir $(subst .mk,,$(MODULES))))

.DEFAULT_GOAL := all

build_message_pre_build:
	@$(ECHO) "$(SECTION_PREFIX) Pre-Build"
ifneq ($(ERROR),)
	@$(ECHO) $(ERROR)
	@exit 1
else
	@$(ECHO) "$(INFO_PREFIX) Nothing to do!"
endif

all: $(BUILD_TARGETS) ### @Default Builds default project
	@$(ECHO) "$(INFO_PREFIX) All built!"

list: ### @Default Lists targets to be built for `all`
	@$(ECHO) "$(INFO_PREFIX) Targets to be built for \`all\`: $(addprefix \n - $(TARGET_PREFIX),$(addsuffix $(TARGET_SUFFIX),$(BUILD_TARGETS)))"
	@$(ECHO) "$(NOTE_PREFIX) For a list of available targets and their descriptions, see \`make help\`"

help: ### @Default Generates this message
	@$(ECHO) "$(INFO_PREFIX) Makefile help\n$(NOTE_PREFIX) This list only includes descriptions for user-desireable targets$(patsubst @%,$(NOTABLE_PREFIX)%$(NOTABLE_SUFFIX),$(patsubst %:,\n - $(TARGET_PREFIX)%$(TARGET_SUFFIX):,$(subst `,\`,$(shell grep -Eh '^\w+:.*\#\#\#.*' $(MAKEFILE_LIST) | sed 's|:.*\#\#\#|:|g'))))"

build_message_clean:
	@$(ECHO) "$(SECTION_PREFIX) Clean"
	@$(ECHO) "$(INFO_PREFIX) Cleaning up build artifacts from all modules"
	@$(ECHO) "$(NOTE_PREFIX) To clean an individual module, use \`make clean_{MODULE_NAME}\`$(ACTION_PREFIX)"

clean: build_message_clean $(CLEAN_TARGETS) ### @Default Cleans the repository of most build artifacts
	@$(ECHO) "$(ACTION_SUFFIX)$(INFO_PREFIX) All clean!"

bin:
	@$(ECHO) "$(ACTION_PREFIX)mkdir $@$(ACTION_SUFFIX)"
	-@mkdir $@
