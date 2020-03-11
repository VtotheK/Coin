#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/parser.h"
#include "../include/conv.h"
#include <limits.h>
#define MSG_SIZE 64

unsigned long hash_comp(unsigned char *str);

struct parse_res parse_args(char **msg,const int a_count)
{
    struct parse_res result;
    result.state = SUCCESS;
    int i;
    int len;
    //char **arg;
    //arg = msg;
    bool u_conv = false;
    bool v_conv = false;
    for(i=0; i<a_count;i++)
    {
        len = strlen(&msg[i][0]);
        if(len > 1 && msg[i][0] == '-' && msg[i][1] != '-')
        {
            switch(hash_comp(msg[i]))
            {
                case VAL:
                    if(!u_conv)
                    {
                        result.file= false;
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
        else if(strlen(&msg[i][0]) > 2 && msg[i][0] == '-' && msg[i][1] ==  '-')
        {
            //TODO handle --commands
        }
        else
        {
            if(u_conv && v_conv)
            {
                switch(result.val_conv.conv) //TODO change this enum int comparison to struct ulong 
                {
                    case CONV_DTOH:
                        if(strlen(msg[i]) > 19)
                                {
                                    result.msg = "Too long conversion target. Max char length 19.";
                                    result.state = FAILURE;
                                    return result;
                                    //TODO ulong max size, how to ensure ulong max length as max input?
                                }
                         else{
                         char *ptr;
                        if((result.val_conv.d_val = strtoul(&msg[i][0],&ptr,10)) > 0)
                        {
                            result.state = SUCCESS;
                            return result;
                        }
                        }
                        break;
                    case CONV_DTOB:
                        break;
                    case CONV_DTOA:
                        break;

                }
            }
            //TODO handle value input
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
