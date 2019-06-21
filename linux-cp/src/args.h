#ifndef ARGS_H
#define ARGS_H

#include "common.h"

void print_usage(char *name);

int parse_args(fileDev *dev, int argc, char **argv);

#endif // ARGS_H
