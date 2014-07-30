CC = gcc
CFLAGS = -Wall
TARGET=runner
INCLUDE = ../include
SRC = ../src

.PHONY: clean run
.SILENT: clean

all: $(TARGET)
	@echo Test runner has been generated

$(TARGET):
	$(CC) $(CFLAGS) -I $(INCLUDE) -o $(TARGET) $(wildcard $(SRC)/*.o) $(TARGET).c

run:
	./$(TARGET)

clean:
	rm $(TARGET)
