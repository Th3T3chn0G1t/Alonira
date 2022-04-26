ALOKERN_SOURCES = $(wildcard alonira/alokern/*.c)
ALOKERN_OBJECTS = $(ALOKERN_SOURCES:.c=$(OBJECT_SUFFIX))

ALOKERN_OUT = boot/alonira-kernel.elf

ALOKERN_C_FLAGS = $(FREESTANDING_C_FLAGS)
ALOKERN_C_FLAGS += -DALO_BOOT_PROTOCOL_ULTRA=2 -DALO_BOOT_PROTOCOL=ALO_BOOT_PROTOCOL_$(BOOT_PROTOCOL)
ALOKERN_C_FLAGS += -Werror -Weverything -Wthread-safety
ALOKERN_C_FLAGS += -Wno-gnu-statement-expression -Wno-c++98-compat -Wno-redundant-parens -Wno-atomic-implicit-seq-cst -Wno-padded -Wno-poison-system-directories -Wno-unknown-warning-option -Wno-c++98-compat-pedantic -Wno-old-style-cast -Wno-register -Wno-overlength-strings -Wno-cast-qual  -Wno-gnu-zero-variadic-macro-arguments -Wno-language-extension-token -Wno-gnu-conditional-omitted-operand -Wno-gnu-case-range -Wno-gnu-binary-literal
# https://stackoverflow.com/questions/28516413/c11-alignas-vs-clang-wcast-align
# Clang fails to check alignment properly when delivering -Wcast-align
ALOKERN_C_FLAGS += -Wno-cast-align
ALOKERN_C_FLAGS += $(ALOCOM_C_FLAGS)
ALOKERN_C_FLAGS += -fsanitize=undefined,cfi

ifeq ($(BOOT_PROTOCOL),ULTRA)
ALOKERN_C_FLAGS += $(ULTRA_C_FLAGS)
endif

ALOKERN_L_FLAGS = -nostdlib -static
ALOKERN_L_FLAGS += $(ALOCOM_L_FLAGS)
ALOKERN_L_FLAGS += -Talonira/alokern/kernel-generic.ld
ALOKERN_L_FLAGS += -fsanitize=undefined,cfi

build_message_alokern:
	@$(ECHO) "$(SECTION_PREFIX) Alokern"
	@$(ECHO) "$(INFO_PREFIX) Build the Alonira kernel"

alokern: $(ALOKERN_OUT)

$(ALOKERN_OUT): CFLAGS = $(ALOKERN_C_FLAGS)
$(ALOKERN_OUT): LFLAGS = $(ALOKERN_L_FLAGS)
$(ALOKERN_OUT): $(ALOKERN_OBJECTS) $(ALOCOM_OUT)

clean_alokern:
	@$(ECHO) "$(ACTION_PREFIX)"
	-rm $(ALOKERN_OBJECTS)
	-rm $(ALOKERN_OUT)
	@$(ECHO) "$(ACTION_SUFFIX)"
