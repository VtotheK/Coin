#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/bprint.h"
void bprint(unsigned long val)
{
    if(val == 1 || val == 0)
    {
        printf("%lu ",val);
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
        printf("Could not allocate memory. Aborting!\n");
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
    printf("%s",bg);
}
