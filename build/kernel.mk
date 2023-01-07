include $(ALONIRA_DIR)/build/config.mk
include $(ALONIRA_DIR)/build/target.mk

ifeq ($(HOST),OSX)
	HOST_LLD = -flavor ld64
endif
ifeq ($(HOST), LINUX)
	HOST_LLD = -flavor ld
endif
ifeq ($(HOST), WINDOWS)
	HOST_LLD = -flavor link
endif

KERNEL_CFLAGS += -fno-pic -static -mcmodel=kernel -ffreestanding -fno-builtin -fno-pic -mno-red-zone -mno-stack-arg-probe -fno-strict-aliasing -fno-threadsafe-statics
ifeq ($(SANITIZE),ENABLED)
	KERNEL_CFLAGS += -fsanitize=$(SANITIZERS)
endif

# TODO: Work out $(GLOBAL_LFLAGS) - perhaps there's a way to isolate clang's tooldriver?
%$(KERNEL_ELF_SUFFIX):
	@$(ECHO) "$(ACTION_PREFIX)$(LLD) $(TARGET_LLD) $(KERNEL_LFLAGS) $(LFLAGS) $(addprefix -L,$(LIBDIRS)) -o $@ $(filter %$(KERNEL_OBJECT_SUFFIX),$^)$(ACTION_SUFFIX)"
	@$(LLD) $(TARGET_LLD) $(KERNEL_LFLAGS) $(LFLAGS) $(addprefix -L,$(LIBDIRS)) -o $@ $(filter %$(KERNEL_OBJECT_SUFFIX),$^)

%$(KERNEL_STATIC_LIB_SUFFIX):
	@$(ECHO) "$(ACTION_PREFIX)$(AR) -r -c $@ $(filter %$(KERNEL_OBJECT_SUFFIX),$^)$(ACTION_SUFFIX)"
	@$(AR) -r -c $@ $(filter %$(KERNEL_OBJECT_SUFFIX),$^)

%$(KERNEL_OBJECT_SUFFIX): %.c
	@$(ECHO) "$(ACTION_PREFIX)$(CLANG) -std=c2x $(KERNEL_CFLAGS) $(GLOBAL_CFLAGS) $(CFLAGS) -o $@ $<$(ACTION_SUFFIX)"
	@$(CLANG) -std=c2x -c $(KERNEL_CFLAGS) $(GLOBAL_CFLAGS) $(CFLAGS) -o $@ $<
