#ifndef PARSER_H_
#define PARSER_H_
#define MSG_SIZE 64
#define ERR_MCONV "Multiple conversion types requested, only specify one."
unsigned long hash_comp(unsigned char*);
char* hret(char*);
struct parse_res parse_args(char **msg,int a_count);
#endif
