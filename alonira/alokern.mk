ALOKERN_SOURCES = $(wildcard alonira/alokern/*.c)
ALOKERN_OBJECTS = $(ALOKERN_SOURCES:.c=$(OBJECT_SUFFIX))

ALOKERN_OUT = boot/alonira-kernel.elf

ALOKERN_C_FLAGS = $(ALOCOM_C_FLAGS)
ALOKERN_C_FLAGS += $(ULTRA_C_FLAGS)

ALOKERN_L_FLAGS = $(ALOCOM_L_FLAGS)
ALOKERN_L_FLAGS += -Talonira/alokern/kernel-generic.ld

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
