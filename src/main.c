#include <getopt.h>
#include <stdio.h>

int main(int argc, char **argv) {
  /* TODO: input validation */
  if (argc != 2) {
    return 1;
  }
  const char *file = argv[1];

  FILE *fp;
  fp = fopen(file, "r");

  /* lex */

  /* parse */

  /* assemble */
  
  fclose(fp);

  return 0;
}
