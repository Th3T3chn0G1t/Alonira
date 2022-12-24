$(GEN_BACKENDS_ALONIRA_LIB): CFLAGS = $(GEN_BACKENDS_ALONIRA_INTERNAL_CFLAGS) $(GEN_CORE_CFLAGS) $(ALO_KERNEL_CFLAGS) -Wno-c++-compat -Wno-gnu-empty-struct -Wno-unused-parameter
$(GEN_BACKENDS_ALONIRA_LIB): LFLAGS = $(GEN_BACKENDS_ALONIRA_INTERNAL_LFLAGS)
$(GEN_BACKENDS_ALONIRA_LIB): LIBDIRS =
$(GEN_BACKENDS_ALONIRA_LIB): SANITIZERS = $(GEN_BACKENDS_ALONIRA_SANITIZERS)
$(GEN_BACKENDS_ALONIRA_LIB): $(GEN_BACKENDS_ALONIRA_OBJECTS) | $(ALONIRA_DIR)/lib

.PHONY: genbackends_alonira
genbackends_alonira: $(GEN_BACKENDS_ALONIRA_LIB)

.PHONY: test_genbackends_alonira
test_genbackends_alonira:

.PHONY: clean_genbackends_alonira
clean_genbackends_alonira:
	@$(ECHO) "$(ACTION_PREFIX)"
	-$(RM) $(GEN_BACKENDS_ALONIRA_OBJECTS)
	-$(RM) $(GEN_BACKENDS_ALONIRA_LIB)
	@$(ECHO) "$(ACTION_SUFFIX)"
