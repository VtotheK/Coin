#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include "../include/conv.h"
#include "../include/char_val.h"
#include "../include/parser.h"
#include "../include/w_error.h"
#include "../include/ansi_c.h"
#include "../include/hget.h"

void bprint(unsigned long val);

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("No command line arguments.");
        exit(EXIT_FAILURE);
    }
    setlocale(LC_ALL,"C");
    struct parse_res result = parse_args(++argv,argc-1);
    if(!result.file) //handle value hexdump
    {
        struct parse_res *n = &result;
        if(result.val_len == 0)
        {
            printf("%s\n",result.msg);
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
                            if(result.originalvalues)
                            {
                                printf("%s",n->val_conv.originalvalue);
                                if(result.customdelimiter)
                                  printf("%s",result.cstdel);
                                else
                                  printf("=");
                            }
                            printf("%lu ",res);
                            if(result.vertical)
                                printf("\n");
                        }
                        else if(n->val_conv.conv == CONV_HTOB)
                        {
                            bprint(res);
                            printf(" ");
                            if(result.vertical)
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
                            {
                                bres = bres + val;
                            }
                            val = val * 2;
                            start--;
                            count--;
                        }
                        if(n->val_conv.conv == CONV_BTOH)
                        {
                            char *resptr = hget(bres);
                            printf("%s",resptr);
                            printf(" ");
                            if(result.vertical)
                                printf("\n");
                        }
                        else
                        {
                            printf("%lu ",bres);
                            if(result.vertical)
                                printf("\n");
                        }
                        break;
                    case CONV_BTOA:
                        break;
                    case CONV_DTOH:
                        ;
                        char *resptr = hget(n->val_conv.d_val);
                        printf("%s",resptr);
                        printf(" ");
                        if(result.vertical)
                            printf("\n");
                        break;
                    case CONV_DTOB:
                        bprint(n->val_conv.d_val);
                        printf(" ");
                        if(result.vertical)
                            printf("\n");
                        break;
                    case CONV_DTOA:
                        break;
                }
            }
            else if(n->state == FAILURE)
            {
                if(result.originalvalues)
                {
                  printf("%s",n->val_conv.originalvalue);
                  if(result.customdelimiter)
                      printf("%s",result.cstdel);
                  else
                      printf("=");
                }
                printf("%s",n->msg);
                if(result.vertical)
                    printf("\n");
                else
                    printf(" ");
            }
            n = n->next;
        }
        if(!result.vertical)
            printf("\n");
        free(n);
    }
    else if(result.state == SUCCESS && result.file)
    {
        long filelen;
        int counter = 0;
        unsigned char *buffer,*txtptr;
        FILE *fileptr = fopen(result.filepath,"rb");
        if(fileptr == NULL)
        { 
            printf("Invalid filepath\n");
            exit(EXIT_FAILURE);
        }
        else
        {
            const unsigned char *start = (unsigned char*) malloc(17*sizeof(char));
            txtptr = (unsigned char*) start;
            memset(txtptr,'\0',17);
            if(result.f_readlen > 0)
            {
                fseek(fileptr,0,SEEK_END);
                if(ftell(fileptr) < result.f_readlen)
                {
                    printf("Unable to read file");
                    exit(EXIT_FAILURE);
                }
                fseek(fileptr,result.f_readlen,SEEK_SET);
                filelen = ftell(fileptr);
            }
            else
            {
                fseek(fileptr,0,SEEK_END);
                filelen = ftell(fileptr);
            }
            buffer = (unsigned char*) malloc(sizeof(unsigned char) * filelen);
            rewind(fileptr);
            fread(buffer,filelen, sizeof(unsigned char),fileptr);
            unsigned long current = 0;
            printf("%s[%s00000000%s]%s ",HRED,reset,HRED,reset);
            int last = filelen % 16;
            for(int a = 0; a<filelen;a++,counter++,buffer++,txtptr++)
            {
                if(counter > 15)
                {
                    printf("%s|%s",GRN,reset);
                    printf("%s%s%s",RED,start,reset);
                    memset((unsigned char*)start,'\0',17);
                    txtptr = (unsigned char*)start;
                    current = current + 1;
                    counter = 0;
                    printf("\n%s[%s",HRED,reset);
                    unsigned char *offset = hget(current);
                    for(int k = 0; k<7-strlen(offset);k++)
                        printf("0");
                    printf("%s0%s]%s ",offset,HRED,reset);

                }
                else if(counter == 8)
                    printf("%s|%s   ",GRN,reset);
                printf("%s|%s",GRN,reset);
                unsigned char *val = hget((unsigned long)*buffer);
                if(*buffer<16)
                    printf("%s0%s",BCYN,reset);
                //printf("BUFFER_VALUE:%s",*buffer);
                printf("%s%s%s",BCYN,val,reset);
                if(*buffer < 127 && *buffer > 33)
                    *txtptr = *buffer;
                else if(*buffer==10)
                    *txtptr = '.'; 
                else
                    *txtptr = '.';
            }
            if(last != 0)
            {
                printf("%s|%s",GRN,reset);
                if(last <= 8)
                    printf("    ");
                int end = (16*3-1) - (last * 3);
                for(int h = 0; h < end; h++)
                {
                    printf(" ");
                    if(h==end-1)
                        printf("%s|%s",GRN,reset);
                }
            }
            else
                printf("%s|%s",GRN,reset);
            txtptr = (char*)start;
            printf("%s%s%s",HRED,txtptr,reset);
            printf("\n");
        }
        free(fileptr);
        free(txtptr);
    }
    return 0;
}

