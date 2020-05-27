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
#include "../include/fileprint.h"
#include "../include/valueprint.h"
void bprint(unsigned long val);

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("No command line arguments.");
        exit(EXIT_FAILURE);
    }
    setlocale(LC_ALL,"C");
    const struct parse_res result = parse_args(++argv,argc-1);
    if(!result.file) 
    {
        struct parse_res *n = (struct parse_res*)&result;
        if(n->state == HELPER)
        {
            printf("=========================================================================\n");
            printf("|         Coin is a light value converter / file hexdump program        |\n");
            printf("|                    https://github.com/VtotheK/Coin.                   |\n");
            printf("|                                                                       |\n");
            printf("|./coin [-dh|-db|-hd|-hb|-bd|-bh] [--ov] [--cd<value>] [--v] <values>   |\n");
            printf("|./coin [-f] [--l<value>] <filepath>                                    |\n");
            printf("|./coin [--h]                                                           |\n");
            printf("|Value converting:                                                      |\n");
            printf("|--ov original values                                                   |\n");
            printf("|--v  vertical printing                                                 |\n");
            printf("|--cd<value> custom value delimiter                                     |\n");
            printf("|File hexdump:                                                          |\n");
            printf("|--l<value> file read length in bytes                                   |\n");
            printf("=========================================================================\n");
            return 0; 
        }

        if(result.val_len == 0)
        {
            printf("%s\n",result.msg);
            exit(EXIT_SUCCESS);
        }
        for(int i=0;i<result.val_len;i++)
        {
            if(!n->file && n->state == SUCCESS)
            {
                valueprint(n,&result);
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
            if(n->next != NULL)
                n = n->next;
        }
        if(!result.vertical)
            printf("\n");
        free(n);
    }
    else if(result.state == SUCCESS && result.file)
    {
        fileprint(&result);
    }
    return 0;
}

