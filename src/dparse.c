#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/conv.h"
#include "../include/dparse.h"

enum parse_state dlen(char *msg)
{
    if(strlen(msg) > 19)
    {
        return  FAILURE;
    }
    else
    {
        return SUCCESS;
    }
}

unsigned long dval(char *msg)
{
    unsigned long lres;
    char *ptr;
    if((lres = strtoul(&msg[0],&ptr,10)) > 0)
    {
        return lres;
    }
    else
    {
        printf("Error converting the input. Aborting!\n");
        exit(EXIT_FAILURE);
    }
}
