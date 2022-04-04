#pragma once
#include <string>

#define  MAX_LENGHT 384 //64*6 

class TcpDataAnaly
{
private:
    /* data */
public:
    TcpDataAnaly(/* args */);

    void add(char *d,int lenght);


private:
    char    pack_data[MAX_LENGHT];
    int     pack_lenght=0;
};

