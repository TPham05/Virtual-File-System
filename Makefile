# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

# Source files
SRCS = main.c interface.c vfs.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = vfs

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile .c to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Optional: rebuild everything
rebuild: clean all
