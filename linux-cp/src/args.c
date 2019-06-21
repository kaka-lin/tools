#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "args.h"

static struct option opts[] = {
    {"help", 0, 0, 'h'},          // Show help
    {"source", 1, 0, 's'},        // SOURCE
    {"destination", 1, 0, 'd'},   // DESTINATION
};

void print_usage(char *name)
{
    printf("Usage: %s [options]\n", name);
	printf("Supported options:\n");
    printf("\t-h show help\n");
    printf("\t-s source\n");
    printf("\t-d destination\n");
    printf("\n");
}

int parse_args(fileDev *dev, int argc, char **argv)
{
    int c;

    while ((c = getopt_long(argc, argv, "hs:d:", opts, NULL)) != -1) {
        switch (c) {
        case 'h':
            print_usage(argv[0]);
            return 1;
            break;
        case 's':
            if (optarg)
                dev->src = optarg;
            break;
        case 'd':
            if (optarg)
                dev->dst = optarg;
            break;
        default:
            printf("Invalid option -%c\n", c);
            printf("Run %s -h for help\n", argv[0]);
            return 1;
        }
    }

    return 0;
}
