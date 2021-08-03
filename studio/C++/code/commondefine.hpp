#pragma once
#include <iostream>
#include <vector>
#include <list>


#define COUT(V) std::cout <<__LINE__<<" ----  "<< V << std::endl;


template<typename T>
void COUTI(T c)
{
    std::cout <<__LINE__<<" ----  ";
    for( auto i : c){
        std::cout << i << " ";
    }
    std::cout<<"\n";
}