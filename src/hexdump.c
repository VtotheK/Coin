#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/conv.h"
int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("No command line arguments.");
        exit(EXIT_FAILURE);
    }
    struct parse_res result = parseargs(++argv,argc-1);
    return 0;
}
