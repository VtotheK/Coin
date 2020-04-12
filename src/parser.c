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
    struct parse_res *n = &result;
    result.file = false;
    result.state = FAILURE;
    result.val_conv.conv = EMP;
    int i,j,index;
    unsigned long target,temptarget;
    int len;
    bool u_conv = false;
    bool v_conv = false;
    for(i=0; i<a_count;i++)
    {
        len = strlen(&msg[i][0]);
        if(len > 1 && msg[i][0] == '-' && msg[i][1] != '-')
        {
            switch(temptarget = hash_comp(msg[i]))
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
                        result.msg = "Multiple conversion types defined.";
                        return result;
                    }
                    break;
                case HTOD:
                    if(!result.file&& result.val_conv.conv == EMP)
                    {
                        result.val_conv.conv = CONV_HTOD;
                    }
                    break;
                case HTOB:
                    if(!result.file && result.val_conv.conv == EMP)
                    {
                        result.val_conv.conv = CONV_HTOB;
                    }
                    break;
                case HTOA:
                    if(!result.file && result.val_conv.conv == EMP)
                    {
                        result.val_conv.conv = CONV_HTOA;
                    }
                    break;
                case BTOH:
                    if(!result.file && result.val_conv.conv == EMP)
                    {
                        result.val_conv.conv = CONV_BTOH;
                    }
                    break;
                case BTOD:
                    if(!result.file && result.val_conv.conv == EMP)
                    {
                        result.val_conv.conv = CONV_BTOD;
                    }
                    break;
                case BTOA:
                    if(!result.file && result.val_conv.conv == EMP)
                    {
                        result.val_conv.conv = CONV_BTOA;
                    }
                    break;
                case DTOH:
                    if(!result.file && result.val_conv.conv == EMP)
                    {
                        result.val_conv.conv = CONV_DTOH;
                    }
                    break;
                case DTOB:
                    if(!result.file && result.val_conv.conv == EMP)
                    {
                        result.val_conv.conv = CONV_DTOB;
                    }
                    break;
                case DTOA:
                    if(!result.file && result.val_conv.conv == EMP)
                    {
                        result.val_conv.conv = CONV_DTOA;
                    }
                    break;
                case HELP:
                    if(!result.file && result.val_conv.conv == EMP)
                    {
                        result.msg = "This has some helper message";
                        result.state = HELPER;
                        return result;
                    }
            }
            if(result.val_conv.conv != EMP || result.file)
            {
                target = temptarget;
            }
        }
        else if(strlen(&msg[i][0]) > 2 && msg[i][0] == '-' && msg[i][1] ==  '-')
        {
            //TODO handle --commands
        }
    }

    if(result.val_conv.conv != EMP && !result.file)
    {
        result.state = SUCCESS;
    }
    else if(result.state == FAILURE)
    {
        result.msg = "Unknown input";
        return result;
    }
    else if(result.file) 
        return result;
    
    for(j=0,index=0; j<a_count;j++)
    {
        //printf("-dh HASH:%lu\n",hash_comp("-dh"));
        //printf("INPUT HASH:%lu",hash_comp(&msg[j][0]));
        if((hash_comp(&msg[j][0])) == target)
        continue;
        switch(n->val_conv.conv) //TODO change this enum int comparison to struct ulong 
        {
            size_t len; 
            case CONV_HTOB:
            ;
            len;

            if((len = strlen(msg[j]))>0)
                n->state = hinput(&msg[j][0],len);
            if(n->state == SUCCESS)
                n->val_conv.val = hret(&msg[j][0]);
            else
                n->msg = "Invalid input";
            n->next = (struct parse_res*)malloc(sizeof(struct parse_res));
            n->next->val_conv.conv = n->val_conv.conv;
            n = n->next;
            break;
            
            case CONV_HTOD:
            ;
            len;
            if((len = strlen(msg[j]))>0)
                n->state = hinput(&msg[j][0],len);
            if(n->state == SUCCESS)
                n->val_conv.val = hret(&msg[j][0]);
            else
                n->msg = "Invalid input";
            n->next = (struct parse_res*) malloc(sizeof(struct parse_res));
            n->next->val_conv.conv = n->val_conv.conv; 
            n = n->next;
            break;
            
            case CONV_HTOA:
            break; //TODO

            case CONV_DTOH:
            n->state = dlen(&msg[j][0],strlen(&msg[j][0]));
            if(n->state == FAILURE)
            {
                n->msg = "Invalid input";
            }
            n->val_conv.d_val = dval(&msg[j][0]);
            n->next = (struct parse_res*) malloc(sizeof(struct parse_res));
            n->next->val_conv.conv = n->val_conv.conv;
            n = n->next;
            break;
            
            case CONV_DTOB:
            n->state = dlen(&msg[j][0],strlen(&msg[j][0]));
            if(n->state == FAILURE)
            {
                n->msg = "Invalid input";
            }
            n->val_conv.d_val = dval(&msg[j][0]);
            n->next = (struct parse_res*) malloc(sizeof(struct parse_res));
            n->next->val_conv.conv = n->val_conv.conv;
            n = n->next;
            break;
            
            case CONV_DTOA:
            break;
            
            case CONV_BTOA:
            case CONV_BTOH:
            case CONV_BTOD:
            ;
            size_t l = strlen(&msg[j][0]);
            if(l<1)
            {
                n->state == FAILURE;
                n->msg = "No input";
            }
            else if(l > sizeof(unsigned long) * 8)
            {
                n->state = FAILURE;
                n->msg = "Too long input";
            }
            else
            {
                if((n->state = bparse(&msg[j][0],strlen(&msg[j][0]))) == FAILURE)
                    n->msg = "Invalid input.";
                if(n->state == SUCCESS)
                    n->val_conv.val = hret(&msg[j][0]);
            }
            n->next = (struct parse_res*) malloc(sizeof(struct parse_res));
            n->next->val_conv.conv = n->val_conv.conv;
            n = n->next;
            break;
            default:
            if(!hash_comp(&msg[j][0]) == result.val_conv.conv)
            {
                printf(S"Unknown conversion type!");
                exit(EXIT_FAILURE);
            }
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

char* hret(char *msg)
{
    int len = (strlen(msg) + 1) * sizeof(char);
    char *strc  = malloc(len);
    memset(strc,'\0',len);
    strcpy(strc,msg);
    return strc;
}
