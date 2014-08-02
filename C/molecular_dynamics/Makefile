CC = gcc
CFLAGS = -Wall
TARGET = md
INCLUDE = -I "include" -I "src" -I "."
SRC = src
TEST = test

.PHONY: clean $(SRC) $(TEST)
.SILENT: clean

all: clean build run

build: $(TARGET)
	@echo Simulation runner has been generated

run:
	$(PWD)/$(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(TARGET) $(wildcard $(SRC)/*.o) $(TARGET).c

$(SRC):
	$(MAKE) -C $@ all

$(TEST):
	$(MAKE) -C $@ clean all run

clean:
	$(MAKE) -is -C $(SRC) clean
	$(MAKE) -is -C $(TEST) clean
	- rm $(TARGET)
	@echo All temporary files have been removed
