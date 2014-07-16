CC = gcc
CFLAGS = -Wall
TARGET = runner
INCLUDE = include
SRC = src

.PHONY: clean $(SRC)
.SILENT: clean

build: $(TARGET)
	@echo Simulation runner has been generated

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -I $(INCLUDE) -o $(TARGET) $(wildcard $(SRC)/*.o) runner.c

$(SRC):
	$(MAKE) -C $@ all

clean:
	$(MAKE) -is -C $(SRC) clean
	- rm $(TARGET)
	@echo All temporary files have been removed
