CC = gcc
CFLAGS = -Wall
TARGET=runner
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
INCLUDE = ../include

.PHONY: clean
.SILENT: clean

build: $(TARGET)
	@echo Simulation runner has been generated

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -I $(INCLUDE) -o $(TARGET) $(TARGET).c

all: $(OBJS)
	@echo Source objects have been compiled

debug: CFLAGS += -DDEBUG -g
debug: all

.c.o:
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

clean:
	rm *.o
