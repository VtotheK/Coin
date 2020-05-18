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
bool istarget(unsigned long,struct parse_res, size_t);
struct targets* addtarget(struct targets*,unsigned long);
struct parse_res parse_args(char **msg,const int a_count)
{
    struct parse_res result;
    result.targets = malloc(sizeof(struct targets));
    result.targetlen = 0;
    result.val_len = 0;
    result.filepath = NULL;
    result.vertical=false;
    struct parse_res *n = &result;
    result.file = false;
    result.customdelimiter = false;
    result.f_readlen = 0;
    result.state = FAILURE;
    result.val_conv.conv = EMP;
    result.originalvalues = false;
    int i,j,index;
    unsigned long target,temptarget;
    struct targets *ntarget = result.targets;
    int len;
    bool u_conv = false;
    for(i=0; i<a_count;i++)
    {
        temptarget = hash_comp(msg[i]);
        len = strlen(&msg[i][0]);
        if(len > 1 && msg[i][0] == '-' && msg[i][1] != '-')
        {
            switch(temptarget)
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
            }
            if((result.val_conv.conv != EMP || result.file) && !u_conv)
            {
                result.targetlen++;
                ntarget = addtarget(ntarget,temptarget);
                u_conv=true;
            }
            else if(result.val_conv.conv != EMP && u_conv)
            {
                result.msg = "Only one value conversion. Type --h to see all commands.";
                result.state = FAILURE;
                return result;
            }
            else if(result.file && result.val_conv.conv != EMP)
            {
                result.msg = "No file and value conversion at same time.";
                result.state = FAILURE;
                return result;
            }

        }
        else if(strlen(&msg[i][0]) > 2 && msg[i][0] == '-' && msg[i][1] ==  '-')
        {
            if(!result.file && strcmp(&msg[i][0],"--v")==0)
            {
                result.vertical = true;
                result.targetlen++;
                ntarget = addtarget(ntarget,temptarget);
            }
            else if(temptarget == HELP)
            {
                result.msg = "Some helper message";
                result.state == HELPER;
                return result;
            }
            else if(result.file && strlen(&msg[i][0]) > 3 && msg[i][0] == '-'
                    && msg[i][1] == '-' && msg[i][2] == 'l')
            {
                int readlen,arglen;
                arglen = strlen(&msg[i][0]) - 3;
                char *arg;
                if((arg = malloc(arglen * sizeof(char) + 1))==NULL)
                {
                    printf("Could not allocate memory");
                    exit(EXIT_FAILURE);
                }
                memset(arg,'\0',arglen+1);
                strncpy(arg,&msg[i][3],arglen);
                if((readlen = atoi(arg)) == 0)
                {
                    result.state = FAILURE;
                    result.msg = "Invalid file read length.";
                    return result;
                }
                else
                {
                    result.f_readlen = readlen;
                    result.targetlen++;
                    ntarget = addtarget(ntarget,temptarget);
                }
            }
            else if(!result.file && strcmp(&msg[i][0],"--ov") == 0)
            {
              result.originalvalues = true;
              result.targetlen++;
              ntarget = addtarget(ntarget,temptarget);
            }
            else if(!result.file && strlen(&msg[i][0]) > 4 && msg[i][0] == '-'
                    && msg[i][1] == '-' && msg[i][2] == 'c' && msg[i][3] == 'd')
            {
              int arglen = strlen(&msg[i][0]) - 4;
              result.cstdel = (char*) malloc(sizeof(char) * arglen + 1);
              if(result.cstdel == NULL)
              {
                  printf("Could not allocate memory");
                  exit(EXIT_FAILURE);
              }
              else
              {
                  memset(result.cstdel, '\0', arglen + 1);
                  strcpy(result.cstdel, &msg[i][4]);
              }
              result.customdelimiter = true;
              result.targetlen++;
              ntarget = addtarget(ntarget,temptarget);
            }
            //TODO handle --commands stack --commands to ntarget struct pointer
        }
    }

    if((result.val_conv.conv != EMP && !result.file) || result.file)
    {
        result.state = SUCCESS;
    }
    else if(result.state == FAILURE)
    {
        result.msg = "No conversion type. Type -h to see all commands.";
        return result;
    }
    if(result.file) 
    {
        for(int k = 0; k<a_count;k++)
        {
            if(istarget(hash_comp(&msg[k][0]),result,result.targetlen))
                continue;
            if(result.filepath == NULL)
            {
                result.filepath = hret(&msg[k][0]);
                return result;
            }
            else
            {
                result.msg = "One filepath only.";
                result.state == FAILURE;
                return result;
            }
        }

    }     
    else if(result.val_conv.val != EMP && result.state == SUCCESS)
    {
        for(j=0,index=0; j<a_count;j++)
        {
            if(istarget(hash_comp(&msg[j][0]),result,result.targetlen))
                continue;
            switch(n->val_conv.conv) 
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
                if(result.originalvalues)
                {
                    int valuelength = strlen(&msg[j][0]);
                    n->val_conv.originalvalue = (char*) malloc(sizeof(char) * valuelength + 1);
                    memset(n->val_conv.originalvalue, '\0', valuelength + 1);
                    strcpy(n->val_conv.originalvalue, &msg[j][0]);
                }
                n->next = (struct parse_res*) malloc(sizeof(struct parse_res));
                n->next->val_conv.conv = n->val_conv.conv; 
                n = n->next;
                break;

                case CONV_HTOA:
                //TODO Decide if to use UTF-8 or just ASCII encoding 
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
                //TODO Decide if to use UTF-8 or just ASCII encoding 
                break;

                case CONV_BTOA:
                //TODO Decide if to use UTF-8 or just ASCII encoding 
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
                    printf("Unknown conversion type!");
                    exit(EXIT_FAILURE);
                }
            }
            result.val_len++;
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

bool istarget(unsigned long arg, struct parse_res res, size_t len)
{
    struct targets *currenttarget = res.targets; 
    for(;len>0;len--) 
    {
        if(arg==currenttarget->ultarget)
        {
            return true;
        }
        currenttarget = currenttarget->next;
    }
    return false;
}

struct targets* addtarget(struct targets* targets, unsigned long val)
{
    targets->ultarget = val;
    targets->next = malloc(sizeof(struct targets));
    targets = targets->next;
    return targets;
}
