#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "../include/conv.h"
#include "../include/bparse.h"
#include "../include/hparse.h"
#include "../include/dparse.h"
#include "../include/parser.h"
struct parse_res parse_args(char **msg,const int a_count)
{
    struct parse_res result;
    result.state = SUCCESS;
    int i;
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
                case VAL:
                    if(!u_conv)
                    {
                        result.file= false;
                        u_conv = true;
                    }
                    else 
                    {
                        result.state = FAILURE;
                        result.msg = "Multiple conversion types. Aborting!";
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
                        result.msg = "Multiple conversion types. Aborting!";
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
                        result.val_conv.conv = CONV_DTOB;
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
                    result.msg = "Unknown input.";
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
                    size_t len; 
                    case CONV_HTOB:
                        ;
                        len;
                        if((len = strlen(msg[i]))>0)
                        {
                            result.state = hinput(&msg[i][0],len);
                        }
                        hret(&result,&msg[i][0]);
                        return result;
                        break;
                    case CONV_HTOD:
                        ;
                        len;
                        if((len = strlen(msg[i]))>0)
                        {
                            result.state = hinput(&msg[i][0],len);
                        }
                        hret(&result,&msg[i][0]);
                        return result;
                        break;
                    case CONV_DTOH:
                        result.state = dlen(&msg[i][0]);
                        if(result.state == FAILURE)
                        {
                            result.msg = "Too long input, input limited to 19 chars";
                            return result;
                        }
                        result.val_conv.d_val = dval(&msg[i][0]);
                        return result;
                    case CONV_DTOB:
                        result.state = dlen(&msg[i][0]);
                        if(result.state == FAILURE)
                        {
                            result.msg = "Too long input, input limited to 19 chars";
                            return result;
                        }
                        result.val_conv.d_val = dval(&msg[i][0]);
                        return result;
                    case CONV_DTOA:
                        break;
                    case CONV_BTOD:
                        ;
                        size_t l = strlen(&msg[i][0]);
                        if(l<1)
                        {
                            result.state == FAILURE;
                            result.msg = "No input";
                            return result;
                        }
                        else if(l > (sizeof(unsigned long) * 8))
                        {
                            printf("Too long");
                            result.state == FAILURE;
                            result.msg = "Too long input";
                            return result;
                        }
                        else
                        {
                            if((result.state = bparse(&msg[i][0],strlen(&msg[i][0]))) == FAILURE)
                            {
                                result.msg = "Invalid input.";
                                return result;
                            }
                            else if(result.state == SUCCESS)
                            {
                                hret(&result,&msg[i][0]);
                                return result;
                            }
                        }
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
