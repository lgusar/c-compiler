#include <stdio.h>
#include <stdlib.h>

#include "file_io.h"

int read_from_file(const char *filename, char **output) {
    FILE *fp = fopen(filename, "rb");
    if (fp) {
        fseek(fp, 0, SEEK_END);
        int length = ftell(fp) + 1;
        fseek(fp, 0, SEEK_SET);
        *output = malloc(length);
        if (*output) {
            fread(*output, 1, length - 1, fp);
        }
        fclose(fp);
        return 0;
    }
    return 1;
}
