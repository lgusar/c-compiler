#ifndef _FILE_IO_H
#define _FILE_IO_H

int read_from_file(const char *filename, char **output);

int write_to_file(const char *filename, const char *input);

#endif /* _FILE_IO_H */
