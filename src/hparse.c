#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/hparse.h"
#include "../include/conv.h"
#include "../include/char_val.h"
enum parse_state hinput(char *comp, size_t clen)
{
    int i;
    char *ptr = comp;
    for(i=0; i<clen;i++,ptr++)
    {
        if((*ptr <= UC_CHAR_MAX && *ptr >= UC_CHAR_MIN) ||
           (*ptr <= LC_CHAR_MAX && *ptr >= LC_CHAR_MAX) ||
           (*ptr <= NUM_MAX     && *ptr >= NUM_MIN))
        {
        }
        else
        {
            return FAILURE;
        }
    }
    return SUCCESS;
}
