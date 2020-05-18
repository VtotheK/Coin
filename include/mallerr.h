#ifndef MALLERR_H__
#define MALLERR_H_

enum sender 
{
    SENDER_PARSER,
    SENDER_HXD
}

void mallerr(char*,enum sender);

#endif
