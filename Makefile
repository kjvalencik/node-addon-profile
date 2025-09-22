CC = gcc
CFLAGS = -Wall -Werror -shared -Wl,-U,_napi_create_function,-U,_napi_set_named_property
SOURCES = addon.c
TARGET = index.node

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $@

clean:
	rm -f $(TARGET)

.PHONY: all clean
