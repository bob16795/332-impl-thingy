CC=gcc
CFLAGS=-Isrc -Ilib/include -g
LFLAGS=-Llib -lm -g
DEPS=src/map.h src/structure.h src/statemachine.h

WEBCC=emcc
WEBCFLAGS=-Isrc -Ilib/include

default: run

out: out/main
	cp dat out -r

run: out
	cd out; ./main

debug: out
	cd out; gdb ./main

bld/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

out/main: setup bld/main.o bld/map.o bld/structure.o bld/statemachine.o
	$(CC) -o out/main bld/*.o $(LFLAGS)

setup:
	mkdir -p out bld
