# Define the compiler and flags
CC = gcc
CFLAGS = -Wall -std=c99

# Define the source file, header file, and output executable
SOURCE = main.c
HEADER = student_database.h
OUTPUT = student_database

# Build the executable
$(OUTPUT): $(SOURCE) $(HEADER)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(SOURCE)

# Define the available targets
.PHONY: all clean

all: $(OUTPUT)

clean:
	rm -f $(OUTPUT)
