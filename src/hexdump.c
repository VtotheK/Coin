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
void hprint(unsigned long c);
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
    if(result.file) //handle file hexdump
    {

    }
    else if(!result.file) //handle value hexdump
    {
        struct parse_res *n = &result;
        if(result.val_len == 0)
        {
            printf(S"%s\n",result.msg);
            exit(EXIT_SUCCESS);
        }
        for(int i=0;i<result.val_len;i++)
        {
            if(!n->file && n->state == SUCCESS)
            {
                switch(n->val_conv.conv)
                {
                    case CONV_HTOB:
                    case CONV_HTOD:
                        ;
                        int             s,hlen,temp;
                        unsigned long   res = 0;
                        char            *ptr;
                        s = hlen = strlen(&n->val_conv.val[0]);
                        ptr = n->val_conv.val;
                        for(;hlen>0;ptr++,hlen--)
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
                            res = res + (pow(16,hlen-1) * temp);
                        }
                        if(n->val_conv.conv == CONV_HTOD)
                        {
                            printf(S"%lu\n",res);
                        }
                        else if(n->val_conv.conv == CONV_HTOB)
                        {
                            bprint(res);
                        }
                        break;
                    case CONV_HTOA:
                        break;
                    case CONV_BTOH:
                    case CONV_BTOD:
                        ;
                        const char      *st = &n->val_conv.val[0];
                        int             len = strlen(&n->val_conv.val[0])-1;
                        char            *start = (char*) st;  
                        unsigned long   bres,val;
                        int             count = len + 1;
                        for(;len>0;len--)
                        {
                            start++;
                        }
                        bres=0;
                        val=1;
                        while(count > 0)
                        {
                            if(*start == 49)
                            {
                                bres = bres + val;
                            }
                            val = val * 2;
                            start--;
                            count--;
                        }
                        if(n->val_conv.conv == CONV_BTOH)
                        {
                            hprint(bres);
                        }
                        else
                        {
                            printf(S"%lu\n",bres);
                        }
                        break;
                    case CONV_BTOA:
                        break;
                    case CONV_DTOH:
                        hprint(n->val_conv.d_val);
                        break;
                    case CONV_DTOB:
                        bprint(n->val_conv.d_val);
                        break;
                    case CONV_DTOA:
                        break;
                }
            }
            else if(n->state == FAILURE)
            {
                printf(S"%s\n",n->msg);
            }
            else if(n->state == SUCCESS && n->file)
            {
                //TODO file hexdump
            }
            n = n->next;
        }
    }
    return 0;
}

void bprint(unsigned long val)
{
    if(val == 1 || val == 0)
    {
        printf(S"%lu\n",val);
        return;
    }
    int             i,k,j;
    char            *bg,*st,*ptr,temp;
    unsigned long   p_val,c_val;
    size_t          l;
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
    ptr=st;
    l = strlen(st);
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

void hprint(unsigned long c)
{
    char hex[] = {'A','B','C','D','E','F'};
    char *res;
    if((res=(char*) malloc(sizeof(char) * VAL_BUFFER))==NULL)
    {
        printf("Could not allocate memory. Aborting!\n");
        exit(EXIT_FAILURE);
    }
    int             temp,dt,i,j,len,m;
    char            t,ptt;
    char            *s_pt,*e_pt;
    s_pt = e_pt = res;
    m = c % 16;
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
    len = strlen(s_pt);
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
