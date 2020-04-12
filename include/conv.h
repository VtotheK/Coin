#ifndef CONV_H_
#define CONV_H_ 
#include <stdbool.h>
#define HTOD    0xB87801E   //-hd
#define HTOB    0xB87801C   //-hb
#define HTOA    0xB87801B   //-ha
#define BTOH    0xB877F5C   //-bh
#define BTOD    0xB877F58   //-bd
#define BTOA    0xB877F55   //-ba
#define DTOH    0xB877F9E   //-dh
#define DTOB    0xB877F98   //-db
#define DTOA    0xB877F97   //-da
#define HELP    0xB877887   //--h
#define VAL     0x597088    //-v
#define FIL     0x597078    //-f

enum conv
{
    CONV_VAL,
    CONV_FIL
};


enum parse_state
{
    FAILURE,
    SUCCESS,
    HELPER
};

enum val_conv 
{
    EMP,
    CONV_HTOD,
    CONV_HTOB,
    CONV_HTOA,
    CONV_BTOH,
    CONV_BTOD,
    CONV_BTOA,
    CONV_DTOH,
    CONV_DTOB,
    CONV_DTOA
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

struct value_conv
{
    enum val_conv conv;
    union
    {
        char **val;
        unsigned long *d_val;
    };
};

struct parse_res
{
    int argc;
    struct parse_res *next;
    char *msg;
    char *arg_raw;
    enum parse_state state;
    bool file;
    union 
    {
        struct file_conv f_conv;
        struct value_conv val_conv;
    };
};

#endif
