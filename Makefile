CFLAGS = -Wall -Wextra -pedantic -ggdb
TESTFLAGS = -D UNITY_OUTPUT_COLOR

UNITY_SRC = ./unity/src

all:
	gcc $(CFLAGS) -o lgcc src/main.c src/lexer.c src/token.c src/parse_args.c src/file_io.c

test-parse_args:
	gcc $(CFLAGS) $(TESTFLAGS) -o test_parse_args tests/parse_args_test.c src/parse_args.c $(UNITY_SRC)/unity.c -I./src -I$(UNITY_SRC)

test-token:
	gcc $(CFLAGS) $(TESTFLAGS) -o test_token tests/token_test.c src/token.c $(UNITY_SRC)/unity.c -I./src -I$(UNITY_SRC)

test-build: test-parse_args test-token

test-run: 
	./test_parse_args
	./test_token

test-file_io: src/file_io.c tests/integration/file_io_test.c
	gcc $(CFLAGS) $(TESTFLAGS) -o test_file_io tests/integration/file_io_test.c src/file_io.c $(UNITY_SRC)/unity.c -I./src -I$(UNITY_SRC)

test-clean:
	rm -f test_*

test-integration: test-file_io

test: test-clean test-build test-run

lgcc-clean:
	rm -f lgcc

clean: lgcc-clean test-clean
