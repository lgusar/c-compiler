all:
	gcc -Wall -Wextra -pedantic -ggdb -o main src/main.c

clean:
	rm -rf main
