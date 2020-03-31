#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "../include/conv.h"
#include "../include/char_val.h"
#include "../include/parser.h"
#include "../include/w_error.h"
#include "../include/ansi_c.h"
#define VAL_BUFFER 1024
void bprint(unsigned long val);

void w_error(char *msg)
{
    perror(msg);
    exit(1);

}

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("No command line arguments.");
        exit(EXIT_FAILURE);
    }
    struct parse_res result = parse_args(++argv,argc-1);
    if(result.state == FAILURE)
    {
        printf("%s\n",result.msg);
        exit(EXIT_FAILURE);
    }
    else if(result.state == SUCCESS)
    {
        if(result.file) //handle file hexdump
        {

        }
        else if(!result.file) //handle value hexdump
        {
            switch(result.val_conv.conv)
            {
                case CONV_HTOB:
                case CONV_HTOD:
                    if(!result.file)
                    {
                        int             s,len,temp;
                        unsigned long   res = 0;
                        char            *ptr;
                        s = len = strlen(result.val_conv.val);
                        ptr = result.val_conv.val;
                        for(;len>0;ptr++,len--)
                        {
                            if (*ptr <= UC_CHAR_MAX && *ptr >= UC_CHAR_MIN) 
                            {
                                temp = (int)*ptr-55;
                            }
                            else if (*ptr <= LC_CHAR_MAX && *ptr >= LC_CHAR_MIN) 
                            {
                                temp = (int)*ptr-87;
                            }
                            else if (*ptr <= NUM_MAX && *ptr >= NUM_MIN)
                            {
                                temp =  *ptr - '0';
                            }
                            else
                            {
                                printf("Value %d is invalid in  hexdump.c. Aborting!\n",temp);
                                exit(1);
                            }
                            res = res + (pow(16,len-1) * temp);
                        }
                        if(result.val_conv.conv == CONV_HTOD)
                        {
                            printf(S"%lu\n",res);
                        }
                        else if(result.val_conv.conv == CONV_HTOB)
                        {
                            bprint(res);
                        }
                    }
                    break;
                case CONV_HTOA:
                    break;
                case CONV_BTOH:
                    break;
                case CONV_BTOD:
                    break;
                case CONV_BTOA:
                    break;
                case CONV_DTOH:
                    if(!result.file)
                    {
                        //printf("%lu",result.val_conv.d_val);
                        char hex[] = {'A','B','C','D','E','F'};
                        char *res;
                        if((res=(char*) malloc(sizeof(char) * VAL_BUFFER))==NULL)
                        {
                            printf("Could not allocate memory. Aborting!\n");
                            exit(EXIT_FAILURE);
                        }
                        int             temp,dt,i,j;
                        char            t,ptt;
                        unsigned long   c = result.val_conv.d_val;
                        int             m = c % 16;
                        char            *s_pt,*e_pt;
                        s_pt = e_pt = res;
                        memset(res, '\0', sizeof(char) * VAL_BUFFER);
                        do
                        {
                            temp = c%16;
                            if(temp > 9)
                            {
                                dt = temp - 10;
                                strncat(res,&hex[dt],1);
                            }
                            else
                            {
                                t = temp + '0';
                                strncat(res,&t,1);
                            }
                        } while((c = c/16) >= 1);
                        int len = strlen(s_pt);
                        for(i=0;i<len-1;i++)
                        {
                            e_pt++;
                        }
                        for(j=0;j<len/2;j++)
                        {
                            ptt = *s_pt;
                            *s_pt = *e_pt;
                            *e_pt = ptt;
                            e_pt--;
                            s_pt++;
                        }
                        printf(S"%s\n",res);
                    }
                    else 
                    {
                        printf(S"FATAL ERROR: Wrong parse result. Aborting!\n");
                        exit(EXIT_FAILURE);
                    }
                    break;
                case CONV_DTOB:
                    ;
                    if(!result.file)
                    {
                        bprint(result.val_conv.d_val);
                    }
                    break;
                case CONV_DTOA:
                    break;
            }
        }
    }

    return 0;
}

void bprint(unsigned long val)
{
    if(val == 1 || val == 0)
    {
        printf(S"%lu",val);
        exit(1);
    }
    int i;
    char            *bg,*st,*ptr;
    unsigned long   p_val,c_val;;
    double          c_bit = 1;
    bool            first = true;
    if((st = (char*) malloc(sizeof(char) * VAL_BUFFER)) == NULL)
    {
        printf(S"Could not allocate memory. Aborting!\n");
        exit(EXIT_FAILURE);
    }
    bg=ptr=st;
    memset(ptr,'0',sizeof(char)*VAL_BUFFER);
    p_val = c_val = 1;
    while(val > 0)
    {
        while(val>=c_val)
        {
            p_val = c_val;
            c_bit++;
            c_val = c_val * 2;
        }
        c_val = c_val - p_val;
        c_bit--;
        val = val - c_val;
        for(i=0;i<c_bit-1;i++)
        {
            ptr++;
        }
        memset(ptr,'1',1);
        if(first)
        {
            memset(st,'0',c_bit-2);
            first=false;
            ptr++;
            memset(ptr,'\0',1);
        }
        ptr=st;
        p_val = c_bit = c_val = 1;
    }
    char temp;
    int k,j;
    ptr=st;
    size_t l = strlen(st);
    for(j=0;j<l-1;j++)
    {
        ptr++;
    }
    for(k=0;k<l/2;k++)
    {
        temp = *st;
        *st=*ptr;
        *ptr=temp;
        ptr--;
        st++;
    }
    printf(S"%s\n",bg);
}
