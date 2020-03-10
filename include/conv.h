#ifndef CONV_H_
#define CONV_H_ 
#include <stdbool.h>
#define HTOD 210644783713   //-htod
#define HTOB 210644783711   //-htob
#define HTOA 210644783710   //-htoa
#define BTOH 210644568095   //-btoh
#define BTOD 210644568091   //-btod
#define BTOA 210644568088   //-btoa
#define DTOH 210644639969   //-dtoh
#define DTOB 210644639963   //-dtob
#define DTOA 210644639962   //-dtoa
#define VAL 6383189877      //-val
#define FIL 6383172717      //-fil
#define HELP 6951207451432  //--help

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
        char *val;
        unsigned long d_val;
    };
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
