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
ifneq ($(OVERRIDE_STRIP_BINARIES),)
STRIP_BINARIES = $(OVERRIDE_STRIP_BINARIES)
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

CLINKER := $(CLANG) -fuse-ld=lld

GLOBAL_C_FLAGS += -std=gnu2x -fcomment-block-commands=example -fmacro-backtrace-limit=0
GLOBAL_C_FLAGS += -mcmodel=kernel -ffreestanding -fno-stack-protector -fno-pic -mno-red-zone
GLOBAL_C_FLAGS += -march=x86-64 -m64 --target=x86_64-none-eabi
GLOBAL_C_FLAGS += -DDEBUG=1 -DRELEASE=0 -DMODE=$(BUILD_MODE) -DENABLED=1 -DDISABLED=0
GLOBAL_C_FLAGS += -Werror -Weverything -Wthread-safety
GLOBAL_C_FLAGS += -Wno-gnu-statement-expression -Wno-c++98-compat -Wno-redundant-parens -Wno-atomic-implicit-seq-cst -Wno-padded -Wno-poison-system-directories -Wno-unknown-warning-option  -Wno-c++98-compat-pedantic -Wno-old-style-cast -Wno-register -Wno-overlength-strings -Wno-cast-qual
# https://stackoverflow.com/questions/28516413/c11-alignas-vs-clang-wcast-align
# Clang fails to check alignment properly when delivering -Wcast-align
GLOBAL_C_FLAGS += -Wno-cast-align

GLOBAL_L_FLAGS += -nostdlib
GLOBAL_L_FLAGS += -march=x86-64 -m64 --target=x86_64-none-eabi

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

ELF_TOOL = $(CLINKER) -o $@ $(filter %$(OBJECT_SUFFIX),$^) $(GLOBAL_L_FLAGS) $(LFLAGS)
STATIC_LIB_TOOL = $(AR) -r -c $@ $(filter %$(OBJECT_SUFFIX),$^)

%$(ELF_SUFFIX):
	@$(ECHO) "$(ACTION_PREFIX)$(ELF_TOOL)$(ACTION_SUFFIX)"
	@$(ELF_TOOL)

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
