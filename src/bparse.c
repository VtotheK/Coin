#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/conv.h"

enum parse_state bparse(char *msg, size_t len)
{
    for(;len>0;msg++,len--)
    {
        if(*msg != 48 && *msg != 49)
        {
            return FAILURE;
        }
    }
    return SUCCESS;
}
