#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

size_t file_size(FILE *fp);
void read_file(FILE *fp, void *buf, size_t size);
void write_file(FILE *fp, void *buf, size_t size);

int min(int a, int b) { return a < b ? a : b; }
void progress_bar(int progress);

#endif
