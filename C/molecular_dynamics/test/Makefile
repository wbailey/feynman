CC = gcc
CFLAGS = -Wall
TARGET=runner
INCLUDE = -I "../include" -I "../src"
SRC = ../src

.PHONY: clean run
.SILENT: clean

all: $(TARGET)
	@echo Test runner has been generated

$(TARGET):
	$(CC) $(CFLAGS) $(INCLUDE) -o $(TARGET) $(wildcard $(SRC)/*.o) $(TARGET).c

run:
	./$(TARGET)

clean:
	- rm $(TARGET)
	@echo All test temporary files have been removed
