# Nome do executável
TARGET = main

# Diretórios
SRC_DIR = src
INC_DIR = include

# Compilador e flags
CC = gcc
CFLAGS = -Wall -I$(INC_DIR)

# Lista automática de arquivos .c
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Regra principal
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $@ -lm

clean:
	rm -f $(TARGET)

rebuild: clean all
