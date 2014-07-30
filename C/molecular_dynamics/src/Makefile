CC = gcc
CFLAGS = -Wall
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
INCLUDE = -I "../include" -I "."

.PHONY: clean
.SILENT: clean

all: $(OBJS)
	@echo Source objects have been compiled

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	- rm *.o
	@echo All source temporary files have been cleaned
