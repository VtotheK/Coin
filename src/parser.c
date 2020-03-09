#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../include/parser.h"
#include "../include/conv.h"

unsigned long hash_comp(unsigned char *str);

struct parse_res parse_args(char **msg,int a_count)
{
    struct parse_res result;
    char **arg = msg;
    int i;
    bool u_conv = false;
    bool v_conv = false;
    char str[64];
    for(i=0; i<a_count;i++)
    {
        switch(hash_comp(arg[i]))
        {
            case VAL:
                if(!u_conv)
                {
                    result.file= false;
                    u_conv = true;
                }
                else
                {
                    memset(str,'\0',sizeof(str));
                    str = "Multiple conversion types. Aborting.";
                    result.state = FAILURE;
                    result.msg = &str[0];
                    return result;
                }
                break;
            case FIL:
                if(!u_conv)
                {
                    parse_res.file = true;
                    u_conv = true;
                }
                else
                {
                    memset(str,'\0',sizeof(str));
                    str = "Multiple conversion types. Aborting."
                    result.state = FAILURE;
                    result.msg = &str[0];
                    return result;
                }
                break;
            case HTOD:
                if(u_conv)
                {
                    result.val_conv.conv = CONV_HTOD;
                    v_conv = true;
                }
                break;
            case HTOB:
                if(u_conv)
                {
                    result.val_conv.conv = CONV_HTOB;
                    v_conv = true;
                }
                break;
            case HTOA:
                if(u_conv)
                {
                    result.val_conv.conv = CONV_HTOA;
                    v_conv = true;
                }
                break;
            case BTOH:
                if(u_conv)
                {
                    result.val_conv.conv = CONV_BTOH;
                    v_conv = true;
                }
                break;
            case BTOD:
                if(u_conv)
                {
                    result.val_conv.conv = CONV_BTOD;
                    v_conv = true;
                }
                break;
            case BTOA:
                if(u_conv)
                {
                    result.val_conv.conv = CONV_BTOA;
                    v_conv = true;
                }
                break;
            case DTOH:
                if(u_conv)
                {
                    result.val_conv.conv = CONV_DTOH;
                    v_conv = true;
                }
                break;
            case DTOB:
                if(u_conv)
                {
                    result.val_conv.conv = CONV_BTOD;
                    v_conv = true;
                }
                break;
            case DTOA:
                if(u_conv)
                {
                    result.val_conv.conv = CONV_DTOA;
                    v_conv = true;
                }
                break;
            default:
                return result;
        }
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
