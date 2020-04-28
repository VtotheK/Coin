#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/hget.h"
char* hget(unsigned long c)
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
    return res;
}
