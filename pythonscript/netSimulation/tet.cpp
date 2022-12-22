#ifndef __PARSER_NET_TYPEDEF_H__
#define __PARSER_NET_TYPEDEF_H__
#include "parser_net_signal_structs.h"

//=====================================================================================//
/*[[[cog
cog.outl('三次:') 
for i in range(3): 
    cog.outl('This is line %d' % i) 
]]]*/
//[[[end]]]
//=====================================================================================//
//cog -r tet.cpp
extern bool parser_net(char *data, int length);
extern void set_update_fun(fpNetUpDateCallBack_t func);
#endif