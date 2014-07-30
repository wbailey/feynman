CC = gcc
CFLAGS = -Wall
TARGET = md
INCLUDE = include
SRC = src
TEST = test

.PHONY: clean $(SRC) $(TEST)
.SILENT: clean

build: $(TARGET)
	@echo Simulation runner has been generated

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -I $(INCLUDE) -o $(TARGET) $(wildcard $(SRC)/*.o) $(TARGET).c

$(SRC):
	$(MAKE) -e "CFLAGS=$(CFLAGS)" -C $@ all

$(TEST):
	$(MAKE) -C $@ clean all run


clean:
	$(MAKE) -is -C $(SRC) clean
	- rm $(TARGET)
	@echo All temporary files have been removed
