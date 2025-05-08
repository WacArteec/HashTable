CC = g++
ASM = nasm
ASMFLAGS = -f elf64
BEFOREFLAGS = -O0 -c -g
MIDFLAGS = -o
AFTERFLAGS = 

SRC = src/Reader.cpp src/HashTable.cpp src/main.cpp
ASM_SRC = src/Search.asm
OBJ = obj/Reader.o obj/HashTable.o obj/main.o obj/Search.o

TARGET = HashTable

all: build
	./$(TARGET)

build: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $^ -o $@ $(AFTERFLAGS)

obj/%.o: src/%.cpp
	$(CC) $(BEFOREFLAGS) $< $(MIDFLAGS) $@

obj/%.o: src/%.asm
	$(ASM) $(ASMFLAGS) $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(TARGET) $(OBJ) obj/

.PHONY: all clean build run