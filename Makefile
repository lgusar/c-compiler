CFLAGS = -Wall -Wextra -pedantic -ggdb

UNITY_SRC = ./unity/src

all:
	gcc $(CFLAGS) -o main src/main.c src/parse_args.c

test-build:
	gcc $(CFLAGS) -o test tests/parse_args_test.c src/parse_args.c $(UNITY_SRC)/unity.c -I./src -I$(UNITY_SRC)

test-run: 
	./test

test-clean:
	rm test

test: test-clean test-build test-run

clean:
	rm -rf main
