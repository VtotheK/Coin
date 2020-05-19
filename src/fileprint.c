#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#include "../include/ansi_c.h"
#include "../include/conv.h"
#include "../include/hget.h"
void fileprint(const struct parse_res *result)
{
    unsigned long filelen;
    int counter = 0;
    unsigned char *buffer,*txtptr;
    FILE *fileptr = fopen(result->filepath,"rb");
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
        if(result->f_readlen > 0)
        {
            fseek(fileptr,0,SEEK_END);
            if(ftell(fileptr) < result->f_readlen)
            {
                printf("Unable to read file");
                exit(EXIT_FAILURE);
            }
            fseek(fileptr,result->f_readlen,SEEK_SET);
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
