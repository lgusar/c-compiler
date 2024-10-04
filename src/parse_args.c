#include <stdio.h>
#include <getopt.h>

#include "parse_args.h"

void usage() {
    fprintf(stderr, "./lgcc file [ --lex | --parse | --codegen ]\n");
}

int parse_args(int argc, char **argv, char **filename, int **flags) {
    int opt;
    while (1) {
        const struct option long_options[] = {
            {"lex", no_argument, flags[0], 1},
            {"parse", no_argument, flags[1], 1},
            {"codegen", no_argument, flags[2], 1},
        };
        int option_index = 0;

        opt = getopt_long(argc, argv, "", long_options, &option_index);
        if (opt == -1) {
            break;
        }

        if (long_options[option_index].flag != 0) {
            for (int i = 0; i < 3; i++) {
                if (i == option_index) {
                    continue;
                }

                if (*long_options[i].flag != 0) {
                    fprintf(stderr, "error: multiple options selected\n");
                    usage();
                    return 1;
                }
            }
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "error: missing file\n");
        usage();
        return 1;
    }

    *filename = argv[optind++];
    if (optind < argc) {
        fprintf(stderr, "error: too many arguments\n");
        usage();
        return 1;
    }

    return 0;
}
