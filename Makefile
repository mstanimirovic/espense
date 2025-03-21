CC=clang
CFLAGS=-Wall -Werror -ggdb -Isrc
LDFLAGS=-lpthread -lsqlite3

SOURCES=$(shell find ./ -name "*.c")
HEADERS=$(shell find ./ -name "*.h")

OBJ_DIR=obj
OBJECTS=$(subst .c,.o, $(subst src,obj,$(SOURCES)))
TARGET=espense

default: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

obj/%.o: src/%.c $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR):
	@mkdir -p $@

.PHONY: clean
clean:
	@rm -rvf $(TARGET) $(OBJ_DIR)
