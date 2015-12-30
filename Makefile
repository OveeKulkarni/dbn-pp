CC=g++
CCFLAGS=-Wall -ansi -pedantic -std=c++11

OBJ=bin/variable.o bin/domain.o bin/factor.o bin/model.o bin/io.o bin/main.o

all: dbn

dbn: $(OBJ)
	$(CC) -o $@ $^

bin/%.o: src/%.cpp
	$(CC) $(CCFLAGS) -I include/ -g -c -o $@ $<

.PHONY: clean

clean:
	rm -rfv dbn bin/*.o
