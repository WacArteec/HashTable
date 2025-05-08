CC = g++
BEFOREFLAGS = -O3 -c -g
MIDFLAGS = -o
AFTERFLAGS = 

SRC = src/Reader.cpp src/HashTable.cpp src/main.cpp
OBJ = obj/Reader.o obj/HashTable.o obj/main.o

TARGET = HashTable


all: build
	./$(TARGET)

build: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $^ -o $@ $(AFTERFLAGS)

obj/%.o: src/%.cpp
	$(CC) $(BEFOREFLAGS) $< $(MIDFLAGS) $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(TARGET) $(OBJ)

.PHONY: all clean build run