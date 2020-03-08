#include <stdio.h>
#include <string.h>
#include "parser.h"

unsigned long hash_comp(unsigned char *str);


struct parse_res parse_args(char **msg,int a_count)
{
    struct parse_res result;
    char **arg = msg;
    int i;

    for(i=0; i<a_count;i++)
    {
        switch(hash_comp(arg[i]))
            case VAL:
                break;
    }
}
unsigned long hash_comp(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while(c = *str++)
    {
       hash = ((hash << 5) + hash + c);
    }
    return hash;
}
