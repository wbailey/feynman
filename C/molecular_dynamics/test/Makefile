CC = gcc
CFLAGS = -Wall
TARGET=runner
INCLUDE = ../include

.PHONY: clean run
.SILENT: clean

all: $(TARGET)
	@echo Test runner has been generated

$(TARGET):
	$(CC) $(CFLAGS) -I $(INCLUDE) -o $(TARGET) $(TARGET).c

run:
	./$(TARGET)

clean:
	rm $(TARGET)
