#ifndef CONV_H_
#define CONV_H_ 

#define HTOD "fuck" 

enum conv
{
    VAL,
    FIL
};

enum val_conv 
{
    //HTOD,
    HTOB,
    HTOA,
    BTOH,
    BTOD,
    BTOA,
    DTOH,
    DTOB,
    DTOA
};

enum f_conv
{
    FTOH,
    FTOB,
    FTOD
};

struct file_conv
{
    enum f_conv conv;
    char *path;
};

/*typedef struct parse_res
{
    union
    {

    }
} 
*/

#endif
