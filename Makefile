all:
	gcc -Wall -Wextra -pedantic -ggdb -o main src/main.c src/parse_args.c

clean:
	rm -rf main
