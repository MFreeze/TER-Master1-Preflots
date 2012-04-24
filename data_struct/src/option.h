#ifndef OPTION_H
#define OPTION_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>

void print_help (FILE *stream);
int treatOption (int argc, char **argv, int *viz, char **graph_file, char **stream);

#endif
