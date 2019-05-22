#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "args.h"

static struct option opts[] = {
    {"help", 0, 0, 'h'},    /* Show help */
    {"power", 1, 0, 'n'},   /* Set device name */ 
};

void print_usage(char *name)
{
    printf("Usage: %s [options]\n", name);
	printf("Supported options:\n");
    printf("\t-h show help\n");
    printf("\t-n 2 to the nth power (e.g. k = 2 -> 2^2 = 4)\n");
    printf("\n");
}

int parse_args(int *N, int argc, char **argv)
{
    int c;

    while ((c = getopt_long(argc, argv, "hn:", opts, NULL)) != -1) {
        switch (c) {
        case 'h':
            print_usage(argv[0]);
            return 1;
            break;
        case 'n':
            if (optarg)
                *N = atoi(optarg);
            printf("2 to the %dth power: \n", *N);
            break;
        default:
            printf("Invalid option -%c\n", c);
            printf("Run %s -h for help\n", argv[0]);
            return 1;
        }
    }

    return 0;
}
