CC = g++
CFLAGS = -g
TARGET = CmpFuncs
TXTS = Sum.txt Polynom.txt Strlen.txt Crc32.txt

SRCS = funcs.c main.c

OBJECTS = obj/funcs.o obj/main.o

all: build
	./$(TARGET)

build: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

obj/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(TARGET) $(OBJECTS) $(TXTS)

.PHONY: all clean build run