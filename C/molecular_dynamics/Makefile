CC = gcc
CFLAGS = -Wall
TARGET = md
INCLUDE = -I "include" -I "src"
SRC = src
TEST = test

.PHONY: clean $(SRC) $(TEST)
.SILENT: clean

build: $(TARGET)
	@echo Simulation runner has been generated

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
