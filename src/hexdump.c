#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/conv.h"
#include "../include/parser.h"
int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("No command line arguments.");
        exit(EXIT_FAILURE);
    }
    struct parse_res result = parse_args(++argv,argc-1);
    
    printf("%s",result.msg);

    return 0;
}
