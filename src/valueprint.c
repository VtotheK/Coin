#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#include "../include/bprint.h"
#include "../include/hget.h"
#include "../include/hget.h"
#include "../include/ansi_c.h"
#include "../include/conv.h"
#include "../include/hget.h"
#include "../include/char_val.h"
#include "../include/valueprint.h"

void ovprint(struct parse_res*, const struct parse_res*);

void valueprint(struct parse_res *n, const struct parse_res *result)
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
                    temp = (int)*ptr-55;
                else if (*ptr <= LC_CHAR_MAX && *ptr >= LC_CHAR_MIN) 
                    temp = (int)*ptr-87;
                else if (*ptr <= NUM_MAX && *ptr >= NUM_MIN)
                    temp =  *ptr - '0';
                else
                {
                    printf("Value %d is invalid in  hexdump.c. Aborting!\n",temp);
                    exit(1);
                }
                res = res + (pow(16,hlen-1) * temp);
            }
            if(n->val_conv.conv == CONV_HTOD)
            {
                if(result->originalvalues)
                  ovprint(n,result);
                printf("%lu ",res);
                if(result->vertical)
                    printf("\n");
            }
            else if(n->val_conv.conv == CONV_HTOB)
            {
                if(result->originalvalues)
                    ovprint(n,result);
                bprint(res);
                printf(" ");
                if(result->vertical)
                    printf("\n");
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
                    bres = bres + val;
                val = val * 2;
                start--;
                count--;
            }
            if(n->val_conv.conv == CONV_BTOH)
            {
                char *resptr = hget(bres);
                if(result->originalvalues)
                    ovprint(n,result);
                printf("%s",resptr);
                printf(" ");
                if(result->vertical)
                    printf("\n");
            }
            else
            {
                if(result->originalvalues)
                    ovprint(n,result);
                printf("%lu ",bres);
                if(result->vertical)
                    printf("\n");
            }
            break;
        case CONV_BTOA:
            break;
        case CONV_DTOH:
            ;
            char *resptr = hget(n->val_conv.d_val);
            if(result->originalvalues)
                ovprint(n,result);
            printf("%s",resptr);
            printf(" ");
            if(result->vertical)
                printf("\n");
            break;
        case CONV_DTOB:
            if(result->originalvalues)
                ovprint(n,result);
            bprint(n->val_conv.d_val);
            printf(" ");
            if(result->vertical)
                printf("\n");
            break;
        case CONV_DTOA:
            break;
    }
}

void ovprint(struct parse_res *n, const struct parse_res *result)
{
    printf("%s",n->val_conv.originalvalue);
    if(result->customdelimiter)
        printf("%s",result->cstdel);
    else
        printf("=");
}
