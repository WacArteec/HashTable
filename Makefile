CC = g++
ASM = nasm
ASMFLAGS = -f elf64
BEFOREFLAGS = -O0 -c -g -mavx2
MIDFLAGS = -o
AFTERFLAGS = 
LDFLAGS = -no-pie -fno-pie

SRC = src/Reader.cpp src/HashTable.cpp src/main.cpp
ASM_SRC = src/Search.asm
OBJ = obj/Reader.o obj/HashTable.o obj/main.o obj/Search.o

TARGET = HashTable

all: build
	./$(TARGET)

build: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@ $(AFTERFLAGS)

obj/%.o: src/%.asm
	$(ASM) $(ASMFLAGS) $< -o $@
	
obj/%.o: src/%.cpp
	$(CC) $(BEFOREFLAGS) $< $(MIDFLAGS) $@


run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(TARGET) $(OBJ)

.PHONY: all clean build run