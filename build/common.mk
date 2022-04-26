ifeq ($(shell uname -s),Darwin)
ECHO = echo
else
ECHO = echo -e
endif

ERROR_PREFIX = \\033[0;31m\\033[1mError:\\033[0m
INFO_PREFIX = \\033[0;34m\\033[1mInfo:\\033[0m
NOTE_PREFIX = \\033[0;36m\\033[1mNote:\\033[0m
SECTION_PREFIX = \\033[1;32m\\033[1mSection:\\033[0m
ACTION_PREFIX = \\033[1;30m
ACTION_SUFFIX = \\033[0m
TARGET_PREFIX = \\033[1;32m\\033[1m
TARGET_SUFFIX = \\033[0m
NOTABLE_PREFIX = \\033[0;33m\\033[1m
NOTABLE_SUFFIX = \\033[0m

ifneq ($(OVERRIDE_CLANG),)
CLANG = $(OVERRIDE_CLANG)
endif
ifneq ($(OVERRIDE_BUILD_MODE),)
BUILD_MODE = $(OVERRIDE_BUILD_MODE)
endif
ifneq ($(OVERRIDE_GLOBAL_C_FLAGS),)
GLOBAL_C_FLAGS = $(OVERRIDE_GLOBAL_C_FLAGS)
endif
ifneq ($(OVERRIDE_GLOBAL_L_FLAGS),)
GLOBAL_L_FLAGS = $(OVERRIDE_GLOBAL_L_FLAGS)
endif
ifneq ($(OVERRIDE_ADDITIONAL_MODULES),)
ADDITIONAL_MODULES = $(OVERRIDE_ADDITIONAL_MODULES)
endif
ifneq ($(OVERRIDE_AR),)
AR = $(OVERRIDE_AR)
endif
ifneq ($(OVERRIDE_CLANG_FORMAT),)
CLANG_FORMAT = $(OVERRIDE_CLANG_FORMAT)
endif
ifneq ($(OVERRIDE_XORRISO),)
XORRISO = $(OVERRIDE_XORRISO)
endif
ifneq ($(OVERRIDE_BOOT_PROTOCOL),)
BOOT_PROTOCOL = $(OVERRIDE_BOOT_PROTOCOL)
endif
ifneq ($(OVERRIDE_ADDITIONAL_QEMU_FLAGS),)
ADDITIONAL_QEMU_FLAGS = $(OVERRIDE_ADDITIONAL_QEMU_FLAGS)
endif

ifneq ($(BUILD_MODE),RELEASE)
ifneq ($(BUILD_MODE),DEBUG)
ERROR = "Invalid value $(BUILD_MODE) for BUILD_MODE"
endif
endif

ifneq ($(BOOT_PROTOCOL),ULTRA)
ERROR = "Invalid value $(BOOT_PROTOCOL) for BOOT_PROTOCOL"
endif

CLINKER := $(CLANG) -fuse-ld=lld

GLOBAL_C_FLAGS += -std=gnu2x -fcomment-block-commands=example -fmacro-backtrace-limit=0
GLOBAL_C_FLAGS += -mcmodel=kernel -ffreestanding -fno-builtin -fno-pic -fstack-protector-all -mno-red-zone -mno-stack-arg-probe -fno-threadsafe-statics -mno-80387 -mno-mmx -mno-3dnow -mno-sse -mno-sse2
GLOBAL_C_FLAGS += -DENABLED=1 -DDISABLED=0 -DALO_BOOT_PROTOCOL_ULTRA=2 -DALO_BOOT_PROTOCOL=ALO_BOOT_PROTOCOL_$(BOOT_PROTOCOL)
GLOBAL_C_FLAGS += -Werror -Weverything -Wthread-safety
GLOBAL_C_FLAGS += -Wno-gnu-statement-expression -Wno-c++98-compat -Wno-redundant-parens -Wno-atomic-implicit-seq-cst -Wno-padded -Wno-poison-system-directories -Wno-unknown-warning-option -Wno-c++98-compat-pedantic -Wno-old-style-cast -Wno-register -Wno-overlength-strings -Wno-cast-qual  -Wno-gnu-zero-variadic-macro-arguments -Wno-language-extension-token -Wno-gnu-conditional-omitted-operand -Wno-gnu-case-range -Wno-gnu-binary-literal
# https://stackoverflow.com/questions/28516413/c11-alignas-vs-clang-wcast-align
# Clang fails to check alignment properly when delivering -Wcast-align
GLOBAL_C_FLAGS += -Wno-cast-align

GLOBAL_L_FLAGS += -nostdlib -static

CLANG_STATIC_ANALYZER_FLAGS = -Xanalyzer -analyzer-output=text
CLANG_STATIC_ANALYZER_FLAGS += -Xanalyzer -analyzer-checker=core -Xanalyzer -analyzer-checker=deadcode
CLANG_STATIC_ANALYZER_FLAGS += -Xanalyzer -analyzer-checker=optin -Xanalyzer -analyzer-checker=security
CLANG_STATIC_ANALYZER_FLAGS += -Xanalyzer -analyzer-checker=alpha.core # This one kinda sucks -Xanalyzer -analyzer-checker=alpha.clone
CLANG_STATIC_ANALYZER_FLAGS += -Xanalyzer -analyzer-checker=alpha.deadcode -Xanalyzer -analyzer-checker=alpha.security

ifeq ($(BUILD_MODE),RELEASE)
	GLOBAL_C_FLAGS += -Ofast -ffast-math -DNDEBUG -flto -mllvm -polly
	GLOBAL_L_FLAGS += -flto -Wl,-s
else
	GLOBAL_C_FLAGS += -O0 -glldb -fstandalone-debug -fno-eliminate-unused-debug-types -fdebug-macro -fno-lto -fsanitize=undefined -fno-omit-frame-pointer
	GLOBAL_L_FLAGS += -fno-lto -fsanitize=undefined
endif

LIB_PREFIX = lib
DYNAMIC_LIB_SUFFIX = .so
STATIC_LIB_SUFFIX = .a
ELF_SUFFIX = .elf
OBJECT_SUFFIX = .o
BIN_SUFFIX = .bin

ELF_TOOL = $(CLINKER) -o $@ $(filter %$(OBJECT_SUFFIX),$^) $(GLOBAL_L_FLAGS) $(LFLAGS)
STATIC_LIB_TOOL = $(AR) -r -c $@ $(filter %$(OBJECT_SUFFIX),$^)

%$(ELF_SUFFIX):
	@$(ECHO) "$(ACTION_PREFIX)$(ELF_TOOL)$(ACTION_SUFFIX)"
	@$(ELF_TOOL)

%$(BIN_SUFFIX): %$(ELF_SUFFIX)
	@$(ECHO) "$(ACTION_PREFIX)$(ELF_TOOL) -Wl,--oformat,binary$(ACTION_SUFFIX)"
	@$(ELF_TOOL) -Wl,--oformat,binary

%$(STATIC_LIB_SUFFIX):
	@$(ECHO) "$(ACTION_PREFIX)$(STATIC_LIB_TOOL)$(ACTION_SUFFIX)"
	@$(STATIC_LIB_TOOL)

%$(OBJECT_SUFFIX): %.c build/config.mk | tmp
	@$(ECHO) "$(ACTION_PREFIX)$(CLANG) -c $(GLOBAL_C_FLAGS) $(CFLAGS) -o $@ $<$(ACTION_SUFFIX)"
	@$(CLANG) -c $(GLOBAL_C_FLAGS) $(CFLAGS) -o $@ $<

	@$(ECHO) "$(ACTION_PREFIX)$(CLANG) $(GLOBAL_C_FLAGS) $(CFLAGS) --analyze $(CLANG_STATIC_ANALYZER_FLAGS) $<$(ACTION_SUFFIX)"
	@$(CLANG) $(GLOBAL_C_FLAGS) $(CFLAGS) --analyze $(CLANG_STATIC_ANALYZER_FLAGS) $<

	@$(ECHO) "$(ACTION_PREFIX)($(CLANG_FORMAT) --style=file $< > tmp/$(notdir $<)-format.tmp) && (diff $< tmp/$(notdir $<)-format.tmp)$(ACTION_SUFFIX)"
	-@($(CLANG_FORMAT) --style=file $< > tmp/$(notdir $<)-format.tmp) && (diff $< tmp/$(notdir $<)-format.tmp)

	@$(ECHO) "$(ACTION_PREFIX)$(CLANG_FORMAT) -i $<$(ACTION_SUFFIX)"
	-@$(CLANG_FORMAT) -i $<

%$(OBJECT_SUFFIX): %.asm build/config.mk | tmp
	@$(ECHO) "$(ACTION_PREFIX)$(NASM) $(GLOBAL_ASM_FLAGS) $(ASMFLAGS) -o $@ $<$(ACTION_SUFFIX)"
	@$(NASM) $(GLOBAL_ASM_FLAGS) $(ASMFLAGS) -o $@ $<

%$(BIN_SUFFIX): %.asm build/config.mk | tmp
	@$(ECHO) "$(ACTION_PREFIX)$(NASM) -fbin $(GLOBAL_ASM_FLAGS) $(ASMFLAGS) -o $@ $<$(ACTION_SUFFIX)"
	@$(NASM) -fbin $(GLOBAL_ASM_FLAGS) $(ASMFLAGS) -o $@ $<

