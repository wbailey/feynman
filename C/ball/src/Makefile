CC = gcc
CFLAGS = -Wall
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
INCLUDE = ../include

.PHONY: clean
.SILENT: clean

all: $(OBJS)
	@echo Source objects have been compiled

debug: CFLAGS += -DDEBUG -g
debug: all

.c.o:
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

clean:
	rm *.o
