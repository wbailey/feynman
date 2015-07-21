CC = cc
CFLAGS = -Wall
TARGET = runner
INCLUDE = -I "include" -I "src"
SRC = src
TEST = test
DATA = ./data.csv
SETUP = ./setup.csv

.PHONY: clean $(SRC) $(TEST)
.SILENT: clean

all: clean build run

build: $(TARGET)
	@echo Simulation runner has been generated

run:
	$(PWD)/$(TARGET) > $(DATA) 2> $(SETUP)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(TARGET) $(wildcard $(SRC)/*.o) $(TARGET).c

$(SRC):
	$(MAKE) -C $@ all

$(TEST): clean $(SRC)
	$(MAKE) -C $@ clean all run

clean:
	$(MAKE) -is -C $(SRC) clean
	$(MAKE) -is -C $(TEST) clean
	- rm $(TARGET)
	@echo All temporary files have been removed

docs:
	doxygen
	open doc/html/index.html

tools: ck_brew ck_valgrind ck_graphviz ck_doxygen

ck_graphviz:
ifeq (, $(shell which dot))
	-brew install graphviz
else
	@echo "== Graphviz Installed =="
endif

ck_doxygen:
ifeq (, $(shell which doxygen))
	-brew install doxygen
else
	@echo "== Doxygen Installed =="
endif

ck_brew:
ifeq (, $(shell which brew))
	$(error "install homebrew")
else
	@echo "== Homebrew Installed =="
endif

ck_valgrind:
ifeq (, $(shell which valgrind))
	-brew install --HEAD valgrind
else
	@echo "== Valgrind Installed =="
endif
