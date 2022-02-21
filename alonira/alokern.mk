ALOKERN_SOURCES = $(wildcard alonira/alokern/*.c)
ALOKERN_OBJECTS = $(ALOKERN_SOURCES:.c=.o)

ALOKERN_OUT = boot/alonira-kernel.elf

ALOKERN_C_FLAGS = $(ALOCOM_C_FLAGS)
ifeq ($(BOOT_PROTOCOL),STIVALE)
ALOKERN_C_FLAGS += $(STIVALE_C_FLAGS)
else
ALOKERN_C_FLAGS += $(ULTRA_C_FLAGS)
endif

build_message_alokern:
	@$(ECHO) "$(SECTION_PREFIX) Alokern"
	@$(ECHO) "$(INFO_PREFIX) Build the Alonira kernel"

alokern: $(ALOKERN_OUT)

$(ALOKERN_OUT): CFLAGS = $(ALOKERN_C_FLAGS)
$(ALOKERN_OUT): LFLAGS = $(ALOCOM_L_FLAGS) -static -Talonira/alokern/kernel.ld
$(ALOKERN_OUT): $(ALOKERN_OBJECTS) $(ALOCOM_OUT)

clean_alokern:
	@$(ECHO) "$(ACTION_PREFIX)"
	-rm $(ALOKERN_OBJECTS)
	-rm $(ALOKERN_OUT)
	@$(ECHO) "$(ACTION_SUFFIX)"
