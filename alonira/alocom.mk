ALOCOM_C_FLAGS = -Ialonira/alocom/include
ALOCOM_L_FLAGS = -Llib -lalonira-common

ALOCOM_SOURCES = $(wildcard alonira/alocom/*.c)
ALOCOM_OBJECTS = $(ALOCOM_SOURCES:.c=.o)

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
