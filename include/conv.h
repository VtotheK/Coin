#ifndef CONV_H_
#include <stdbool.h>
#define CONV_H_ 
#define HTOD    0xB87801E   //-hd
#define HTOB    0xB87801C   //-hb
#define HTOA    0xB87801B   //-ha
#define BTOH    0xB877F5C   //-bh
#define BTOD    0xB877F58   //-bd
#define BTOA    0xB877F55   //-ba
#define DTOH    0xB877F9E   //-dh
#define DTOB    0xB877F98   //-db
#define DTOA    0xB877F97   //-da
#define ATOD    0xB877F37   //-ad
#define ATOH    0xB877F3B   //-ah
#define ATOB    0xB877F35
#define HELP    0xB877887   //--h
#define VAL     0x597088    //-v
#define FIL     0x597078    //-f
#define VRT     0xB877895   //--v 
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
    CONV_DTOA,
    CONV_ATOD,
    CONV_ATOH,
    CONV_ATOB
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

struct targets
{
    unsigned long ultarget; 
    struct targets *next;
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
    int argc;
    struct parse_res *next;
    struct targets *targets;
    size_t targetlen;
    size_t val_len;
    char *msg;
    char *filepath;
    enum parse_state state;
    bool file;
    bool vertical;
    union 
    {
        struct file_conv f_conv;
        struct value_conv val_conv;
    };
};

#endif
