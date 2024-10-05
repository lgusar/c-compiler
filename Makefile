CFLAGS = -Wall -Wextra -pedantic -ggdb
TESTFLAGS = -D UNITY_OUTPUT_COLOR

UNITY_SRC = ./unity/src

all:
	gcc $(CFLAGS) -o main src/main.c src/parse_args.c

test-parse_args:
	gcc $(CFLAGS) $(TESTFLAGS) -o test_parse_args tests/parse_args_test.c src/parse_args.c $(UNITY_SRC)/unity.c -I./src -I$(UNITY_SRC)

test-token:
	gcc $(CFLAGS) $(TESTFLAGS) -o test_token tests/token_test.c src/token.c $(UNITY_SRC)/unity.c -I./src -I$(UNITY_SRC)

test-build: test-parse_args test-token

test-run: 
	./test_parse_args
	./test_token

test-clean:
	rm -f test_*

test: test-clean test-build test-run

main-clean:
	rm -f main

clean: main-clean test-clean
