ALOCOM_C_FLAGS = -Ialonira/alocom/include -march=x86-64 -m64 --target=x86_64-none-eabi -fstack-protector-all -fsanitize=undefined,cfi
ALOCOM_C_FLAGS += -Werror -Weverything -Wthread-safety
ALOCOM_C_FLAGS += -Wno-gnu-statement-expression -Wno-c++98-compat -Wno-redundant-parens -Wno-atomic-implicit-seq-cst -Wno-padded -Wno-poison-system-directories -Wno-unknown-warning-option -Wno-c++98-compat-pedantic -Wno-old-style-cast -Wno-register -Wno-overlength-strings -Wno-cast-qual  -Wno-gnu-zero-variadic-macro-arguments -Wno-language-extension-token -Wno-gnu-conditional-omitted-operand -Wno-gnu-case-range -Wno-gnu-binary-literal -Wno-declaration-after-statement
# https://stackoverflow.com/questions/28516413/c11-alignas-vs-clang-wcast-align
# Clang fails to check alignment properly when delivering -Wcast-align
ALOCOM_C_FLAGS += -Wno-cast-align
ALOCOM_L_FLAGS = -Llib -lalonira-common -march=x86-64 -m64 --target=x86_64-none-eabi -fstack-protector-all -fsanitize=undefined,cfi

# Freestanding vs. Non-Freestanding Alocom?
ALOCOM_C_FLAGS += $(FREESTANDING_C_FLAGS)
ALOCOM_L_FLAGS += $(FREESTANDING_L_FLAGS)

ALOCOM_SOURCES = $(wildcard alonira/alocom/*.c)
ALOCOM_OBJECTS = $(ALOCOM_SOURCES:.c=$(OBJECT_SUFFIX))

ALOCOM_OUT = lib/libalonira-common.a

build_message_alocom:
	@$(ECHO) "$(SECTION_PREFIX) Alocom"
	@$(ECHO) "$(INFO_PREFIX) Build common Alonira utilities"

alocom: build_message_alocom $(ALOCOM_OUT)

$(ALOCOM_OUT): CFLAGS =
$(ALOCOM_OUT): LFLAGS =
$(ALOCOM_OUT): $(ALOCOM_OBJECTS) | lib

clean_alocom:
	@$(ECHO) "$(ACTION_PREFIX)"
	-rm $(ALOCOM_OBJECTS)
	-rm $(ALOCOM_OUT)
	@$(ECHO) "$(ACTION_SUFFIX)"
