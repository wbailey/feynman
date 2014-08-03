CC = gcc
CFLAGS = -Wall
TARGET=test_runner
PATH = ..
INCLUDE = -I $(PATH)/include -I $(PATH)/src
SRC = $(PATH)/src
OBJECTS = $(wildcard $(SRC)/*.o)

.PHONY: clean run
.SILENT: clean

all: $(TARGET)
	@echo Test runner has been generated

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(TARGET) $(OBJECTS) $(TARGET).c

$(SRC):
	$(MAKE) -C $@ all

run:
	- ./$(TARGET)

clean:
	- rm $(TARGET)
	@echo All test temporary files have been removed
