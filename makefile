CC = gcc
CFLAGS = -ansi -Wall -pedantic

# Source files
SRCS = tests.c

# Object files
OBJS = $(SRCS:.c=.o)

# Header files
HEADERS =

# Executable
TARGET = run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

