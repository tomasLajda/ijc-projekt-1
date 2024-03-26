#  Řešení IJC-DU1, příklad b), 22.3.2024
#  Autor: Tomáš Lajda, FIT
#  Přeloženo: 11.4.0

CC = gcc

CFLAGS = -Wall -Wextra -Werror -std=c11 -pedantic

SRCS = no-comment.c error.c

OBJS = $(SRCS:.c=.o)

TARGET = no-comment

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)
