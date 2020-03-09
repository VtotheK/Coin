#ifndef CONV_H_
#define CONV_H_ 
#include <stdbool.h>
#define HTOD 191386209
#define HTOB 191386207
#define HTOA 191386206
#define BTOH 191170591
#define BTOD 191170587
#define BTOA 191170584
#define DTOH 191242465
#define DTOB 191242459
#define DTOA 191242458
#define VAL 2088222581
#define FIL 2088205421


enum conv
{
    CONV_VAL,
    CONV_FIL
};

enum parse_state
{
    FAILURE,
    SUCCESS
};

enum val_conv 
{
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
    char *val;
};

struct parse_res
{
    char *msg;
    enum parse_state state;
    bool file;
    union 
    {
        struct file_conv f_conv;
        struct value_conv val_conv;
    };
};

#endif
