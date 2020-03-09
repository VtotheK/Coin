#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/parser.h"
#include "../include/conv.h"

#define MSG_SIZE 64

unsigned long hash_comp(unsigned char *str);

struct parse_res parse_args(char **msg,const int a_count)
{
    struct parse_res result;
    result.state = SUCCESS;
    int i;
    char **arg;
    arg = msg;
    bool u_conv = false;
    bool v_conv = false;
    for(i=0; i<a_count;i++)
    {
        switch(hash_comp(arg[i]))
        {
            case VAL:
                if(!u_conv)
                {
                    result.file= false;
                    v_conv = true;
                    u_conv = true;
                }
                else 
                {
                    result.state = FAILURE;
                    result.msg = "Multiple conversion types. Aborting\n";
                    return result;
                }
                break;
            case FIL:
                if(!u_conv)
                {
                    result.file = true;
                    u_conv = true;
                }
                else 
                {
                    result.state = FAILURE;
                    result.msg = "Multiple conversion types. Aborting\n";
                    return result;
                }
                break;
            case HTOD:
                if(u_conv && !v_conv)
                {
                    result.val_conv.conv = CONV_HTOD;
                    v_conv = true;
                }
                break;
            case HTOB:
                if(u_conv && !v_conv)
                {
                    result.val_conv.conv = CONV_HTOB;
                    v_conv = true;
                }
                break;
            case HTOA:
                if(u_conv && !v_conv)
                {
                    result.val_conv.conv = CONV_HTOA;
                    v_conv = true;
                }
                break;
            case BTOH:
                if(u_conv && !v_conv)
                {
                    result.val_conv.conv = CONV_BTOH;
                    v_conv = true;
                }
                break;
            case BTOD:
                if(u_conv && !v_conv)
                {
                    result.val_conv.conv = CONV_BTOD;
                    v_conv = true;
                }
                break;
            case BTOA:
                if(u_conv && !v_conv)
                {
                    result.val_conv.conv = CONV_BTOA;
                    v_conv = true;
                }
                break;
            case DTOH:
                if(u_conv && !v_conv)
                {
                    result.val_conv.conv = CONV_DTOH;
                    v_conv = true;
                }
                break;
            case DTOB:
                if(u_conv && !v_conv)
                {
                    result.val_conv.conv = CONV_BTOD;
                    v_conv = true;
                }
                break;
            case DTOA:
                if(u_conv && !v_conv)
                {
                    result.val_conv.conv = CONV_DTOA;
                    v_conv = true;
                }
                break;
            case HELP:
                result.msg = "This has some helper message";
                result.state = HELPER;
                return result;
            default:
                result.msg = "Unknown input.\n";
                result.state = FAILURE;
                return result;
        }
    }
    return result;
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
