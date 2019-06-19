#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "args.h"

static struct option opts[] = {
    {"help", 0, 0, 'h'},    // Show help
    {"path", 1, 0, 'p'},   // Set device name
};

void print_usage(char *name)
{
    printf("Usage: %s [options]\n", name);
	printf("Supported options:\n");
    printf("\t-h show help\n");
    printf("\t-p filesystem path\n");
    printf("\n");
}

int parse_args(char **path, int argc, char **argv)
{
    int c;

    while ((c = getopt_long(argc, argv, "hp:", opts, NULL)) != -1) {
        switch (c) {
        case 'h':
            print_usage(argv[0]);
            return 1;
            break;
        case 'p':
            if (optarg) {
                *path = optarg;
            }
            break;
        default:
            printf("Invalid option -%c\n", c);
            printf("Run %s -h for help\n", argv[0]);
            return 1;
        }
    }

    return 0;
}
