#include "tcp_data_analy.hpp"
#include "base_library.h"
#include <iostream>
#include "tcp_define.hpp"
#include <string.h>

TcpDataAnaly::TcpDataAnaly(/* args */) 
{
    
}

void TcpDataAnaly::add(char *d, int lenght) 
{
    if( pack_lenght == 0)
    {
        memset(pack_data,0,sizeof(pack_data));
    }

    //解析头
    PACKET_HEADER head;
    auto head_lenght = sizeof(head);
    memcpy(&head,d,head_lenght);

    //解析数据
    int start_bit = pack_lenght;
    int data_lenght = lenght - head_lenght;
    pack_lenght += data_lenght;

    if(pack_lenght <= MAX_LENGHT)
    {
        memcpy(pack_data + start_bit, d + head_lenght,data_lenght);
    }

}
