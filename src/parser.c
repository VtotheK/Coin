#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "../include/ansi_c.h"
#include "../include/conv.h"
#include "../include/bparse.h"
#include "../include/hparse.h"
#include "../include/dparse.h"
#include "../include/parser.h"
struct parse_res parse_args(char **msg,const int a_count)
{
    struct parse_res result;
    result.file = false;
    result.state = FAILURE;
    int i,j;
    int len;
    bool u_conv = false;
    bool v_conv = false;
    for(i=0; i<a_count;i++)
    {
        len = strlen(&msg[i][0]);
        if(len > 1 && msg[i][0] == '-' && msg[i][1] != '-')
        {
            switch(hash_comp(msg[i]))
            {
                case FIL:
                    if(!result.file)
                    {
                        result.file = true;
                        result.state == SUCCESS;
                    }
                    else 
                    {
                        result.state = FAILURE;
                        result.msg = "Multiple conversion types. Aborting!";
                        return result;
                    }
                    break;
                case HTOD:
                    if(!result.file)
                    {
                        result.val_conv.conv = CONV_HTOD;
                    }
                    break;
                case HTOB:
                    if(!result.file)
                    {
                        result.val_conv.conv = CONV_HTOB;
                    }
                    break;
                case HTOA:
                    if(!result.file)
                    {
                        result.val_conv.conv = CONV_HTOA;
                    }
                    break;
                case BTOH:
                    if(!result.file)
                    {
                        result.val_conv.conv = CONV_BTOH;
                    }
                    break;
                case BTOD:
                    if(!result.file)
                    {
                        result.val_conv.conv = CONV_BTOD;
                    }
                    break;
                case BTOA:
                    if(!result.file)
                    {
                        result.val_conv.conv = CONV_BTOA;
                    }
                    break;
                case DTOH:
                    if(!result.file)
                    {
                        result.val_conv.conv = CONV_DTOH;
                    }
                    break;
                case DTOB:
                    if(!result.file)
                    {
                        result.val_conv.conv = CONV_DTOB;
                    }
                    break;
                case DTOA:
                    if(!result.file)
                    {
                        result.val_conv.conv = CONV_DTOA;
                    }
                    break;
                case HELP:
                    if(!result.file)
                    {
                        result.msg = "This has some helper message";
                        result.state = HELPER;
                        return result;
                    }
            }
            if(result.val_conv.conv != EMP && !result.file)
            {
                result.state = SUCCESS;
            }
            if(result.state == FAILURE)
            {
                result.msg = "Unknown input";
                return result;
            }
        }
        else if(strlen(&msg[i][0]) > 2 && msg[i][0] == '-' && msg[i][1] ==  '-')
        {
            //TODO handle --commands
        }
        for(j=0; i<a_count;i++)
        {
            if(u_conv && v_conv)
            {
                switch(result.val_conv.conv) //TODO change this enum int comparison to struct ulong 
                {
                    size_t len; 
                    case CONV_HTOB:
                    ;
                    len;
                    if((len = strlen(msg[j]))>0)
                    {
                        result.state = hinput(&msg[j][0],len);
                    }
                    hret(&result,&msg[j][0]);
                    return result;
                    break;
                    case CONV_HTOD:
                    ;
                    len;
                    if((len = strlen(msg[j]))>0)
                    {
                        result.state = hinput(&msg[j][0],len);
                    }
                    hret(&result,&msg[j][0]);
                    return result;
                    break;
                    case CONV_DTOH:
                    result.state = dlen(&msg[j][0]);
                    if(result.state == FAILURE)
                    {
                        result.msg = "Too long input, input limited to 19 chars";
                        return result;
                    }
                    result.val_conv.d_val = dval(&msg[j][0]);
                    return result;
                    case CONV_DTOB:
                    result.state = dlen(&msg[j][0]);
                    if(result.state == FAILURE)
                    {
                        result.msg = "Too long input, input limited to 19 chars";
                        return result;
                    }
                    result.val_conv.d_val = dval(&msg[j][0]);
                    return result;
                    case CONV_DTOA:
                    break;
                    case CONV_BTOA:
                    case CONV_BTOH:
                    case CONV_BTOD:
                    ;
                    size_t l = strlen(&msg[j][0]);
                    if(l<1)
                    {
                        result.state == FAILURE;
                        result.msg = "No input";
                        return result;
                    }
                    else if(l > sizeof(unsigned long) * 8)
                    {
                        result.state = FAILURE;
                        result.msg = "Too long input";
                        return result;
                    }
                    else
                    {
                        if((result.state = bparse(&msg[j][0],strlen(&msg[j][0]))) == FAILURE)
                        {
                            result.msg = "Invalid input.";
                            return result;
                        }
                        else if(result.state == SUCCESS)
                        {
                            hret(&result,&msg[j][0]);
                            return result;
                        }
                    }
                    break;
                    default:
                    if(!hash_comp(&msg[j][0]) == result.val_conv.conv)
                    {
                        printf(S"Unknown conversion type!");
                        exit(EXIT_FAILURE);
                    }
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

void hret(struct parse_res *strc,char *msg)
{

    if(strc->state == FAILURE)
    {
        char *errmsg = "Invalid value. Please check the input!";
        strc->msg = errmsg; 
    }
    else if(strc->state == SUCCESS)
    {
        int len = (strlen(msg) + 1) * sizeof(char);
        strc->val_conv.val = malloc(len);
        memset(strc->val_conv.val,'\0',len);
        strcpy(strc->val_conv.val,msg);
    }
}
