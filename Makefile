CC = gcc
CFLAGS = -Wall -Wextra -O2
INCLUDES = -Iinclude
SRC = src/main.c src/interpreter.c src/jump_table.c
TARGET = brainfuck

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
