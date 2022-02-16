CFLAGS=-g -O2 -Wall -Wextra  -std=c2x -pedantic -lm $(OPTFLAGS)
CC=clang
MODULES_OBJECT_DIR=build/modules
MODULES_SOURCE_DIR=src/modules
MODULES_SOURCES=$(wildcard $(MODULES_SOURCE_DIR)/*.c )
MODULES_OBJECTS=$(patsubst $(MODULES_SOURCE_DIR)/%.c, $(MODULES_OBJECT_DIR)/%.o, $(MODULES_SOURCES))
SC_OBJECT=build/sc.o
SC_SOURCE=src/sc.c
SC_BIN=bin/sc

all: sc tests

sc: build $(SC_OBJECT) $(MODULES_OBJECTS) 
	$(CC) -o $(SC_BIN) $(CFLAGS) $(SC_OBJECT) $(MODULES_OBJECTS)
	@ctags -R .
$(SC_OBJECT): $(SC_SOURCE)
	$(CC) -c $(CFLAGS) $(SC_SOURCE) -o $(SC_OBJECT)
$(MODULES_OBJECTS): $(MODULES_OBJECT_DIR)/%.o: $(MODULES_SOURCE_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

build:
	@mkdir -p build/modules
	@mkdir -p bin

.PHONY: tests
tests:
	make -f MakeCppUTest.mk all

clean:
	rm -rf bin
	rm -rf build
	rm -f *~
	rm -f .*~
	rm -f *.*~
	rm -f src/*.*~
	rm -f src/modules/*.*~
	rm -rf test-obj
	rm -rf test-lib
	rm -f tests/*.*~
	rm -f sc_tests 
