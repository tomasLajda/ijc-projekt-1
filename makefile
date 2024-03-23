# Compiler
CC = gcc
# Compiler flags
CFLAGS = -Wall -Wextra -Werror -std=c11 -pedantic

# Source files
SRCS = no-comment.c error.c
# Object files
OBJS = $(SRCS:.c=.o)
# Executable name
TARGET = no-comment

# Default rule
all: $(TARGET)

# Rule for linking object files into the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule for compiling source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET)
