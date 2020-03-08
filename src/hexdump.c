#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/conv.h"
int main(int argc, char *argv)
{
    if(argc < 2)
    {
        printf("No command line arguments.");
        exit(EXIT_FAILURE);
    }
    if(strcmp(&argv[1],HTOD) == 0)
    {
        printf("Halelel");
    }
    return 0;
}
