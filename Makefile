CFLAGS = -Wall -Wextra -pedantic -ggdb

all:
	gcc $(CFLAGS) -o main src/main.c src/parse_args.c

test:
	gcc $(CFLAGS) -o test tests/parse_args_test.c src/parse_args.c -I./src 

test-run: test	
	@./test

clean-test:
	rm test

clean:
	rm -rf main
