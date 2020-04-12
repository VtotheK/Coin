#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/conv.h"
#include "../include/dparse.h"
#include "../include/ansi_c.h"
enum parse_state dlen(char *msg,size_t len)
{
    if(strlen(msg) > 19)
    {
        return  FAILURE;
    }
    for(;len>0;len--,msg++)
    {
        if(*msg < 48 || *msg > 57)
        {
            return FAILURE;
        }
    }
    return SUCCESS;
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
    }
}
