#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/conv.h"
#include "../include/parser.h"
#include "../include/w_error.h"
#define VAL_BUFFER 128

void w_error(char *msg)
{
    printf("%s",msg);
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
        printf("%s",result.msg);
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
                case CONV_HTOD:
                    break;
                case CONV_HTOB:
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
                        char *hex = "A,B,C,D,E,F";
                        char *res = (char*) malloc(sizeof(char) * VAL_BUFFER);
                        memset(res, '\0', sizeof(char) * VAL_BUFFER);
                        int i = 0;
                        unsigned long c = result.val_conv.d_val;
                        int m = c % 16;
                        if(m > 9)
                        {
                            int n = m - 10;
                            strcpy(res++,&hex[n]);
                        }
                        else
                        {
                            *res++ = m + '0';
                        }
                        i++;
                        int rem = c; 
                        while((rem = rem / 16) > 1)
                        {
                            int s;
                            int temp = rem % 16;
                            if(temp > 9)
                            {
                                s = rem - 10;
                                strcpy(res++,&hex[s]);  
                            }
                        }
                        printf("%s",res);
                    }
                    else 
                    {
                        w_error("FATAL ERROR: Wrong parse result. Aborting!");
                    }
                    break;
                case CONV_DTOB:
                    break;
                case CONV_DTOA:
                    break;
            }
        }
    }

    return 0;
}
