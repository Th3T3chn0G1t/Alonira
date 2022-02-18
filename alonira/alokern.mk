ALOKERN_SOURCES = $(wildcard alonira/alokern/*.c)
ALOKERN_OBJECTS = $(ALOKERN_SOURCES:.c=.o)

ALOKERN_OUT = boot/alonira-kernel.elf

build_message_alokern:
	@$(ECHO) "$(SECTION_PREFIX) Alokern"
	@$(ECHO) "$(INFO_PREFIX) Build the Alonira kernel"

alokern: $(ALOKERN_OUT)

$(ALOKERN_OUT): CFLAGS = $(ALOCOM_C_FLAGS) $(STIVALE_C_FLAGS)
$(ALOKERN_OUT): LFLAGS = -static -Talonira/alokern/kernel.ld
$(ALOKERN_OUT): $(ALOKERN_OBJECTS)

clean_alokern:
	@$(ECHO) "$(ACTION_PREFIX)"
	-rm $(ALOKERN_OBJECTS)
	-rm $(ALOKERN_OUT)
	@$(ECHO) "$(ACTION_SUFFIX)"
